#include <string>
#include <vector>
#include <random>
#include <mutex>
#include "analysisMatrix.hpp"

#ifndef SERIALISM_GENERATOR_HPP_INCLUDED
#define SERIALISM_GENERATOR_HPP_INCLUDED

class SerialismGenerator
{
private:
    std::mt19937 rng_;
    std::normal_distribution<double> boulezDist_;
    std::mutex boulezMutex_;
    std::vector<Row> rhRows_;
    std::vector<Row> lhRows_;
    std::vector<short> dynamicsRow_;
    const std::vector<std::string> pitchMap_{"c","cs","d","ef","e","f","fs","g","af","a","bf","b"};
    const std::vector<std::string> articulationMap_{"->", "-^", "-_", "-!", "-.", "--", "->-.", "-^\\sfz", "", "->-!", "\\sfz", "-^-!"};
    const std::vector<std::string> dynamicMap_{"\\ppppp", "\\pppp", "\\ppp", "\\pp", "\\p", "\\mp", "\\mf", "\\f", "\\ff", "\\fff", "\\ffff", "\\fffff"};
    
    std::string title_;
    std::string composer_;
    AnalysisMatrix *pitches_;
    AnalysisMatrix* rhythms_;
    AnalysisMatrix* articulations_;
    
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
    std::string rowToLilypond(Row r, short dynamic);

    /**
     * @brief Function that formats a string in lilypond style for a given 
     * rhythm duration. Called only when no barline tie is needed
     * 
     * @param duration Note length required. 
     * @param pitch String of the pitch 
     * @param articulation Articulation (is "" if no articulation needed)
     * @return std::string : Lilypond formatted string for the duration
     */
    std::string fullDuration(short duration, std::string jitter, std::string pitch, std::string articulation);

    void generatePiece(bool rh,std::vector<std::string>& lilypondCode);

    std::string header();

    std::string boulezJitter();
};

#endif
