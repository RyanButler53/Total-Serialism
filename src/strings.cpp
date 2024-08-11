#include "strings.hpp"

using namespace std;

Violin::Violin(InstrumentData data, std::vector<Row> rows) : 
SingleClefInstrument(data, rows){};

string Violin::staffHeader(){
    return "violin = \\fixed c''{\\clef treble \\global \n";
}
string Violin::scoreBox(){
    return "\n\t\\new Staff \\with {instrumentName = \"Violin\"} { \\violin }";
}

Viola::Viola(InstrumentData data, std::vector<Row> rows) : 
SingleClefInstrument(data, rows){};

string Viola::staffHeader(){
    return "viola = \\fixed c''{\\clef alto \\global \n";
}
string Viola::scoreBox(){
    return "\n\t\\new Staff \\with {instrumentName = \"Viola\"} { \\viola }";
}

Cello::Cello(InstrumentData data, std::vector<Row> rows) : 
SingleClefInstrument(data, rows){};

string Cello::staffHeader(){
    return "cello = \\fixed c{\\clef bass \\global \n";
}
string Cello::scoreBox(){
    return "\n\t\\new Staff \\with {instrumentName = \"Cello\"} { \\cello }";
}

Bass::Bass(InstrumentData data, std::vector<Row> rows) : 
SingleClefInstrument(data, rows){};

string Bass::staffHeader(){
    return "bass = \\fixed c{\\clef bass \\global \n";
}
string Bass::scoreBox(){
    return "\n\t\\new Staff \\with {instrumentName = \"String Bass\"} { \\bass }";
}