#ifndef CELLO_HPP_INCLUDED
#define CELLO_HPP_INCLUDED

#include "instrument.hpp"
#include "note.hpp"
#include "analysisMatrix.hpp"

class Cello : public Instrument
{
private:
    std::vector<Row> rows_;
    const Note lowerBound_ = Note("c", -1);
    const Note upperBound_ = Note("e", 3);
    std::string instrumentName_ = "Cello";

public:
    Cello(AnalysisMatrix* pitches, AnalysisMatrix* rhythms, AnalysisMatrix* articulations, std::vector<short>& dynamics, TimeSignature ts, std::vector<Row> rows);
    ~Cello() = default;

    virtual void generateCode(std::vector<std::string> &lilypondCode);
    std::string staffHeader();
    std::string scoreBox();
};

#endif // CELLO_HPP_INCLUDED