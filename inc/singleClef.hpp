#ifndef SINGLE_CLEF_HPP_INCLUDED
#define SINGLE_CLEF_HPP_INCLUDED

#include "instrument.hpp"

class SingleClefInstrument : public Instrument
{
  private:
    InstrumentData data_;
    std::vector<Row> rows_;

  public:
    SingleClefInstrument(InstrumentData data, std::vector<Row> rows);
    virtual ~SingleClefInstrument();

    void generateCode(std::vector<std::string> &lilypondCode);
};

#endif // SINGLE_CLEF_HPP_INCLUDED

