#ifndef PIANO_HARP_HPP_INCLUDED
#define PIANO_HARP_HPP_INCLUDED

#include "instrument.hpp"
#include "note.hpp"
#include "multiClef.hpp"
#include "analysisMatrix.hpp"

class Piano : public MultiClefInstrument  {
  public:
    Piano(InstrumentData data, std::vector<Row> RhRows, std::vector<Row> LHRows, std::vector<short> dynamics,int num, BoulezData boulez);
};

class Harp : public MultiClefInstrument {
  public:
    Harp(InstrumentData data, std::vector<Row> RhRows, std::vector<Row> LHRows, std::vector<short> dynamics, int num, BoulezData boulez);
};

#endif //PIANO_HARP_HPP_INCLUDED
