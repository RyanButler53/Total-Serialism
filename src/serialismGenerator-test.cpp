#include <iostream>
#include "serialismGenerator.hpp"
#include <gtest/gtest.h>
#include <string>

using namespace std;

TEST(Generator, Duration){
    SerialismGenerator randomGen{70};
    std::string duration1 = randomGen.fullDuration(1, "a", "->");
    std::string duration2 = randomGen.fullDuration(2, "a", "->-!");
    std::string duration3 = randomGen.fullDuration(3, "cs", "-!");
    std::string duration4 = randomGen.fullDuration(4, "a", "-_");
    std::string duration5 = randomGen.fullDuration(5, "af", "--");
    std::string duration6 = randomGen.fullDuration(6, "a", "->");
    std::string duration7 = randomGen.fullDuration(7, "a", "");
    std::string duration8 = randomGen.fullDuration(8, "cs", "-!");
    std::string duration9 = randomGen.fullDuration(9, "bf", "-_");
    std::string duration10 = randomGen.fullDuration(10, "af", "--");
    std::string duration11 = randomGen.fullDuration(11, "a", "-_");
    std::string duration12 = randomGen.fullDuration(12, "af", "--");

    ASSERT_EQ(duration1, "a16->");  //|| (cout << "duration 1: " << duration1 << endl));
    ASSERT_EQ(duration2, "a8->-!"); // || (cout << "duration 2: " <<duration2 << endl));
    ASSERT_EQ(duration3, "cs8.-!"); // || (cout << "duration 3: " <<duration3 << endl));
    ASSERT_EQ(duration4, "a4-_"); // || (cout << "duration 4: " <<duration4 << endl));
    ASSERT_EQ(duration5, "af4--~af16"); // || (cout << "duration 5: " <<duration5 << endl));
    ASSERT_EQ(duration6, "a4.->");    // || (cout << "duration 6: " <<duration6 << endl));
    ASSERT_EQ(duration7, "a4..");       // || (cout << "duration 7: " <<duration7 << endl));
    ASSERT_EQ(duration8, "cs2-!");      //|| (cout << "duration 8: " <<duration8 << endl));
    ASSERT_EQ(duration9, "bf2-_~bf16"); // || (cout << "duration 9: " <<duration9 << endl));
    ASSERT_EQ(duration10, "af2--~af8"); // || (cout << "duration 10: " <<duration10 << endl));
    ASSERT_EQ(duration11, "a2-_~a8."); // || (cout << "duration 11: " <<duration11 << endl));
    ASSERT_EQ(duration12, "af2.--"); // || (cout << "duration 12: " <<duration12 << endl));
}

TEST(Generator, FileGen){
    SerialismGenerator fileGen("test/test-in.txt");
    string rowP0 = fileGen.rowToLilypond(Row(P, 0), 5);
    string P0row = "c16-- \\mp cs8-- d8.-- ef4-- e8.--~ | e8 f4.-- fs4--~fs16~ | fs8 g2-- af8.--~ | af4. a4..--~ | a8. bf2--~bf8~ | bf16 b2.-- | \n";
    ASSERT_EQ(rowP0, P0row);
}

// int main()
// {
//     cout << "Serialism Generator Tests" << endl;

//     SerialismGenerator randomGen(70);
//     std::string duration1 = randomGen.fullDuration(1, "a", "->");
//     std::string duration2 = randomGen.fullDuration(2, "a", "->-!");
//     std::string duration3 = randomGen.fullDuration(3, "cs", "-!");
//     std::string duration4 = randomGen.fullDuration(4, "a", "-_");
//     std::string duration5 = randomGen.fullDuration(5, "af", "--");
//     std::string duration6 = randomGen.fullDuration(6, "a", "->");
//     std::string duration7 = randomGen.fullDuration(7, "a", "");
//     std::string duration8 = randomGen.fullDuration(8, "cs", "-!");
//     std::string duration9 = randomGen.fullDuration(9, "bf", "-_");
//     std::string duration10 = randomGen.fullDuration(10, "af", "--");
//     std::string duration11 = randomGen.fullDuration(11, "a", "-_");
//     std::string duration12 = randomGen.fullDuration(12, "af", "--");
    
//     assert(duration1 == "a16->" || (cout << "duration 1: " << duration1 << endl));
//     assert(duration2 == "a8->-!" || (cout << "duration 2: " <<duration2 << endl));
//     assert(duration3 == "cs8.-!" || (cout << "duration 3: " <<duration3 << endl));
//     assert(duration4 == "a4-_" || (cout << "duration 4: " <<duration4 << endl));
//     assert(duration5 == "af4--~af16" || (cout << "duration 5: " <<duration5 << endl));
//     assert(duration6 == "a4.->" || (cout << "duration 6: " <<duration6 << endl));
//     assert(duration7 == "a4.." || (cout << "duration 7: " <<duration7 << endl));
//     assert(duration8 == "cs2-!" || (cout << "duration 8: " <<duration8 << endl));
//     assert(duration9 == "bf2-_~bf16" || (cout << "duration 9: " <<duration9 << endl));
//     assert(duration10 == "af2--~af8" || (cout << "duration 10: " <<duration10 << endl));
//     assert(duration11 == "a2-_~a8." || (cout << "duration 11: " <<duration11 << endl));
//     assert(duration12 == "af2.--" || (cout << "duration 12: " <<duration12 << endl));

//     SerialismGenerator fileGen("test/test-in.txt");
//     string rowP0 = fileGen.rowToLilypond(Row(P, 0), 5);
//     string P0row = "c16-- \\mp cs8-- d8.-- ef4-- e8.--~ | e8 f4.-- fs4--~fs16~ | fs8 g2-- af8.--~ | af4. a4..--~ | a8. bf2--~bf8~ | bf16 b2.-- | \n";
//     //"c16 \\mp cs8 d8. ef4 e8.~ | e8 f4. fs4~fs16~ | fs8 g2 af8.~ | af4. a4..~ | a8. bf2~bf8~ | bf16 b2. | \n";

//     assert(rowP0 == P0row || (cout << rowP0 << endl));
//     cout << "All tests pass" << endl;
// }