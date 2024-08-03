#include "cello.hpp"

using namespace std;
Cello::Cello(AnalysisMatrix *pitches, AnalysisMatrix *rhythms, AnalysisMatrix *articulations, std::vector<short> &dynamics, TimeSignature ts, std::vector<Row> rows) : 
Instrument(pitches, rhythms, articulations, dynamics, ts), rows_{rows} {};

void Cello::generateCode(vector<string>& lilypondCode){
    short leftover16ths = ts_.num16ths();
    string lilypondRow = staffHeader();
    lilypondCode.push_back(lilypondRow);
    for (size_t row = 0; row < 12; ++row)
    {
        lilypondRow = rowToLilypond(rows_[row], dynamicsRow_[row], leftover16ths);
        lilypondCode.push_back(lilypondRow);
    }

    // Leftover 16ths in the piece
    if (leftover16ths == ts_.num16ths()){
        lilypondCode.push_back("\n \\fine}\n");
    } else {
        string remainingPiece = fullDuration(leftover16ths, "", "r", "");
        lilypondCode.back().append(remainingPiece + "|\n \\fine}\n");
    }
}

string Cello::staffHeader(){
    return "cello = \\fixed c{\\clef bass \\global \n";
}
string Cello::scoreBox(){
    return "\n\t\\new Staff \\with {instrumentName = \"Cello\"} { \\cello }";
}