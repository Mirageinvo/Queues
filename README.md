# The queues are implemented with two stacks or with a single linked list

In this project stacks have been taken from: https://github.com/Mirageinvo/Stack

### To build the project the following is needed to be done:

```
mkdir build && cd build/

\\to build tests with either queue implementations:\\
cmake .. && make

\\to add sanitizers to tests:\\
-DADD_SANITIZERS=1

\\or if user has Google Benchmark installed they can try:\\
-DBENCHMARK=1

\\to run tests for stack queue implementation:\\
make run_tests_for_stack_queue

\\to run tests for list queue implementation:\\
make run_tests_for_list_queue

\\to run Google Benchmark for either queue implementations(if only Google Benchmark is installed):\\
make run_queues_benchmark

\\to use clang format for all *.cpp and *hpp files:\\
make clang_format
```