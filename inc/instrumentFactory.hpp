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

    InstrumentFactory(std::shared_ptr<AnalysisMatrix> pitches, std::shared_ptr<AnalysisMatrix> rhythms, std::shared_ptr<AnalysisMatrix> articulations, TimeSignature ts, BoulezData boulezMutex);
    ~InstrumentFactory() = default;

    /**
     * @brief Create a SingleClef Instrument object.  
     * Overloaded to readibly allow for Single Clef and MultiClef instruments
     * 
     * @param instrumentName Instrument's name in params files an randomness lists
     * @param rows The rows for the whole piece. Doesn't need to be 12 rows long
     * @param dynamics The dynamics for each row. 
     * @param num Number of this instrument. Allows for Violin 1 and Violin 2 to have different parts. 
     * @return SingleClefInstrument* (shared)
     */
    std::shared_ptr<SingleClefInstrument> createInstrument(std::string instrumentName, std::vector<Row> rows, std::vector<short> dynamics, int num);
    
    /**
     * @brief Create a Instrument object. This is only for Piano and Harp
     * 
     * @param instrumentName Instrument name. 
     * @param rhRows Rows for the right hand
     * @param lhRows  Rows for left hand
     * @param dynamics Dynamics for each row. Dynamics are the same in each hand
     * @param num To allow for multiple pianos/harps. 
     * @return MultiClefInstrument* (shared)
     */
    std::shared_ptr<MultiClefInstrument> createInstrument(std::string instrumentName, std::vector<Row> rhRows, std::vector<Row> lhRows, std::vector<short> dynamics, int num);
};

#endif // INSTRUMENT_FACTORY_HPP_INCUDED