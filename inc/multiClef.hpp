#ifndef MULTI_CLEF_HPP_INCLUDED
#define MULTI_CLEF_HPP_INCLUDED

#include "instrument.hpp"

class MultiClefInstrument : public Instrument
{
  private:
    InstrumentData data_;
    std::vector<Row> rhRows_;
    std::vector<Row> lhRows_;

  public:
    MultiClefInstrument(InstrumentData data, std::vector<Row> rhrows, std::vector<Row> lhrows);
    virtual ~MultiClefInstrument();

    void generateCode(std::vector<std::string> &lilypondCode);
};

#endif // MULTI_CLEF_HPP_INCLUDED