#ifndef PIANO_HARP_HPP_INCLUDED
#define PIANO_HARP_HPP_INCLUDED

#include "instrument.hpp"
#include "note.hpp"
#include "multiClef.hpp"
#include "analysisMatrix.hpp"

class Piano : public MultiClefInstrument 
{
private:

    const Note lowerBound_ = Note("a", -3);
    const Note upperBound_ = Note("c", 4);

public:
    Piano(InstrumentData data, std::vector<Row> RhRows, std::vector<Row> LHRows, std::vector<short> dynamics,int num);
};

class Harp : public MultiClefInstrument 
{
private:

    const Note lowerBound_ = Note("c", -2);
    const Note upperBound_ = Note("g", 3);

public:
    Harp(InstrumentData data, std::vector<Row> RhRows, std::vector<Row> LHRows, std::vector<short> dynamics, int num);
};

#endif //PIANO_HARP_HPP_INCLUDED
