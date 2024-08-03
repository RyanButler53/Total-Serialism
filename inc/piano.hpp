#ifndef PIANO_HPP_INCLUDED
#define PIANO_HPP_INCLUDED

#include "instrument.hpp"
#include "note.hpp"
#include "analysisMatrix.hpp"

class Piano : public Instrument 
{
private:

    std::vector<Row> RHrows_; // Rows for the entire piece
    std::vector<Row> LHrows_;
    const Note lowerBound_ = Note("a", -3); // use with boulez factor for clamping
    const Note upperBound_ = Note("c", 4);
    std::string instrumentName_ = "Piano";


public:
    Piano(AnalysisMatrix* pitches, AnalysisMatrix* rhythms, AnalysisMatrix* articulations, std::vector<short>& dynamics, TimeSignature ts, std::vector<Row> RhRows, std::vector<Row> LHRows);
    ~Piano() = default;

    // Pure virtual functions
    virtual void generateCode(std::vector<std::string>& lilypondCode);
    std::string staffHeader();
    std::string scoreBox();
};

#endif //PIANO_HPP_INCLUDED
