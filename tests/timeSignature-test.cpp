#include <iostream>
#include "timeSignature.hpp"
#include <gtest/gtest.h>

TEST(isValid, validSignatures){

    std::vector < std::string > times{
                                     "1/4","3/8", "2/4", "5/8",
                                     "3/4", "7/4", "15/8","13/8",
                                     "6/8", "12/8", "6/4", "3/2",
                                     "7/8", "4/4", "9/8", "5/4", "11/8"
                                 };
    for (const auto& timesig : times){
        TimeSignature ts(timesig);
        ASSERT_TRUE(ts.isValid());
    }
}

TEST(isValid, invalidSignatures ){
        std::vector < std::string > times2{
                                     "1/3","1/8", "9/4", "0/8",
                                     "-3/4", "6/2", "4/2","4/8",
                                     "6/9", "11/4", "10/4", "10/2",
                                     "7/16", "2/16", "3/16", "9/1"
                                 };

    for (const auto& timesig : times2){
        TimeSignature ts(timesig);
        ASSERT_FALSE(ts.isValid());
    }
}

int main(int argc, char** argv) {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}