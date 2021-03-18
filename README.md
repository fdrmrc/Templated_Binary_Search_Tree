# Template Binary Search Tree [![Build Status](https://travis-ci.com/fdrmrc/Templated_Binary_Search_Tree.svg?branch=main)](https://travis-ci.com/github/fdrmrc/Templated_Binary_Search_Tree)

A C++ implementation of a Templated Binary Search Tree using smart pointers, tested with the GoogleTest framework. You can find a [Doxygen documentation](https://www.doxygen.nl/index.html) at: https://fdrmrc.github.io/Templated_Binary_Search_Tree/html/index.html


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






## Unit testing
To check the goodness of our functions, we used the testing framework [Google Test](https://github.com/google/googletest). In particular, we provide tests for the each one of the implemented classes. If you have Google Test installed on your machine, you can just use the `Makefile` provided in the unit_tests folder, or alternatively:

- ` g++  test_all.cpp -lgtest -lgtest_main -pthread -o test_all -std=c++14`
- `./test_all`

and the output will be something like the following:

```[==========] Running 21 tests from 4 test suites.
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

[----------] 6 tests from IteratorTests
[ RUN      ] IteratorTests.custom_constructor
[       OK ] IteratorTests.custom_constructor (0 ms)
[ RUN      ] IteratorTests.double_pre_increment
[       OK ] IteratorTests.double_pre_increment (0 ms)
[ RUN      ] IteratorTests.non_constness_check
[       OK ] IteratorTests.non_constness_check (0 ms)
[ RUN      ] IteratorTests.equality_check
[       OK ] IteratorTests.equality_check (0 ms)
[ RUN      ] IteratorTests.inequality_check
[       OK ] IteratorTests.inequality_check (0 ms)
[ RUN      ] IteratorTests.post_increment
[       OK ] IteratorTests.post_increment (0 ms)
[----------] 6 tests from IteratorTests (0 ms total)

[----------] 7 tests from TreeTests
[ RUN      ] TreeTests.insertion
[       OK ] TreeTests.insertion (0 ms)
[ RUN      ] TreeTests.copy_constructor
[       OK ] TreeTests.copy_constructor (0 ms)
[ RUN      ] TreeTests.copy_assignment
[       OK ] TreeTests.copy_assignment (0 ms)
[ RUN      ] TreeTests.move_constructor
[       OK ] TreeTests.move_constructor (0 ms)
[ RUN      ] TreeTests.move_assignment
[       OK ] TreeTests.move_assignment (0 ms)
[ RUN      ] TreeTests.emplace_test
[       OK ] TreeTests.emplace_test (0 ms)
[ RUN      ] TreeTests.balance_tests
[       OK ] TreeTests.balance_tests (0 ms)
[----------] 7 tests from TreeTests (0 ms total)

[----------] 3 tests from Tree_Tests
[ RUN      ] Tree_Tests.erasure_test_leaf_node
[       OK ] Tree_Tests.erasure_test_leaf_node (0 ms)
[ RUN      ] Tree_Tests.erasure_test_one_child
[       OK ] Tree_Tests.erasure_test_one_child (0 ms)
[ RUN      ] Tree_Tests.erasure_test_two_children
[       OK ] Tree_Tests.erasure_test_two_children (0 ms)
[----------] 3 tests from Tree_Tests (0 ms total)

[----------] Global test environment tear-down
[==========] 21 tests from 4 test suites ran. (0 ms total)
[  PASSED  ] 21 tests.
```

## Benchmarking

The natural competitor is [std::map](https://en.cppreference.com/w/cpp/container/map). The current implementation of `find()` for a balanced tree is faster than the one of `std::map`. The results and the plots can be found in the `Benchmark` folder.
 
