# The queues are implemented with two stacks or with a single linked list

In this project stacks have been taken from: https://github.com/Mirageinvo/Stack

### To build the project the following is needed to be done:

```
mkdir build && cd build/

\\to build tests with two-stacks-based queue:\\
cmake -DSTACK_IMPL=1 .. && make

\\to build test with single-linked-list-based queue:\\
cmake -DLIST_IMPL .. && make

\\to add sanitizers to tests:\\
-DADD_SANITIZERS=1

\\or if user has Google Benchmark installed they can try:\\
-DBENCHMARK=1

\\to use clang format for all *.cpp and *hpp files:\\
make clang_format
```