cmake_minimum_required(VERSION 3.31.0)
set(VERSION 1.0.1)
project(Total-Serialism)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

string(TOUPPER ${CMAKE_BUILD_TYPE} buildType)
if (buildType STREQUAL "DEBUG")
    add_compile_options(-fsanitize=address)
    add_link_options(-fsanitize=address)

    add_compile_options(-fsanitize=undefined)
    add_link_options(-fsanitize=undefined)
    message("-- Debug Mode: Enabling address and undefined behavior sanitizers")
endif()

option(TS_DO_TESTS "Build Tests" OFF)

set(INSTRUMENT_SRC 
    src/instrumentFactory.cpp
    src/instrument.cpp
    src/singleClef.cpp
    src/multiClef.cpp
    src/instrumentDefinitions.cpp
    src/pianoharp.cpp)

set (SERIALISM_SRC
    src/serialismGenerator.cpp
    src/analysisMatrix.cpp
    src/timeSignature.cpp
    src/note.cpp
    )

set (PARALLELISM_SRC
    src/joinThreads.cpp
    src/threadPool.cpp)

include_directories(inc)

add_library(serialism ${INSTRUMENT_SRC} ${SERIALISM_SRC})
add_library(parallelism ${PARALLELISM_SRC})


# Tests
if(TS_DO_TESTS)
    message("-- Building Tests")
    add_subdirectory(tests)
else()
    message("-- Not building tests")
endif()

# Production
add_executable( TotalSerialism src/totalSerialism.cpp)

target_link_libraries(TotalSerialism serialism parallelism)
