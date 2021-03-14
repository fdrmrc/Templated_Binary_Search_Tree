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
- `./exe.x` from command line

### From command line:
- `$ g++ -o exe.x -Wall -Wextra -g -std=c++14 -I include main.cpp`
- then do `./exe.x`

### To check memory leaks with [Valgrind](https://valgrind.org) and see the heap/leak summary:
- `valgrind ./exe.x --leaks-check=full`

The current version doesn't leak memory, as can be verified.

## Documentation
You can find a [Doxygen documentation](https://www.doxygen.nl/index.html) at: https://fdrmrc.github.io/Templated_Binary_Search_Tree/html/index.html




## Unit testing
To check the goodness of our functions, we used the testing framework [Google Test](https://github.com/google/googletest). In particular, we provide tests for the each one of the implemented classes. If you have Google Test installed on your machine, and for instance you want to compile and run the tests for the Node class, just type from command line:

- ` g++  NodeTesting.cpp -lgtest -lgtest_main -pthread -o NodeTesting -std=c++14`

and the output will be something like the following:

```[==========] Running 5 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 5 tests from nodeTesting
[ RUN      ] nodeTesting.Node_Default_Constructor
[       OK ] nodeTesting.Node_Default_Constructor (0 ms)
[ RUN      ] nodeTesting.Node_Custom_Constructor_integers
[       OK ] nodeTesting.Node_Custom_Constructor_integers (0 ms)
[ RUN      ] nodeTesting.Node_Custom_Constructor_strings
[       OK ] nodeTesting.Node_Custom_Constructor_strings (0 ms)
[ RUN      ] nodeTesting.Node_Constructor_With_Parent
[       OK ] nodeTesting.Node_Constructor_With_Parent (0 ms)
[ RUN      ] nodeTesting.Multiple_Nodes
[       OK ] nodeTesting.Multiple_Nodes (0 ms)
[----------] 5 tests from nodeTesting (0 ms total)

[----------] Global test environment tear-down
[==========] 5 tests from 1 test suite ran. (0 ms total)
[  PASSED  ] 5 tests
```



You can test in a similar fashion also the other tests in the unit_tests folder.

## Benchmarking

The natural competitor is [std::map](https://en.cppreference.com/w/cpp/container/map). The current implementation of `find()` for a balanced tree is faster than the one of `std::map`. [still in progress]
 
