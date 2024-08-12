#ifndef INSTRUMENT_FACTORY_HPP_INCLUDED
#define INSTRUMENT_FACTORY_HPP_INCLUDED

#include "note.hpp"
#include "instrument.hpp"
#include "singleClef.hpp"
#include "multiClef.hpp"
#include "timeSignature.hpp"
#include <string> 
#include <memory>
/**
 * @brief Class to make instrument objects. Serialism Generator owns
 * one instance of this class which it uses to make instrument objects. 
 * 
 * Needs all the information to build the instruments. 
 */
class InstrumentFactory {
  private:  
    InstrumentData data_;

  public:
      InstrumentFactory() = default;
      InstrumentFactory(AnalysisMatrix *pitches, AnalysisMatrix *rhythms, AnalysisMatrix *articulations, std::vector<short> dynamics, TimeSignature ts);
      ~InstrumentFactory() = default;

      // Overload Create Instrument to handle single and multi clef instruments
      SingleClefInstrument *createInstrument(std::string instrumentName, std::vector<Row> rows);
      MultiClefInstrument *createInstrument(std::string instrumentName, std::vector<Row> rhRows, std::vector<Row> lhRows);
};

#endif // INSTRUMENT_FACTORY_HPP_INCUDED