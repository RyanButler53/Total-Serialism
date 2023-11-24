#include <string>
#include <vector>
#include <random>
#include "analysisMatrix.hpp"

class SerialismGenerator
{
private:
    std::mt19937 rng_;
    std::vector<Row> rhRows_;
    std::vector<Row> lhRows_;
    std::vector<short> dynamicsRow_;
    const std::vector<std::string> pitchMap_{"c,cs,d,ef,e,f,fs,g,af,a,bf,b"};
    const std::vector<std::string> articulationMap_{"->", "-^", "-_", "-!", "-.", "--", "->-.", "-^\\sfz", " ", "->-!", "\\sfz", "-^-!"};
    const std::vector<std::string> dynamicMap_;
    AnalysisMatrix *pitches_;
    AnalysisMatrix* rhythms_;
    AnalysisMatrix* articulations_;
    
    long seed_;
    short tempo_;

public:

    // Constructors
    SerialismGenerator();
    SerialismGenerator(long seed);
    SerialismGenerator(std::string inputfile);
    ~SerialismGenerator();

    void initializeRandom();
    string mapRhythm(short duration, std::string pitch, string articulation);
    string rowToLilypond(Row r);
};
