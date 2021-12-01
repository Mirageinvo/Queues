cmake_minimum_required(VERSION 3.16.3)
project(Queues VERSION 1.0.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDART 20)

add_compile_options (
    -Wall -Werror -Wextra -Wpedantic -Wcast-qual -Wcast-align -Wconversion
    -Wsign-promo -Wfloat-equal -Wenum-compare -Wold-style-cast -Wredundant-decls
    -Wnon-virtual-dtor -Woverloaded-virtual 
)

file(GLOB_RECURSE STACK_FILES *.cpp *.hpp)
add_custom_target(
    clang_format
    COMMAND clang-format -i ${STACK_FILES}
)

set(CMAKE_CXX_CLANG_TIDY
    clang-tidy;
    --format-style=file;
    --header-filter=*.hpp;
)

add_subdirectory("tests")

if (BENCHMARK)
    add_subdirectory("Queues/benchmark")
endif()