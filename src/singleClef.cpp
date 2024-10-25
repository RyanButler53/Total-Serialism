#include "singleClef.hpp"

using namespace std;
SingleClefInstrument::SingleClefInstrument(InstrumentData data, BoulezData boulez, SingleClefData SCdata, Range range): 
                    Instrument(data, boulez, range), 
                    rows_{SCdata.rows_},
                    displayName_{SCdata.displayName_}, 
                    variableName_{SCdata.variableName_}, 
                    shortName_{SCdata.shortName_},
                    dynamicsRow_{SCdata.dynamicsRow_},
                    clef_{SCdata.clef_}, 
                    octave_{SCdata.octave_},
                    num_{SCdata.num_}
                    {
                        for (size_t i = 0; i < num_ - 1; ++i){
                            variableName_ += "X"; //differentiate between names
                        }
                    }

SingleClefInstrument::~SingleClefInstrument(){}

std::vector<std::string> SingleClefInstrument::generateCode(){
    std::vector<std::string> lilypondCode;
    short leftover16ths = ts_.num16ths();
    string lilypondRow = staffHeader();
    lilypondCode.push_back(lilypondRow);

    // Generate the notes
    for (size_t row = 0; row < rows_.size(); ++row)
    {
        lilypondRow = rowToLilypond(rows_[row], dynamicsRow_[row], leftover16ths);
        lilypondCode.push_back(lilypondRow);
    }

    // Leftover 16ths in the piece
    if (leftover16ths == ts_.num16ths()){
        lilypondCode.push_back("\\fine}\n");
    } else {
        string remainingPiece = fullDuration(leftover16ths, "r", "");
        lilypondCode.back().append(remainingPiece + "\\fine}\n");
    }
    return lilypondCode;
}

std::string SingleClefInstrument::staffHeader() {
    string header = variableName_;
    header += " = \\fixed " + octave_ + "{\\clef " + clef_;
    header += " \\global \n";
    return header;
}

std::string SingleClefInstrument::instrumentScoreBox(bool specificPart) {
    string num = to_string(num_);
    string scoreBox = "\n\t\\new Staff \\with {instrumentName = \"";
    scoreBox += displayName_ + " " + to_string(num_) + "\"";
    if (!specificPart){ // If not in a specific part, add short instrument name
        scoreBox += " shortInstrumentName = \"" + shortName_ + " " + to_string(num_) + "\"";
    }
    scoreBox += "} { \\" + variableName_ + " }";

    return scoreBox;
}

std::string SingleClefInstrument::getName(){
    return displayName_;
}

int SingleClefInstrument::getNum(){
    return num_;
}
