include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/52eb8108c5bdec04579160ae17225d66034bd723.zip
)

FetchContent_MakeAvailable(googletest)
include(GoogleTest)

macro(TotalSerialismTest testname src)
    add_executable(${testname} ${src})
    target_link_libraries(${testname} gtest gtest_main serialism ${ARGN})
    gtest_discover_tests(${testname})
    target_include_directories(${testname} PRIVATE ${PROJECT_SOURCE_DIR}/inc)
endmacro()


TotalSerialismTest(AnalysisMatrixTest analysisMatrix-test.cpp)
TotalSerialismTest(NoteTest note-test.cpp)
TotalSerialismTest(TimeSignatureTest timeSignature-test.cpp)
TotalSerialismTest(FuzzTest fuzzTest.cpp parallelism)
