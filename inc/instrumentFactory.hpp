#ifndef INSTRUMENT_FACTORY_HPP_INCLUDED
#define INSTRUMENT_FACTORY_HPP_INCLUDED

#include "note.hpp"
#include "instrument.hpp"
#include <string> 

// Instrument Factory

class InstrumentFactory {
    private: 
    AnalysisMatrix* pitches_;
    AnalysisMatrix* rhythms_;
    AnalysisMatrix* articulations;
    // std::vector<Row> rows;

    InstrumentFactory(AnalysisMatrix* pitches, AnalysisMatrix* rhythms, AnalysisMatrix* );
    ~InstrumentFactory() = default;

    Instrument createInstrument(std::string instrument, std::vector<Row> rows);
};

#endif