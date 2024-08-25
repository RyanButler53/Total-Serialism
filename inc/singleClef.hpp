#ifndef SINGLE_CLEF_HPP_INCLUDED
#define SINGLE_CLEF_HPP_INCLUDED

#include "instrument.hpp"
#include <string>
#include "note.hpp"

struct SingleClefData
{
    std::vector<Row> rows_;
    std::string displayName_;
    std::string variableName_;
    std::vector<short> dynamicsRow_;
    std::string clef_;
    std::string octave_;
    int num_;
};


class SingleClefInstrument : public Instrument
{
  private:
    std::vector<Row> rows_;
    std::string displayName_;
    std::string variableName_;
    std::vector<short> dynamicsRow_;
    std::string clef_;
    std::string octave_;
    int num_;

  public:
    SingleClefInstrument(InstrumentData data, BoulezData boulez, SingleClefData SCdata, Range r);
    virtual ~SingleClefInstrument();
    void generateCode(std::vector<std::string> &lilypondCode);
    std::string staffHeader();
    std::string scoreBox();
};

#endif
