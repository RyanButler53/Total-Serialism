#include "woodwinds.hpp"

using namespace std;

AltoSax::AltoSax(InstrumentData data, std::vector<Row> rows) : SingleClefInstrument(data, rows) {};

string AltoSax::staffHeader(){
    return "altosax = \\fixed c''{\\clef treble \\global \n";
}
string AltoSax::scoreBox(){
    std::string scoreBox = "\n\t\\new Staff \\with {instrumentName = \"";
    scoreBox += instrumentName_;
    scoreBox += "\"} { \\altosax }";
    return scoreBox;
}

TenorSax::TenorSax(InstrumentData data, std::vector<Row> rows) : SingleClefInstrument(data, rows) {};

string TenorSax::staffHeader(){
    return "tenorsax = \\fixed c''{\\clef treble \\global \n";
}
string TenorSax::scoreBox(){
    std::string scoreBox = "\n\t\\new Staff \\with {instrumentName = \"";
    scoreBox += instrumentName_;
    scoreBox += "\"} { \\tenorsax }";
    return scoreBox;
}

BariSax::BariSax(InstrumentData data, std::vector<Row> rows) : SingleClefInstrument(data, rows) {};

string BariSax::staffHeader(){
    return "barisax = \\fixed c''{\\clef treble \\global \n";
}
string BariSax::scoreBox(){
    std::string scoreBox = "\n\t\\new Staff \\with {instrumentName = \"";
    scoreBox += instrumentName_;
    scoreBox += "\"} { \\barisax }";
    return scoreBox;
}

Oboe::Oboe(InstrumentData data, std::vector<Row> rows) : SingleClefInstrument(data, rows) {};

string Oboe::staffHeader(){
    return "oboe = \\fixed c''{\\clef treble \\global \n";
}
string Oboe::scoreBox(){
    std::string scoreBox = "\n\t\\new Staff \\with {instrumentName = \"";
    scoreBox += instrumentName_;
    scoreBox += "\"} { \\oboe }";
    return scoreBox;
}

Bassoon::Bassoon(InstrumentData data, std::vector<Row> rows) : SingleClefInstrument(data, rows) {};

string Bassoon::staffHeader(){
    return "bassoon = \\fixed c''{\\clef treble \\global \n";
}
string Bassoon::scoreBox(){
    std::string scoreBox = "\n\t\\new Staff \\with {instrumentName = \"";
    scoreBox += instrumentName_;
    scoreBox += "\"} { \\bassoon }";
    return scoreBox;
}

Clarinet::Clarinet(InstrumentData data, std::vector<Row> rows) : SingleClefInstrument(data, rows) {};

string Clarinet::staffHeader(){
    return "clarinet = \\fixed c''{\\clef treble \\global \n";
}
string Clarinet::scoreBox(){
    std::string scoreBox = "\n\t\\new Staff \\with {instrumentName = \"";
    scoreBox += instrumentName_;
    scoreBox += "\"} { \\clarinet }";
    return scoreBox;
}

Piccolo::Piccolo(InstrumentData data, std::vector<Row> rows) : SingleClefInstrument(data, rows) {};

string Piccolo::staffHeader(){
    return "piccolo = \\fixed c''{\\clef treble \\global \n";
}
string Piccolo::scoreBox(){
    std::string scoreBox = "\n\t\\new Staff \\with {instrumentName = \"";
    scoreBox += instrumentName_;
    scoreBox += "\"} { \\piccolo }";
    return scoreBox;
}

Flute::Flute(InstrumentData data, std::vector<Row> rows) : SingleClefInstrument(data, rows) {};

string Flute::staffHeader(){
    return "flute = \\fixed c''{\\clef treble \\global \n";
}
string Flute::scoreBox(){
    std::string scoreBox = "\n\t\\new Staff \\with {instrumentName = \"";
    scoreBox += instrumentName_;
    scoreBox += "\"} { \\flute }";
    return scoreBox;
}