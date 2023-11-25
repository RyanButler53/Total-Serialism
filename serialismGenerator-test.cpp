#include <iostream>
#include "serialismGenerator.hpp"
#include <string>

using namespace std;
int main()
{
    cout << "Serialism Generator Tests" << endl;

    SerialismGenerator randomGen(70);
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
    
    assert(duration1 == "a16->" || (cout << "duration 1: " << duration1 << endl));
    assert(duration2 == "a8->-!" || (cout << "duration 2: " <<duration2 << endl));
    assert(duration3 == "cs8.-!" || (cout << "duration 3: " <<duration3 << endl));
    assert(duration4 == "a4-_" || (cout << "duration 4: " <<duration4 << endl));
    assert(duration5 == "af4--~af16" || (cout << "duration 5: " <<duration5 << endl));
    assert(duration6 == "a4.->" || (cout << "duration 6: " <<duration6 << endl));
    assert(duration7 == "a4.." || (cout << "duration 7: " <<duration7 << endl));
    assert(duration8 == "cs2-!" || (cout << "duration 8: " <<duration8 << endl));
    assert(duration9 == "bf2-_~bf16" || (cout << "duration 9: " <<duration9 << endl));
    assert(duration10 == "af2--~af8" || (cout << "duration 10: " <<duration10 << endl));
    assert(duration11 == "a2-_~a8." || (cout << "duration 11: " <<duration11 << endl));
    assert(duration12 == "af2.--" || (cout << "duration 12: " <<duration12 << endl));

    SerialismGenerator fileGen("test/test-in.txt");
    
}