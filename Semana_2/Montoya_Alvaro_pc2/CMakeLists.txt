cmake_minimum_required(VERSION 3.16)

project(Montoya_Alvaro_pc2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(nqueens
    src/NQueensSolver.cpp
)

target_include_directories(nqueens
    PUBLIC
        include
)

add_executable(nqueens_demo
    demos/main.cpp
)

target_link_libraries(nqueens_demo
    PRIVATE
        nqueens
)

add_executable(nqueens_tests
    tests/test_nqueens.cpp
)

target_link_libraries(nqueens_tests
    PRIVATE
        nqueens
)

add_executable(nqueens_benchmark
    benchmark/benchmark_nqueens.cpp
)

target_link_libraries(nqueens_benchmark
    PRIVATE
        nqueens
)

enable_testing()

add_test(
    NAME nqueens_tests
    COMMAND nqueens_tests
)