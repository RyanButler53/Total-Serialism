#include "multiClef.hpp"

using namespace std;
MultiClefInstrument::MultiClefInstrument(InstrumentData data, MultiClefData MCdata) : 
                    Instrument(data),
                    rhRows_{MCdata.rhRows_},
                    lhRows_{MCdata.lhRows_},
                    displayName_{MCdata.displayName_},
                    variableName_{MCdata.variableName_},
                    num_{MCdata.num_}{
                        for (size_t i = 0; i < num_ - 1; ++i){
                            variableName_ += "X";
                        }
                    }


MultiClefInstrument::~MultiClefInstrument(){}

void MultiClefInstrument::generateCode(vector<string>& lilypondCode){
    std::vector<string> rightCode;
    std::vector<string> leftCode;
    short leftover16ths = ts_.num16ths();
    string lilypondRow;
    // Generate Right then left in series (later in parallel)

    string staffHeaders = staffHeader();
    size_t pos = staffHeaders.find("|");
    string rightHeader = staffHeaders.substr(0, pos);
    string leftHeader = staffHeaders.substr(pos+1);// +1 to skip | delimiter

    rightCode.push_back(rightHeader);
    for (size_t row = 0; row < 12; ++row){
        lilypondRow = rowToLilypond(rhRows_[row], dynamicsRow_[row], leftover16ths);
        rightCode.push_back(lilypondRow);
    }

    if (leftover16ths == ts_.num16ths()){ // no leftover 16ths.
        rightCode.push_back("\n \\fine}\n");
    } else {
        string remainingPiece = fullDuration(leftover16ths, "", "r", "");
        rightCode.back().append(remainingPiece + "|\n \\fine}\n");
    }
    // Reset and generate the left hand. 
    leftover16ths = ts_.num16ths();
    leftCode.push_back(leftHeader);
    for (size_t row = 0; row < 12; ++row){
        lilypondRow = rowToLilypond(lhRows_[row], -1, leftover16ths);
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

string MultiClefInstrument::staffHeader(){
    string header = variableName_ + "_right";
    header += " = \\fixed c''{\\clef treble \\global \n |";
    header += variableName_ + "_left";
    header += " = \\fixed c {\\clef bass \\global \n";
    return header;
}

// Variable names will look like rightXX_hand 
string MultiClefInstrument::scoreBox() {
    string scoreBox = "\t\\new PianoStaff \\with {instrumentName = \"";
    scoreBox += displayName_ +" "+ to_string(num_) + "\"} {\n\t\t<<";
    scoreBox += "\n\t\t\\new Staff {\\" + variableName_ + "_right"+ " }";
    scoreBox += "\n\t\t\\new Staff {\\" + variableName_ + "_left" + " }";
    scoreBox += " \n\t\t>>\n\t}\n";
    return scoreBox;
}