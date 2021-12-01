cmake_minimum_required(VERSION 3.16.3)
project(Tests_for_Queues VERSION 1.0.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDART 20)

set(EXEC_FILE_L tests_for_list_queue)
set(EXEC_FILE_S tests_for_stack_queue)
set(TEST_FILE_L run_${EXEC_FILE_L})
set(TEST_FILE_S run_${EXEC_FILE_S})
set(INCL_PATH "../Queues/includes/")

include(FetchContent)
FetchContent_Declare(googletest URL https://github.com/google/googletest/archive/release-1.10.0.tar.gz)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_definitions(-DLIST_IMPL)
add_executable(${EXEC_FILE_L} tests.cpp)
target_link_libraries(${EXEC_FILE_L} gtest_main)
target_include_directories(${EXEC_FILE_L} PUBLIC ${INCL_PATH})

include(GoogleTest)
gtest_discover_tests(${EXEC_FILE_L})

add_custom_target(
    ${TEST_FILE_L}
    COMMENT "Running tests for \"list\" queue"
    COMMAND ./${EXEC_FILE_L}
)
add_dependencies(${TEST_FILE_L} ${EXEC_FILE_L})

remove_definitions(-DLIST_IMPL)
add_definitions(-DSTACK_IMPL)
add_executable(${EXEC_FILE_S} tests.cpp)
target_link_libraries(${EXEC_FILE_S} gtest_main)
target_include_directories(${EXEC_FILE_S} PUBLIC ${INCL_PATH})

gtest_discover_tests(${EXEC_FILE_S})

add_custom_target(
    ${TEST_FILE_S}
    COMMENT "Running tests for \"stack\" queue"
    COMMAND ./${EXEC_FILE_S}
)
add_dependencies(${TEST_FILE_S} ${EXEC_FILE_S})

if (ADD_SANITIZERS)
    target_compile_options(${EXEC_FILE_L} PUBLIC -fsanitize=address -g)
    set_target_properties(${EXEC_FILE_L}  PROPERTIES LINK_FLAGS "-fsanitize=address")
    target_compile_options(${EXEC_FILE_S} PUBLIC -fsanitize=address -g)
    set_target_properties(${EXEC_FILE_S}  PROPERTIES LINK_FLAGS "-fsanitize=address")
endif()