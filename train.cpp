namespace command_line {
    const char help_message[] =
" [options] images...\n"
"Train a neural network to recognize the images listed in the command line.\n"
"\n"
"Options:\n"
"--net-output <file>\n"
"    Writes the neural net to <file>.\n"
"    Default: neural.net.\n"
"\n"
"--data-output <file>\n"
"    Writes auxiliary data (to pretty-printing the output) to <file>.\n"
"    Default: neural.data.\n"
"\n"
"--error <F>\n"
"    Chooses the maximum allowed error.\n"
"    Default: 1e-3.\n"
"\n"
"--hidden-neurons <N>\n"
"    Chooses the number of hidden neurons.\n"
"    Default: 1 + sqrt( image size * image number ).\n"
"\n"
"--max-epochs <N>\n"
"    Chooses the maximum number of training epochs.\n"
"    Default: 1e5.\n"
"\n"
"--epochs-between-reports <N>\n"
"    Number of epochs between each status report.\n"
"    Default: 1000.\n"
"\n"
"--help\n"
"    Show this text and quit.\n"
;
} // namespace command_line

#include <cstdlib>
#include <cmath>
#include <iostream>
#include <fstream>
#include "cmdline/args.hpp"
#include "fann.h"
#include "fann_cpp.h"
#include "read_img.h"

namespace command_line {
    /* These two vectors contains all the input data used for training.
     * input.data() is ready to be used as the input parameter
     * in the FANN::training_data::set_train_data method.
     * input_holder is an auxiliar vector, used to delete the subvectors of the input.
     */
    std::vector< float * > input;
    std::vector< std::vector<float> > input_holder;

    std::string net_output = "neural.net";
    std::string data_output = "neural.data";
    std::vector< std::string > file_names;

    double error = 1e-3;
    unsigned hidden_neurons = 0; // if it is zero, we will reset to sqrt(...).
    unsigned max_epochs = 1e5;
    unsigned epochs_between_reports = 1000;

    void parse( cmdline::args && args ) {
        while( args.size() > 0 ) {
            std::string arg = args.next();
            if( arg == "--net-output" ) {
                net_output = args.next();
                continue;
            }
            if( arg == "--data-output" ) {
                data_output = args.next();
                continue;
            }
            if( arg == "--error" ) {
                args.range(0) >> error;
                continue;
            }
            if( arg == "--hidden-neurons" ) {
                args.range(1) >> hidden_neurons;
                continue;
            }
            if( arg == "--max-epochs" ) {
                args.range(1) >> max_epochs;
                continue;
            }
            if( arg == "--epochs-between-reports" ) {
                args.range(1) >> epochs_between_reports;
                continue;
            }
            if( arg == "--help" ) {
                std::cout << args.program_name() << help_message;
                std::exit(0);
            }
            file_names.push_back( arg );
            input_holder.push_back( read_pixels(arg) );
            input.push_back( input_holder.back().data() );
        }
        if( file_names.size() == 0 ) {
            args.log() << "There must be at least one file name.\n";
            std::exit(1);
        }
        if( hidden_neurons == 0 )
            hidden_neurons = 1 + std::sqrt( input.size() * input_holder[0].size() );
    }
} // namespace command_line

int main( int argc, char ** argv ) {
    command_line::parse( cmdline::args(argc, argv) );

    /* Similar to command_line::input, but for the output.
     */
    std::vector< float * > output;
    std::vector< std::vector<float> > output_holder;
    for( int i = 0; i < command_line::input.size(); i++ ) {
        std::vector<float> output_instance( command_line::input.size(), 0.0 );
        output_instance[i] = 1.0;
        output_holder.push_back( output_instance );
        output.push_back( output_holder.back().data() );
    }

    FANN::neural_net nn;

    /* We have to cast some arguments to unsigned
     * because create_standard is a C-style variadic function
     * that expects unsigned elements,
     * and std::vector::size() returns a std::size_t.
     */
    nn.create_standard(
        3,
        (unsigned) command_line::input_holder[0].size(),
        command_line::hidden_neurons,
        (unsigned) command_line::input.size()
    );

    FANN::training_data data;
    data.set_train_data(
        command_line::input.size(),
        command_line::input_holder[0].size(),
        command_line::input.data(),
        output_holder[0].size(),
        output.data()
    );

    nn.set_activation_function_output( FANN::SIGMOID );
    nn.set_activation_function_hidden( FANN::SIGMOID );
    nn.train_on_data(
        data,
        command_line::max_epochs,
        command_line::epochs_between_reports,
        command_line::error
    );

    nn.save( command_line::net_output );

    std::ofstream data_file( command_line::data_output );
    for( auto str : command_line::file_names )
        data_file << str << '\n';

    return 0;
}
