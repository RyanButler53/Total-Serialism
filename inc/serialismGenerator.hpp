#include <string>
#include <vector>
#include <random>
#include <mutex>
#include "instrument.hpp"
#include "piano.hpp"
#include "instrumentFactory.hpp"
#include "timeSignature.hpp"
#include "analysisMatrix.hpp"

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
    // std::vector<Row> rhRows_;
    // std::vector<Row> lhRows_;
    //
    std::vector<short> dynamicsRow_;
    const std::vector<std::string> pitchMap_{"c","cs","d","ef","e","f","fs","g","af","a","bf","b"};
    const std::vector<std::string> articulationMap_{"->", "-^", "-_", "-!", "-.", "--", "->-.", "-^\\sfz", "", "->-!", "\\sfz", "-^-!"};
    const std::vector<std::string> dynamicMap_{"\\ppppp", "\\pppp", "\\ppp", "\\pp", "\\p", "\\mp", "\\mf", "\\f", "\\ff", "\\fff", "\\ffff", "\\fffff"};
    //

    TimeSignature ts_;
    std::string title_;
    std::string composer_;
    AnalysisMatrix *pitches_;
    AnalysisMatrix* rhythms_;
    AnalysisMatrix* articulations_;

    std::vector<std::string> instrumentNames_;
    std::vector<Instrument*> allInstruments_;

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

    /**
     * @brief Converts a row r to lilypond code. Returns a single string
     * that represents the entire row in lilypond. Each measure is given its 
     * own line.
     * 
     * @param r The Row to convert
     * @param dynamic The dynamic index. -1 if no dynamic needed.
     * @param ts Time signature. 
     * @param leftover The number of leftover 16ths. The leftover 16hs are used
     * in the next row
     * @return std::string Lilypond code representing a single row.  
     */
    // std::string rowToLilypond(Row r, short dynamic, short& leftover);

    /**
     * @brief Function that formats a string in lilypond style for a given 
     * rhythm duration. Called only when no barline tie is needed and at the
     * end of the piece to handle the remainder
     * 
     * @param duration Note length required. 
     * @param pitch String of the pitch 
     * @param articulation Articulation (is "" if no articulation needed)
     * @return std::string : Lilypond formatted string for the duration
     */
    // std::string fullDuration(short duration, std::string jitter, std::string pitch, std::string articulation);

    /**
     * @brief Generates the entire lilypond piece for the right or left hand
     * 
     * @param rh Bool, if generating the right hand or the left hand. 
     * @param lilypondCode Reference to std::vector that will hold the code
     * for the entire piece for that hand (or instrument)
     * @param ts Time signature. 
     */
    // void generatePiece(bool rh,std::vector<std::string>& lilypondCode);

    void generatePiece(std::vector<std::string> &lilypondCode);

    std::string header();

    std::string boulezJitter();

    // void clearSfz(std::string &str);

    std::string scoreBox();
};

#endif
