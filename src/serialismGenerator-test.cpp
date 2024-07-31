#include <iostream>
#include "serialismGenerator.hpp"
#include <gtest/gtest.h>
#include <string>

using namespace std;

// TEST(Generator, Duration){
//     SerialismGenerator randomGen{70};
//     std::string duration1 = randomGen.fullDuration(1, "", "a", "->");
//     std::string duration2 = randomGen.fullDuration(2, "", "a", "->-!");
//     std::string duration3 = randomGen.fullDuration(3, "", "cs", "-!");
//     std::string duration4 = randomGen.fullDuration(4, "", "a", "-_");
//     std::string duration5 = randomGen.fullDuration(5, "", "af", "--");
//     std::string duration6 = randomGen.fullDuration(6, "", "a", "->");
//     std::string duration7 = randomGen.fullDuration(7, "", "a", "");
//     std::string duration8 = randomGen.fullDuration(8, "", "cs", "-!");
//     std::string duration9 = randomGen.fullDuration(9, "", "bf", "-_");
//     std::string duration10 = randomGen.fullDuration(10, "", "af", "--");
//     std::string duration11 = randomGen.fullDuration(11, "", "a", "-_");
//     std::string duration12 = randomGen.fullDuration(12, "", "af", "--");

//     ASSERT_EQ(duration1, "a16->");
//     ASSERT_EQ(duration2, "a8->-!");
//     ASSERT_EQ(duration3, "cs8.-!");
//     ASSERT_EQ(duration4, "a4-_");
//     ASSERT_EQ(duration5, "af4--~af16");
//     ASSERT_EQ(duration6, "a4.->");
//     ASSERT_EQ(duration7, "a4..");
//     ASSERT_EQ(duration8, "cs2-!");
//     ASSERT_EQ(duration9, "bf2-_~bf16"); 
//     ASSERT_EQ(duration10, "af2--~af8"); 
//     ASSERT_EQ(duration11, "a2-_~a8."); 
//     ASSERT_EQ(duration12, "af2.--"); 
// }
