#include "instrumentFactory.hpp"

InstrumentFactory::InstrumentFactory(AnalysisMatrix *pitches, AnalysisMatrix *rhythms, AnalysisMatrix *articulations, TimeSignature ts) : 
data_{pitches, rhythms, articulations, ts}{}

SingleClefInstrument* InstrumentFactory::createInstrument(std::string name, std::vector<Row> rows, std::vector<short> dynamics, int num){
    if (name == "violin"){
        return new Violin(data_, rows, dynamics, num);
    } else if (name == "viola") {
        return new Viola(data_, rows, dynamics, num);
    } else if (name == "cello"){
        return new Cello(data_, rows, dynamics, num);
    } else if (name == "bass") {
        return new Bass(data_, rows, dynamics, num);
    } else if (name == "altosax") {
        return new AltoSax(data_, rows, dynamics, num);
    } else if (name == "tenorsax") {
        return new TenorSax(data_, rows, dynamics, num);
    } else if (name == "barisax") {
        return new BariSax(data_, rows, dynamics, num);
    } else if (name == "oboe") {
        return new Oboe(data_, rows, dynamics, num);
    } else if (name == "bassoon") {
        return new Bassoon(data_, rows, dynamics, num);
    } else if (name == "clarinet") {
        return new Clarinet(data_, rows, dynamics, num);
    } else if (name == "piccolo") {
        return new Piccolo(data_, rows, dynamics, num);
    } else if (name == "trombone") {
        return new Trombone(data_, rows, dynamics, num);
    } else if (name == "trumpet") {
        return new Trumpet(data_, rows, dynamics, num);
    } else if (name == "frenchhorn") {
        return new FrenchHorn(data_, rows, dynamics, num);
    } else if (name == "tuba") {
        return new Tuba(data_, rows, dynamics, num);
    } else if (name == "flute") {
        return new Flute(data_, rows, dynamics, num);
    } else {
        std::cerr << "Invalid Instrument" << std::endl;
        return nullptr;
    }
}
MultiClefInstrument* InstrumentFactory::createInstrument(std::string name, std::vector<Row> rhRows, std::vector<Row> lhRows, std::vector<short> dynamics, int num){
    if (name == "harp"){
        return new Harp(data_, rhRows, lhRows, dynamics, num);
    } else {
        return new Piano(data_, rhRows, lhRows, dynamics, num);
    }
}
