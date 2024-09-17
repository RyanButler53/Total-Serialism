#include <string>
#include <vector>
#include <random>
#include <mutex>
#include <unordered_map>
#include <tuple>
#include <filesystem>
#include <memory>

#include "instrumentFactory.hpp"
#include "timeSignature.hpp"
#include "analysisMatrix.hpp"
#include "instrument.hpp"
#include "pianoharp.hpp"
#include "instrumentDefinitions.hpp"
#include "threadPool.hpp"

#ifndef SERIALISM_GENERATOR_HPP_INCLUDED
#define SERIALISM_GENERATOR_HPP_INCLUDED


/**
 * @brief Class to handle the full generator of total serialist sheet music
 * The Serialism Generator class holds the data required to build the 
 * instruments and complete the entire score. There is only one instance of a
 * SerialismGenerator created. 
 * 
 * Memory: The Serialism Generator class owns pointers to 
 * 3 analysis Matrices, all instruments and the instrument Factory. 
 * It also has the instances of the mutex and distributions shared between
 * all the instruments.  
 * 
 */
class SerialismGenerator
{
  private:

    // Randomness Data
    std::mt19937 rng_;
    std::normal_distribution<double> boulezDist_;
    std::mutex boulezMutex_;

    // Mappings for pitches, articulations and dynamics to map a number
    // to  a specific value. Constant and determined at compile time. 
    const std::vector<std::string> pitchMap_{"c","cs","d","ef","e","f","fs","g","af","a","bf","b"};
    const std::vector<std::string> articulationMap_{"->", "-^", "-_", "-!", "-.", "--", "->-.", "-^\\sfz", "", "->-!", "\\sfz", "-^-!"};
    const std::vector<std::string> dynamicMap_{"\\ppppp", "\\pppp", "\\ppp", "\\pp", "\\p", "\\mp", "\\mf", "\\f", "\\ff", "\\fff", "\\ffff", "\\fffff"};
    
    // List of instruments that the random serialism generator can pick from. 
    std::vector<std::string> instrumentList_{
        "piano", "harp",
        "violin", "viola", "cello", "bass", 
        "oboe", "bassoon", "clarinet", "piccolo", "flute", 
        "trombone", "trumpet", "frenchhorn", "tuba"
    };

    // Mapping Row Types in strings to RowType Enums. 
    std::unordered_map<std::string, RowType> rowTypes_{
        {"P", RowType(P)},
        {"R", RowType(R)},
        {"I", RowType(I)},
        {"RI", RowType(RI)}};

    // Instrument Sorting Map
    const std::unordered_map<std::string, int> scoreOrdering_{
        {"Flute", 0}, {"Piccolo", 1}, {"Oboe", 2}, {"Clarinet",3},{"Bassoon", 4}, {"Alto Saxophone", 5}, 
        {"Tenor Saxophone", 6}, {"Bari Saxophone", 7}, {"French Horn", 8}, {"Trumpet", 9}, 
        {"Trombone", 10}, {"tuba", 11}, {"Piano", 12}, {"Harp", 13}, 
        {"Violin", 14}, {"Viola", 15}, {"Cello", 16}, {"String Bass", 17}};

    // Global piece data: Time Signature, Title, Composer and Output Filename
    TimeSignature ts_;
    std::string title_;
    std::string composer_;
    std::string outputFilename_;

    // Matrices (dynamically managed)
    std::shared_ptr<AnalysisMatrix> pitches_;
    std::shared_ptr<AnalysisMatrix> rhythms_;
    std::shared_ptr<AnalysisMatrix> articulations_;

    // Factory and Instrument vector
    std::shared_ptr<InstrumentFactory> factory_;
    std::vector<std::shared_ptr<Instrument>> instruments_;
    
    // Instrument names holds the name of each instrument and the number of them
    // Used to calculate Display Name in instrument objects
    std::vector<std::tuple<std::string, int>> instrumentNames_;
    
    // Holds all the rows belonging to each instrument
    std::vector<std::vector<Row>> instrumentRows_;

    size_t numRows_; // length of the piece (in rows). Defaults to 12
    long seed_; // Randomness Seed. Refaults to (time(0))
    short tempo_; // Piece Tempo
    float boulezFactor_; // Std deviation of the boulez dist. 0 for gui designed pieces
    bool parts_;
    
    // Parallelism
    unsigned int maxThreads_ = 8; // max threads for concurrent generation

    // Private Functions

    /**
     * @brief Initializes the variables of the SerialismGenerator randomly
     * 
     */
    void initializeRandom();

    /**
     * @brief Generates the entire piece
     * 
     * @param lilypondCode Vector to populate with lilypond code
     */
    void generatePiece(std::vector<std::string> &lilypondCode);

    /**
     * @brief Returns the header of the piece
     * 
     * @return std::string Piece header. 
     */
    std::string header() const;

    /**
     * @brief Returns the "Score box" for the piece. 
     * The score box in lilypond is analogous to the main function in C++
     * This is the driver code that lets the staves get called and added correcly. 
     * 
     * @return std::string 
     */
    std::string scoreBox(bool parts=false);

    // Utility Functions

    /**
     * @brief Get the Row Nums object from a file stream by reading in 12 numbers
     * Calls getRowTypes() immediately after. 
     * @param input Fstream object to read from
     * @return std::vector<short> Row Numbers.
     */
    std::vector<short> getRowNums(std::fstream& input) const;

    /**
     * @brief Get the Row Types object from a fileStrem by reading in 12 words
     * Combines the words with their row type and number to create Row objects
     * Called immediately after getRowNums()
     * @param input Fstream to read from
     * @param rowNums A vector of corresponding Row Numbers
     * @return std::vector<Row> Vector of Rows read from 2 lines from a file
     */
    std::vector<Row> getRowTypes(std::fstream &input, std::vector<short> rowNums) const;

  public:

    // Constructors

    // Only given an output file, use time for seed and generate randomly
    SerialismGenerator(std::string outputFileThat);
    
    // Given a seed and output filename, generate the fields randomly. 
    SerialismGenerator(long seed, std::string outputFilename, unsigned int numThreads = 8, bool parts=false);

    // Given an input and output filenae, use the inputfile to read in fields. 
    SerialismGenerator(std::string inputfile, std::string outputFilename, bool parts=false);
    
    // Clean up Analysis Matrices, Instruments and Factory
    ~SerialismGenerator() = default;

    /**
     * @brief Runs the Total Serial Generator process from end to end. 
     * 
     * Writes the lilypond code to the outputFilename_ file for compilation
     */
    void run();
};

#endif
