cmake_minimum_required(VERSION 3.20)
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

set(GCC_UBSAN_COMPILE_FLAGS "-fsanitize=undefined -fsanitize=address")
set(GCC_UBSAN_LINK_FLAGS    "-fsanitize=undefined -fsanitize=address")

set(CMAKE_CXX_FLAGS "${GCC_UBSAN_COMPILE_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${GCC_UBSAN_LINK_FLAGS}")

include_directories(inc)

# Production
add_executable(
    totalSerialism 
    src/totalSerialism.cpp
    src/serialismGenerator.cpp
    src/analysisMatrix.cpp
    )

# Tests
add_executable(
    analysisMatrix-test 
    src/analysisMatrix-test.cpp
    src/analysisMatrix.cpp
    )

add_executable(
    serialismGenerator-test
    src/serialismGenerator-test.cpp
    src/serialismGenerator.cpp
    src/analysisMatrix.cpp
    )

target_link_libraries(
    analysisMatrix-test
    GTest::gtest_main
    )

target_link_libraries(
    serialismGenerator-test
    GTest::gtest_main
    )
    

include(GoogleTest)
gtest_discover_tests(analysisMatrix-test)
gtest_discover_tests(serialismGenerator-test)