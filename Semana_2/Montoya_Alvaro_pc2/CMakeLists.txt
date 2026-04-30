cmake_minimum_required(VERSION 3.16)

project(apellido_nombre_pc2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(nqueens src/NQueensSolver.cpp)
target_include_directories(nqueens PUBLIC include)

add_executable(nqueens_demo demos/main.cpp)
target_link_libraries(nqueens_demo PRIVATE nqueens)

add_executable(nqueens_tests tests/test_nqueens.cpp)
target_link_libraries(nqueens_tests PRIVATE nqueens)

add_executable(nqueens_benchmark benchmark/benchmark_nqueens.cpp)
target_link_libraries(nqueens_benchmark PRIVATE nqueens)

add_library(actividad1_dynamic_array
    actividades/actividad1-CC232/src/DynamicArray.cpp
)
target_include_directories(actividad1_dynamic_array
    PUBLIC actividades/actividad1-CC232/include
)

add_executable(actividad1_tests
    actividades/actividad1-CC232/tests/test_dynamic_array.cpp
)
target_link_libraries(actividad1_tests PRIVATE actividad1_dynamic_array)

add_library(actividad2_linked_list
    actividades/actividad2-CC232/src/SimpleLinkedList.cpp
)
target_include_directories(actividad2_linked_list
    PUBLIC actividades/actividad2-CC232/include
)

add_executable(actividad2_tests
    actividades/actividad2-CC232/tests/test_simple_linked_list.cpp
)
target_link_libraries(actividad2_tests PRIVATE actividad2_linked_list)

add_library(actividad3_stack_tools
    actividades/actividad3-CC232/src/StackTools.cpp
)
target_include_directories(actividad3_stack_tools
    PUBLIC actividades/actividad3-CC232/include
)

add_executable(actividad3_tests
    actividades/actividad3-CC232/tests/test_stack_tools.cpp
)
target_link_libraries(actividad3_tests PRIVATE actividad3_stack_tools)

enable_testing()
add_test(NAME nqueens_tests COMMAND nqueens_tests)
add_test(NAME actividad1_tests COMMAND actividad1_tests)
add_test(NAME actividad2_tests COMMAND actividad2_tests)
add_test(NAME actividad3_tests COMMAND actividad3_tests)

