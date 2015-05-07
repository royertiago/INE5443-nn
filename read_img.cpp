#include <stdexcept>
#include <opencv2/highgui/highgui.hpp>
#include "read_img.h"

std::vector<float> read_pixels( std::string filename ) {
    cv::Mat_<float> img = cv::imread( filename, CV_LOAD_IMAGE_GRAYSCALE );

    if( ! img.data )
        throw std::runtime_error("Error reading file " + filename);

    std::vector<float> ret(img.begin(), img.end());
    for( auto & f : ret )
        f = 1 - f/255;

    return ret;
}
