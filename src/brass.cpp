#include "brass.hpp"

using namespace std;

Trombone::Trombone(InstrumentData data, std::vector<Row> rows) : SingleClefInstrument(data, rows) {};

string Trombone::staffHeader(){
    return "trombone = \\fixed c''{\\clef treble \\global \n";
}
string Trombone::scoreBox(){
    std::string scoreBox = "\n\t\\new Staff \\with {instrumentName = \"";
    scoreBox += instrumentName_;
    scoreBox += "\"} { \\trombone }";
    return scoreBox;
}

Trumpet::Trumpet(InstrumentData data, std::vector<Row> rows) : SingleClefInstrument(data, rows) {};

string Trumpet::staffHeader(){
    return "trumpet = \\fixed c''{\\clef treble \\global \n";
}
string Trumpet::scoreBox(){
    std::string scoreBox = "\n\t\\new Staff \\with {instrumentName = \"";
    scoreBox += instrumentName_;
    scoreBox += "\"} { \\trumpet }";
    return scoreBox;
}

FrenchHorn::FrenchHorn(InstrumentData data, std::vector<Row> rows) : SingleClefInstrument(data, rows) {};

string FrenchHorn::staffHeader(){
    return "frenchhorn = \\fixed c''{\\clef treble \\global \n";
}
string FrenchHorn::scoreBox(){
    std::string scoreBox = "\n\t\\new Staff \\with {instrumentName = \"";
    scoreBox += instrumentName_;
    scoreBox += "\"} { \\frenchhorn }";
    return scoreBox;
}

Tuba::Tuba(InstrumentData data, std::vector<Row> rows) : SingleClefInstrument(data, rows) {};

string Tuba::staffHeader(){
    return "tuba = \\fixed c''{\\clef treble \\global \n";
}
string Tuba::scoreBox(){
    std::string scoreBox = "\n\t\\new Staff \\with {instrumentName = \"";
    scoreBox += instrumentName_;
    scoreBox += "\"} { \\tuba }";
    return scoreBox;
}
