Neural Networks
===============


This is a class assignment for the INE5443 discipline
--- Pattern Recognition.

Our task is to use some neural network library
and train a neural network to recognize numbers
in images with 10x15 pixels.

Building
========

This program depends on the libraries `opencv` and `fann`.
These can be obtained via

    apt-get install libopencv-dev libfann-dev

Also, I've made use of some of the C++11 features,
so your compiler should be moderately recent.
I have tested with `gcc 4.9.2`.

Just type

    make

on the command line.
