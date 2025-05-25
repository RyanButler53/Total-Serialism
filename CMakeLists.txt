cmake_minimum_required(VERSION 3.24.0)
set(VERSION 1.0.1)
project(Total-Serialism)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

set(GCC_UBSAN_COMPILE_FLAGS "-fsanitize=undefined  -g") #-fsanitize=address
set(GCC_UBSAN_LINK_FLAGS    "-fsanitize=undefined" ) #-fsanitize=address"

set(CMAKE_CXX_FLAGS "${GCC_UBSAN_COMPILE_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${GCC_UBSAN_LINK_FLAGS}")

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

add_library(instrument ${INSTRUMENT_SRC})
add_library(serialism ${SERIALISM_SRC})
add_library(parallelism ${PARALLELISM_SRC})

# Tests
add_subdirectory(tests)

# Production
add_executable( TotalSerialism src/totalSerialism.cpp)

target_link_libraries(TotalSerialism instrument serialism parallelism)
