cmake_minimum_required(VERSION 3.24.0)
project(Total-Serialism)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

set(GCC_UBSAN_COMPILE_FLAGS "-fsanitize=undefined -fsanitize=address -g")
set(GCC_UBSAN_LINK_FLAGS    "-fsanitize=undefined -fsanitize=address")

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

# Production
add_executable(
    TotalSerialism 
    src/totalSerialism.cpp
    ${SERIALISM_SRC}
    ${INSTRUMENT_SRC}
    ${PARALLELISM_SRC}
    )

# Tests
add_executable(
    analysisMatrix-test 
    src/analysisMatrix-test.cpp
    src/analysisMatrix.cpp
    )

add_executable(
    note-test 
    src/note-test.cpp
    src/note.cpp
    )

add_executable(
    timeSignature-test 
    src/timeSignature-test.cpp
    src/timeSignature.cpp
    )

# TESTING

# Unit Tests
target_link_libraries(
    analysisMatrix-test
    GTest::gtest_main
    )
    
target_link_libraries(
    timeSignature-test
    GTest::gtest_main
    )
target_link_libraries(
    note-test
    GTest::gtest_main
    )

include(GoogleTest)
gtest_discover_tests(analysisMatrix-test)
gtest_discover_tests(timeSignature-test)
gtest_discover_tests(note-test)

# Fuzz Test:
add_executable(
    fuzz
    src/fuzzTest.cpp
    ${SERIALISM_SRC}
    ${PARALLELISM_SRC}
    ${INSTRUMENT_SRC}
    )