Neural Networks
===============


This is a class assignment for the INE5443 discipline
--- Pattern Recognition.

Our task is to use some neural network library
and train a neural network to recognize numbers
in images with 10x15 pixels.

The training images are avaliable in the `img/` subdirectory.

Building
========

This program depends on the libraries `opencv` and `fann`.
These can be obtained via

    apt-get install libopencv-dev libfann-dev

Also, I've made use of some of the C++11 features,
so your compiler should be moderately recent.
I have tested with `gcc 4.9.2`.

To build `doc/relatorio.pdf`, you will also need LaTeX.

Just type

    make

on the command line.
