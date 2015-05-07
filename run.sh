#!/bin/bash

echo Training the neural network with 10 internal nodes:
./train --hidden-neurons 10 img/*

echo Testing the neural network with the training images:
./test --verbose img/*
