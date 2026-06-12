cmake_minimum_required(VERSION 3.16)

# Proyecto
project(PC3_Skyline_CC232 LANGUAGES CXX)

# Estándar C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# =========================
# Includes
# =========================
include_directories(include)

# =========================
# Librería principal
# =========================
add_library(skyline_lib
    src/Skyline.cpp
)

# =========================
# Main
# =========================
add_executable(pc3
    demos/main.cpp
)

target_link_libraries(pc3 skyline_lib)

# =========================
# Warnings
# =========================
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(pc3 PRIVATE -Wall -Wextra -Wpedantic)
    target_compile_options(tests_pc3 PRIVATE -Wall -Wextra -Wpedantic)
    target_compile_options(benchmark_pc3 PRIVATE -Wall -Wextra -Wpedantic)
endif()

# =========================
# Testing 
# =========================
enable_testing()

file(GLOB_RECURSE TEST_SOURCES tests/*.cpp)

if(TEST_SOURCES)
    add_executable(tests_pc3 ${TEST_SOURCES})

    target_link_libraries(tests_pc3 skyline_lib)

    target_include_directories(tests_pc3 PRIVATE include)

    add_test(NAME skyline_tests COMMAND tests_pc3)
endif()

# =========================
# Benchmark 
# =========================
file(GLOB_RECURSE BENCH_SOURCES benchmark/*.cpp)

if(BENCH_SOURCES)
    add_executable(benchmark_pc3 ${BENCH_SOURCES})
    target_include_directories(benchmark_pc3 PRIVATE include)
    target_link_libraries(benchmark_pc3 skyline_lib)

    if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        target_compile_options(benchmark_pc3 PRIVATE -O2)
    endif()
endif()

# =========================
# Organización de salida
# =========================

set_target_properties(pc3 PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

if(TARGET tests_pc3)
    set_target_properties(tests_pc3 PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    )
endif()