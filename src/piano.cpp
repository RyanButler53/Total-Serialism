#include "piano.hpp"
#include "instrument.hpp"

using namespace std;

Piano::Piano(AnalysisMatrix *pitches, AnalysisMatrix *rhythms, AnalysisMatrix *articulations, std::vector<short> &dynamics, std::vector<Row> RHrows,std::vector<Row> LHrows) : 
    Instrument(pitches, rhythms, articulations, dynamics), RHrows_{RHrows}, LHrows_{LHrows} {};

void Piano::generateCode(vector<string>& lilypondCode){
    std::vector<string> rightCode;
    std::vector<string> leftCode;
    short leftover16ths = 16;
    string lilypondRow;
    // Generate Right then left in series (later in parallel)
    rightCode.push_back("right = \\fixed c'{\\clef treble \\global \n");
    for (size_t row = 0; row < 12; ++row){
        lilypondRow = rowToLilypond(RHrows_[row], dynamicsRow_[row], leftover16ths);
        rightCode.push_back(lilypondRow);
    }

    if (leftover16ths == 16 /*ts_.num16ths()*/){ // no leftover 16ths.
        rightCode.push_back("\n \\fine}\n");
    } else {
        string remainingPiece = fullDuration(leftover16ths, "", "r", "");
        rightCode.back().append(remainingPiece + "|\n \\fine}\n");
    }
    cout << leftover16ths << endl;
    leftover16ths = 16;
    leftCode.push_back("left = \\fixed c'{\\clef treble \\global \n");
    for (size_t row = 0; row < 12; ++row){
        lilypondRow = rowToLilypond(LHrows_[row], -1, leftover16ths);
        leftCode.push_back(lilypondRow);
    }

    if (leftover16ths == 16 /*ts_.num16ths()*/){ // no leftover 16ths.
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

string Piano::staffHeader(vector<string>& lilypondCode){
    return "right = \\fixed c'{\\clef treble \\global \n";
}