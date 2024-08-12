#include "instrumentFactory.hpp"

InstrumentFactory::InstrumentFactory(AnalysisMatrix *pitches, AnalysisMatrix *rhythms, AnalysisMatrix *articulations, std::vector<short> dynamics, TimeSignature ts) : 
data_{pitches, rhythms, articulations, dynamics, ts}{}

SingleClefInstrument* InstrumentFactory::createInstrument(std::string name, std::vector<Row> rows, int num){
    if (name == "violin"){
        return new Violin(data_, rows, num);
    } else if (name == "viola") {
        return new Viola(data_, rows, num);
    } else if (name == "cello"){
        return new Cello(data_, rows, num);
    } else if (name == "bass") {
        return new Bass(data_, rows, num);
    } else if (name == "altosax") {
        return new AltoSax(data_, rows, num);
    } else if (name == "tenorsax") {
        return new TenorSax(data_, rows, num);
    } else if (name == "barisax") {
        return new BariSax(data_, rows, num);
    } else if (name == "oboe") {
        return new Oboe(data_, rows, num);
    } else if (name == "bassoon") {
        return new Bassoon(data_, rows, num);
    } else if (name == "clarinet") {
        return new Clarinet(data_, rows, num);
    } else if (name == "piccolo") {
        return new Piccolo(data_, rows, num);
    } else if (name == "trombone") {
        return new Trombone(data_, rows, num);
    } else if (name == "trumpet") {
        return new Trumpet(data_, rows, num);
    } else if (name == "frenchhorn") {
        return new FrenchHorn(data_, rows, num);
    } else if (name == "tuba") {
        return new Tuba(data_, rows, num);
    } else if (name == "flute") {
        return new Flute(data_, rows, num);
    } else {
        std::cerr << "Invalid Instrument" << std::endl;
        return nullptr;
    }
}
MultiClefInstrument* InstrumentFactory::createInstrument(std::string name, std::vector<Row> rhRows, std::vector<Row> lhRows, int num){
    if (name == "harp"){
        return new Harp(data_, rhRows, lhRows, num);
    } else {
        return new Piano(data_, rhRows, lhRows,num);
    }
}
