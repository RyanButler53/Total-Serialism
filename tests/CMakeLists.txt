include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/52eb8108c5bdec04579160ae17225d66034bd723.zip
)

FetchContent_MakeAvailable(googletest)
include(GoogleTest)

macro(TotalSerialismTest testname src)
    message(${testname})
    message(${src})
    add_executable(${testname} ${src})
    target_link_libraries(${testname} gtest ${ARGN})
    gtest_discover_tests(${testname})
endmacro()


TotalSerialismTest(AnalysisMatrixTest analysisMatrix-test.cpp serialism)
TotalSerialismTest(NoteTest note-test.cpp serialism)
TotalSerialismTest(TimeSignatureTest timeSignature-test.cpp serialism)

add_executable(fuzz fuzzTest.cpp)
target_link_libraries(fuzz serialism parallelism instrument)