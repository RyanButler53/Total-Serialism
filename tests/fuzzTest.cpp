#include "serialismGenerator.hpp"
#include <iostream>
#include <string>
#include <stddef.h>
#include <filesystem>
#include <fstream>
#include <vector>
#include <gtest/gtest.h>
#include <format>

class FuzzTest : public testing::Test, public testing::WithParamInterface<long> {

    void TearDown() override {
        long s = GetParam();
        std::string folder = std::format("fuzz{}", s);
        if (std::filesystem::exists(folder)){
            std::filesystem::remove_all(folder);
        }
    }
};

TEST_P(FuzzTest, NoWarnings){
    long s = GetParam();

    std::filesystem::create_directories(std::format("fuzz{}", s));
    std::string filename = std::format("fuzz{}/{}.ly", s, s);
    std::string lpCommand  = std::format("lilypond -f pdf -o fuzz{} -l WARN fuzz{}/{}.ly 2>fuzz{}/err.txt", s, s, s, s);
    SerialismGenerator gen = SerialismGenerator(s, filename, 1);
    gen.run();
    std::system(lpCommand.data());

    // Evaluate for no error
    std::string err = std::format("fuzz{}/err.txt", s);
    if (std::filesystem::exists(err) && !std::filesystem::is_empty(err)){
        FAIL() << std::format("Lilypond error found in {}. Reproduce with sh score.sh {}", err, s);
    }

}

INSTANTIATE_TEST_SUITE_P(NoLilypondErrors,
    FuzzTest,
    testing::Values(5, 35, 60, 70, 81, 105, 131, 133, 140, 181));
