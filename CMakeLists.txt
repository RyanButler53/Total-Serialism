cmake_minimum_required(VERSION 3.31.0)
set(VERSION 1.1.0)
project(Total-Serialism)

set(CMAKE_CXX_STANDARD 23) # std:;println
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Address and Undefined behavior sanitizers for debug builds
add_compile_options($<$<CONFIG:Debug>:-fsanitize=address>)
add_link_options($<$<CONFIG:Debug>:-fsanitize=address>)

add_compile_options($<$<CONFIG:Debug>:-fsanitize=undefined>)
add_link_options($<$<CONFIG:Debug>:-fsanitize=undefined>)

option(TS_DO_TESTS "Build Tests" OFF)
option(WITH_PYTHON_BINDINGS "With Python Bindings" OFF)

add_subdirectory(src)
# Python bindings
if (WITH_PYTHON_BINDINGS)
  message(STATUS "Building Python Bindings")
  add_subdirectory(python_bindings)
endif()

# Tests
if(TS_DO_TESTS)
    message(STATUS "Building Tests")
    add_subdirectory(tests)
else()
    message(STATUS "Not building tests")
endif()

