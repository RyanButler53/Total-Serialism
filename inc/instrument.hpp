#ifndef INSTRUMENT_HPP_INCLUDED
#define INSTRUMENT_HPP_INCLUDED

#include "analysisMatrix.hpp"
#include "timeSignature.hpp"
#include "note.hpp"

#include <cassert>
#include <algorithm>
#include <string>
#include <mutex>
#include <random>
#include <memory>
#include <iostream>
#include <fstream>

// Structs to store Instrument Data (Passed from Instrument classes to Instrument Base)
struct InstrumentData
{
    // Musical Shared Data
    std::shared_ptr<AnalysisMatrix> pitches_;
    std::shared_ptr<AnalysisMatrix> rhythms_;
    std::shared_ptr<AnalysisMatrix>  articulations_;
    TimeSignature ts_;
};

// Struct to store all the necessary data for the Boulez Jitter (And concurrency)
struct BoulezData {
    std::mt19937& rng_;
    std::normal_distribution<double>& boulezDist_;
    std::mutex& boulezMutex_;
};

// Struct to store Instrument Ranges for Boulez Jitter and proper ranges
struct Range {
    Note low_;
    Note high_;
};

// Base class
class Instrument
{
private:
    // Non Musical Shared Data
    std::mt19937 &rng_;
    std::normal_distribution<double> &boulezDist_;
    std::mutex &boulezMutex_;

    // Instrument Specific, Passed up from derived classes
    Note low_;
    Note high_;

protected:

    // All Inherited Instruments can use the Analysis Matrices and dynamics rows
    std::shared_ptr<AnalysisMatrix> pitches_;
    std::shared_ptr<AnalysisMatrix> rhythms_;
    std::shared_ptr<AnalysisMatrix> articulations_;
    TimeSignature ts_;

    // Everything can access the pitch, articulation and dynamic mappings
    const std::vector<std::string> pitchMap_{"c", "cs", "d", "ef", "e", "f", "fs", "g", "af", "a", "bf", "b"};
    const std::vector<std::string> articulationMap_{"\\sfz", "-^\\sfz", "->", "-^", "-_", "-!", "-.", "--", "->-.",  "", "->-!" , "-^-!"};
    const std::vector<std::string> dynamicMap_{"\\ppppp", "\\pppp", "\\ppp", "\\pp", "\\p", "\\mp", "\\mf", "\\f", "\\ff", "\\fff", "\\ffff", "\\fffff"};

public:
    // Constructors
    Instrument(InstrumentData data, BoulezData boulez, Range range);
    virtual ~Instrument() = default;

    // Generation functions

    /**
     * @brief Converts a row r to lilypond code. Returns a single string
     * that represents the entire row in lilypond. Each measure is given its
     * own line.
     *
     * @param r The Row to convert
     * @param dynamic The dynamic index. -1 if no dynamic needed.
     * @param leftover The number of leftover 16ths. The leftover 16ths are used
     * in the next row
     * @return std::string Lilypond code representing a single row.
     */
    std::string rowToLilypond(Row r, short dynamic, short &leftover);

    /**
     * @brief Generate Code for the entire piece
     *
     * @param lilypondCode Reference to vector of strings with each line
     */
    virtual std::vector<std::string> generateCode() = 0;

    /**
     * @brief Unique Staff Header for each staff in the piece
     *
     * @return std::string
     */
    virtual std::string staffHeader() = 0;

    /**
     * @brief Unique score box entry
     *
     * @return std::string
     */
    virtual std::string instrumentScoreBox(bool specificPart) = 0;

    // Utility Functions

    /**
     * @brief Clears the Sfz off of the starting note
     *
     * @param str
     */
    void clearSfz(std::string &str);

    /**
     * @brief Adds a dynamic if necessary
     * 
     * @param lilypondCode Lilypond code to modify. 
     * @param dynamic Dynamic index to add
     * @param note Index of the note. Only add if note == 0
     */
    void addDynamic(std::string &lilypondCode, short dynamic, size_t note);

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
    std::string fullDuration(short duration, std::string absPitch, std::string articulation);


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
    std::string fullDurationDynamic(short duration, std::string absPitch, size_t articulationInd, short dynamic);

    /**
     * @brief Clamps a note to be within the instruments range
     *
     * @return String. The adjusted note. If he note is in range
     * than returns the input
     */
    std::string clamp(std::string n);

    /**
     * @brief Uses uses the BoulezDist_ distribution to increase or decrease
     * the pitch of a note by 1 or 2 octaves. Named after Pierre Boulez
     * for his original Total Serial experiment putting notes as far
     * away as possible
     * 
     * @return std::string a suffix to put after a note string in the lilypond code
     */
    std::string boulezJitter();

    /**
     * @brief Gets the instrument's name
     * 
     */
    virtual std::string getName() = 0;

    /**
     * @brief Gets the intruments number
     * 
     */
    virtual int getNum() = 0;

    /**
     * @brief Gets the header information for each part
     * 
     * @return std::string String with the header information
     */
    std::string header(std::string title, std::string composer);
    
    /**
     * @brief Makes the part for the instrument
     * 
     * @param filename filename to write to
     */
    void makePart(std::string filename, std::string title, std::string composer);

};



#endif // INSTRUMENT_HPP_INCLUDED