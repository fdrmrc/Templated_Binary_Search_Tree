# Template Binary Search Tree [![Build Status](https://travis-ci.com/fdrmrc/Templated_Binary_Search_Tree.svg?branch=main)](https://travis-ci.com/github/fdrmrc/Templated_Binary_Search_Tree)

A C++ implementation of a Templated Binary Search Tree using smart pointers

## Authors:

- [Marco Feder](mailto:marco.feder@sissa.it)
-
-

## How to compile
First, clone the repo to your local machine.

### Using `Makefile`:
- open a terminal
- move to the project folder
- type `make` to build the executable `exe`
- `./exe.x`

### From command line:
- `$ g++ -o exe.x -Wall -Wextra -g -std=c++14 -I include main.cpp`
- then do ``./exe.x`

### To check memory leaks with [Valgrind](https://valgrind.org) and see the heap/leak summary:
- `valgrind ./exe.x --leaks-check=full`

The current version doesn't leak memory, as can be verified.

## Documentation
You can find a [Doxygen documentation](https://www.doxygen.nl/index.html) at: https://fdrmrc.github.io/Templated_Binary_Search_Tree/html/index.html

##Benchmarking

The natural competitor is [std::map](https://en.cppreference.com/w/cpp/container/map). The current implementation of `find()` for a balanced tree is faster than the one of `std::map`. [still in progress]
 
