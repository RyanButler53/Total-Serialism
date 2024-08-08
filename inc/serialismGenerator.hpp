#include <string>
#include <vector>
#include <random>
#include <array>
#include <mutex>
#include "instrumentFactory.hpp"
#include "timeSignature.hpp"
#include "analysisMatrix.hpp"
#include "instrument.hpp"
#include "piano.hpp"
#include "strings.hpp"
#include "woodwinds.hpp"
#include "brass.hpp"

#ifndef SERIALISM_GENERATOR_HPP_INCLUDED
#define SERIALISM_GENERATOR_HPP_INCLUDED

// The SerialismGenerator handles the "global" stuff while the 
// instruments handle the variable assignment. 

class SerialismGenerator
{
private:
    std::mt19937 rng_;
    std::normal_distribution<double> boulezDist_;
    std::mutex boulezMutex_;
    InstrumentFactory factory_;

    std::vector<short> dynamicsRow_;
    const std::vector<std::string> pitchMap_{"c","cs","d","ef","e","f","fs","g","af","a","bf","b"};
    const std::vector<std::string> articulationMap_{"->", "-^", "-_", "-!", "-.", "--", "->-.", "-^\\sfz", "", "->-!", "\\sfz", "-^-!"};
    const std::vector<std::string> dynamicMap_{"\\ppppp", "\\pppp", "\\ppp", "\\pp", "\\p", "\\mp", "\\mf", "\\f", "\\ff", "\\fff", "\\ffff", "\\fffff"};
    std::vector<std::string> instrumentList_{
        "piano", 
        "violin", "viola", "cello", "bass", 
        "oboe", "bassoon", "clarinet", "piccolo", "flute", 
        "trombone", "trumpet", "frenchhorn", "tuba"
    };

    TimeSignature ts_;
    std::string title_;
    std::string composer_;
    AnalysisMatrix *pitches_;
    AnalysisMatrix* rhythms_;
    AnalysisMatrix* articulations_;

    std::vector<Instrument*> instruments_;
    std::vector<std::string> instrumentNames_;
    std::vector<std::vector<Row>> instrumentRows_;

    long seed_;
    short tempo_;
    float boulezFactor_;

public:

    // Constructors
    SerialismGenerator();
    SerialismGenerator(long seed);
    SerialismGenerator(std::string inputfile);
    ~SerialismGenerator();

    void initializeRandom();

    void generatePiece(std::vector<std::string> &lilypondCode);

    std::string header();

    std::string boulezJitter();

    std::string scoreBox();
};

#endif
