#include "instrumentFactory.hpp"
#include "piano.hpp"
#include "strings.hpp"

InstrumentFactory::InstrumentFactory(AnalysisMatrix *pitches, AnalysisMatrix *rhythms, AnalysisMatrix *articulations, std::vector<short> dynamics, TimeSignature ts) : 
data_{pitches, rhythms, articulations, dynamics, ts}{}

Instrument* InstrumentFactory::createInstrument(std::string name, std::vector<Row> rows){
    if (name == "violin"){
        return new Violin(data_, rows);
    } else if (name == "viola")
    {
        return new Viola(data_, rows);
    } else if (name == "cello"){
        return new Cello(data_, rows);
    } else if (name == "bass")
    {
        return new Bass(data_, rows);
    } else {
        // Crash. 
        return nullptr;
    }
}
Instrument* InstrumentFactory::createInstrument(std::vector<Row> rhRows, std::vector<Row> lhRows){
    return new Piano(data_, rhRows, lhRows);
}
