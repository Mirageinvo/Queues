cmake_minimum_required(VERSION 3.16.3)
project(Queues_benchmark VERSION 1.0.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDART 20)

find_package(benchmark REQUIRED)

set(EXEC queues_benchmark)
set(RUN_EXEC run_${EXEC})
set(INCL_PATH "../includes/")

add_executable(${EXEC} ${EXEC}.cpp)
target_link_libraries(${EXEC} benchmark::benchmark)
target_include_directories(${EXEC} PUBLIC ${INCL_PATH})

add_custom_target(
    ${RUN_EXEC}
    COMMENT Running GoogleBenchmark for Queues
    COMMAND ./${EXEC}
)