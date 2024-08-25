#ifndef INSTRUMENT_FACTORY_HPP_INCLUDED
#define INSTRUMENT_FACTORY_HPP_INCLUDED

#include "note.hpp"
#include "instrument.hpp"
#include "singleClef.hpp"
#include "multiClef.hpp"
#include "timeSignature.hpp"
#include "instrumentDefinitions.hpp"
#include "pianoharp.hpp"
#include <string> 
#include <memory>
#include <thread>

/**
 * @brief Class to make instrument objects. Serialism Generator owns
 * one instance of this class which it uses to make instrument objects. 
 * 
 * Constains all the information to build the instruments and 
 * all the concurrency information to do a shared boulez distribution 
 */
class InstrumentFactory {
  private:  
    InstrumentData data_;
    BoulezData boulez_;

public:

    InstrumentFactory(AnalysisMatrix *pitches, AnalysisMatrix *rhythms, AnalysisMatrix *articulations, TimeSignature ts, BoulezData boulezMutex);
    ~InstrumentFactory() = default;

    // Overload Create Instrument to handle single and multi clef instruments
    SingleClefInstrument *createInstrument(std::string instrumentName, std::vector<Row> rows, std::vector<short> dynamics, int num);
    MultiClefInstrument *createInstrument(std::string instrumentName, std::vector<Row> rhRows, std::vector<Row> lhRows, std::vector<short> dynamics, int num);
};

#endif // INSTRUMENT_FACTORY_HPP_INCUDED