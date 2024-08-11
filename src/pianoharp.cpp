#include "pianoharp.hpp"
#include "instrument.hpp"

using namespace std;

Piano::Piano(InstrumentData data, std::vector<Row> RHrows,std::vector<Row> LHrows) : 
    MultiClefInstrument(data, RHrows, LHrows) {};


// Piano class is different and staffHeader isn't useful for it. 
string Piano::staffHeader(){
    return "piano_right = \\fixed c''{\\clef treble \\global \n |piano_left = \\fixed c{\\clef bass \\global \n";
}

string Piano::scoreBox(){
    string scoreBox = "\t\\new PianoStaff \\with {instrumentName = \"Piano\"} {\n\t\t<<";
    scoreBox += "\n\t\t\\new Staff {\\piano_right }\n\t\t\\new Staff {\\piano_left } \n\t\t>>\n\t}\n";
    return scoreBox;
}

Harp::Harp(InstrumentData data, std::vector<Row> RHrows,std::vector<Row> LHrows) : 
    MultiClefInstrument(data, RHrows, LHrows) {};


// Piano class is different and staffHeader isn't useful for it. 
string Harp::staffHeader(){
    return "harp_right = \\fixed c''{\\clef treble \\global \n |harp_left = \\fixed c{\\clef treble \\global \n";
}

string Harp::scoreBox(){
    string scoreBox = "\t\\new PianoStaff \\with {instrumentName = \"Harp\"} {\n\t\t<<";
    scoreBox += "\n\t\t\\new Staff {\\harp_right }\n\t\t\\new Staff {\\harp_left } \n\t\t>>\n\t}\n";
    return scoreBox;
}

