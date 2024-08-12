#ifndef MULTI_CLEF_HPP_INCLUDED
#define MULTI_CLEF_HPP_INCLUDED

#include "instrument.hpp"

struct MultiClefData{
    std::vector<Row> rhRows_;
    std::vector<Row> lhRows_;
    std::string displayName_;
    std::string variableName_; 
    int num_;
};

class MultiClefInstrument : public Instrument
{
  private:
    std::vector<Row> rhRows_;
    std::vector<Row> lhRows_;
    std::string variableName_;
    std::string displayName_;
    int num_;

  public:
    MultiClefInstrument(InstrumentData data, MultiClefData MCdata);
    virtual ~MultiClefInstrument();

    void generateCode(std::vector<std::string> &lilypondCode);
    std::string staffHeader();
    std::string  scoreBox();
};

#endif // MULTI_CLEF_HPP_INCLUDED