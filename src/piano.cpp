#include "piano.hpp"
#include "instrument.hpp"

using namespace std;

Piano::Piano(AnalysisMatrix *pitches, AnalysisMatrix *rhythms, AnalysisMatrix *articulations, std::vector<short> &dynamics, TimeSignature ts, std::vector<Row> RHrows,std::vector<Row> LHrows) : 
    Instrument(pitches, rhythms, articulations, dynamics, ts), RHrows_{RHrows}, LHrows_{LHrows} {};

void Piano::generateCode(vector<string>& lilypondCode){
    std::vector<string> rightCode;
    std::vector<string> leftCode;
    short leftover16ths = ts_.num16ths();
    string lilypondRow;
    // Generate Right then left in series (later in parallel)
    rightCode.push_back("right = \\fixed c'{\\clef treble \\global \n");
    for (size_t row = 0; row < 12; ++row){
        lilypondRow = rowToLilypond(RHrows_[row], dynamicsRow_[row], leftover16ths);
        rightCode.push_back(lilypondRow);
    }

    if (leftover16ths == ts_.num16ths()){ // no leftover 16ths.
        rightCode.push_back("\n \\fine}\n");
    } else {
        string remainingPiece = fullDuration(leftover16ths, "", "r", "");
        rightCode.back().append(remainingPiece + "|\n \\fine}\n");
    }
    leftover16ths = ts_.num16ths();
    leftCode.push_back("left = \\fixed c'{\\clef treble \\global \n");
    for (size_t row = 0; row < 12; ++row){
        lilypondRow = rowToLilypond(LHrows_[row], -1, leftover16ths);
        leftCode.push_back(lilypondRow);
    }

    if (leftover16ths == ts_.num16ths()){ // no leftover 16ths.
        leftCode.push_back("\n \\fine}\n");
    } else {
        string remainingPiece = fullDuration(leftover16ths, "", "r", "");
        leftCode.back().append(remainingPiece + "|\n \\fine}\n");
    }

    for (auto& l : rightCode){
        lilypondCode.push_back(l);
    }
    for (auto& l : leftCode){
        lilypondCode.push_back(l);
    }
}

// Piano class is different and staffHeader isn't useful for it. 
string Piano::staffHeader(){
    return "right = \\fixed c'{\\clef treble \\global \n";
}

string Piano::scoreBox(){
    string scoreBox = "\t\\new PianoStaff \\with {instrumentName = \"Piano\"} {\n\t\t<<";
    scoreBox += "\n\t\t\\new Staff {\\right }\n\t\t\\new Staff {\\left } \n\t\t>>\n\t}\n";
    return scoreBox;
}