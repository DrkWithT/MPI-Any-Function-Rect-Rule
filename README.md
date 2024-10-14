# README

### Brief:
A MPI C++ project for doing numeric integral approximation with the rectangle rule, but with a twist: For a range of user-entered functions!

### Requirements:
 - Git
 - CMake 3.16+
 - A C++ compiler e.g clang++, g++, etc.
 - The `mpi.h` AKA the MPI library header.

### TODOs:
 - Add, test, and integrate instruction generator for AST.
 - Create skeleton of parallelized code:
    - Root takes user input to parse and compile to a function exclusively.
    - Root also serializes the instructions and broadcasts them to other processes as the "x-function".
 - Test more!
