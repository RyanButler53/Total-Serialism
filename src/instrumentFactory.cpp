#include "instrumentFactory.hpp"

InstrumentFactory::InstrumentFactory(std::shared_ptr<AnalysisMatrix> pitches, std::shared_ptr<AnalysisMatrix> rhythms, std::shared_ptr<AnalysisMatrix> articulations, TimeSignature ts, BoulezData boulez) : 
    data_{pitches, rhythms, articulations, ts}, boulez_{boulez}{
}

std::shared_ptr<SingleClefInstrument> InstrumentFactory::createInstrument(std::string name, std::vector<Row> rows, std::vector<short> dynamics, int num){
    if (name == "violin"){
        return std::make_shared<Violin>(data_, rows, dynamics, num, boulez_);
    } else if (name == "viola") {
        return std::make_shared<Viola>(data_, rows, dynamics, num, boulez_);
    } else if (name == "cello"){
        return std::make_shared<Cello>(data_, rows, dynamics, num, boulez_);
    } else if (name == "bass") {
        return std::make_shared<Bass>(data_, rows, dynamics, num, boulez_);
    } else if (name == "altosax") {
        return std::make_shared<AltoSax>(data_, rows, dynamics, num, boulez_);
    } else if (name == "tenorsax") {
        return std::make_shared<TenorSax>(data_, rows, dynamics, num, boulez_);
    } else if (name == "barisax") {
        return std::make_shared<BariSax>(data_, rows, dynamics, num, boulez_);
    } else if (name == "oboe") {
        return std::make_shared<Oboe>(data_, rows, dynamics, num, boulez_);
    } else if (name == "bassoon") {
        return std::make_shared<Bassoon>(data_, rows, dynamics, num, boulez_);
    } else if (name == "clarinet") {
        return std::make_shared<Clarinet>(data_, rows, dynamics, num, boulez_);
    } else if (name == "piccolo") {
        return std::make_shared<Piccolo>(data_, rows, dynamics, num, boulez_);
    } else if (name == "trombone") {
        return std::make_shared<Trombone>(data_, rows, dynamics, num, boulez_);
    } else if (name == "trumpet") {
        return std::make_shared<Trumpet>(data_, rows, dynamics, num, boulez_);
    } else if (name == "frenchhorn") {
        return std::make_shared<FrenchHorn>(data_, rows, dynamics, num, boulez_);
    } else if (name == "tuba") {
        return std::make_shared<Tuba>(data_, rows, dynamics, num, boulez_);
    } else if (name == "flute") {
        return std::make_shared<Flute>(data_, rows, dynamics, num, boulez_);
    } else {
        std::cerr << "Invalid Instrument" << std::endl;
        return nullptr;
    }
}

std::shared_ptr<MultiClefInstrument> InstrumentFactory::createInstrument(std::string name, std::vector<Row> rhRows, std::vector<Row> lhRows, std::vector<short> dynamics, int num){
    if (name == "harp"){
        return std::make_shared<Harp>(data_, rhRows, lhRows, dynamics, num, boulez_);
    } else {
        return std::make_shared<Piano>(data_, rhRows, lhRows, dynamics, num, boulez_);
    }
}
