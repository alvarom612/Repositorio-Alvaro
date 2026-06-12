cmake_minimum_required(VERSION 3.16)

project(PC3_Skyline_CC232)

# =========================
# Configuración general
# =========================
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# =========================
# Includes
# =========================
include_directories(include)

# =========================
# Fuente base del proyecto
# =========================
file(GLOB_RECURSE SOURCES src/*.cpp)

# =========================
# Demo principal
# =========================
add_executable(pc3 demos/main.cpp ${SOURCES})

# =========================
# Tests
# =========================
file(GLOB_RECURSE TEST_SOURCES tests/*.cpp)

if(TEST_SOURCES)
    add_executable(tests_pc3 ${TEST_SOURCES} ${SOURCES})
    target_include_directories(tests_pc3 PRIVATE include)

    enable_testing()
    add_test(NAME skyline_tests COMMAND tests_pc3)
endif()

# =========================
# Benchmark
# =========================
file(GLOB_RECURSE BENCH_SOURCES benchmark/*.cpp)

if(BENCH_SOURCES)
    add_executable(benchmark_pc3 ${BENCH_SOURCES} ${SOURCES})
    target_include_directories(benchmark_pc3 PRIVATE include)
    
  if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(benchmark_pc3 PRIVATE $<$<CONFIG:Release>:-O2>)
    elseif (MSVC)
    target_compile_options(benchmark_pc3 PRIVATE $<$<CONFIG:Release>:/O2>)
    endif()
endif()

# =========================
# Salida organizada
# =========================
set_target_properties(pc3 PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

if(TARGET tests_pc3)
    set_target_properties(tests_pc3 PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    )
endif()

if(TARGET benchmark_pc3)
    set_target_properties(benchmark_pc3 PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    )
endif()