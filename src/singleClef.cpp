#include "singleClef.hpp"

using namespace std;
SingleClefInstrument::SingleClefInstrument(InstrumentData data, std::vector<Row> rows) : 
                    Instrument(data), rows_{rows} {}

SingleClefInstrument::~SingleClefInstrument(){}

void SingleClefInstrument::generateCode(vector<string>& lilypondCode){
    short leftover16ths = ts_.num16ths();
    string lilypondRow = staffHeader();
    lilypondCode.push_back(lilypondRow);
    
    // Generate the notes
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