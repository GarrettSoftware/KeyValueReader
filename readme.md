# KeyValueReader 2.0

## Overview
This is a library to implement a simple Key/Value reader from file.
The goal is for the library to be very simple to use and understand.

I wrote it with the scientific community in mind, especially for small projects that want a simple ability to read input parameters from a file.
This is the reason for both the C and Fortran interfaces.

## Getting the software
The main repository for this software is at: https://github.com/GarrettSoftware/KeyValueReader

To get the software, click on the `Branch` button and choose the version you want to use.
Alternatively, the `master` branch should contain the latest stable version.

## Compiling the software
The software is compiled using C++ and requires a compiler that implements the C++11 standard.
If you are using GCC, you should be able to type `make` in the main directory to build the library.
If you are not using GCC, open `Makefile` and set the top line for your compiler.
Both a static and dynamic library are created and placed in a directory called `lib`.

## Using the software
There are examples in the `examples` directory of how to build both a C and Fortran application with the library.
