#ifndef MULTI_CLEF_HPP_INCLUDED
#define MULTI_CLEF_HPP_INCLUDED

#include "instrument.hpp"
#include <fstream>
#include <ostream>

/**
 * @brief Struct to hold all data required for multi clef instruments
 * 
 * rhRows_: Row for the right hand
 * lhRows_: Row for the left hand
 * dynamic_: Dynamics row (shared)
 * displayName_: Name used to display on the score (Piano 1)
 * variableName_: Name used in lilypond source file. Differs from display name
 * if there is a space in the display name. 
 * num_: Number of the instrument. 
 */
struct MultiClefData{
    std::vector<Row> rhRows_;
    std::vector<Row> lhRows_;
    std::vector<short> dynamic_;
    std::string displayName_;
    std::string variableName_;
    std::string shortName_;
    int num_;
};

/**
 * @brief Derived class of Instrument Base to handle Multi Clef instruments
 * 
 */
class MultiClefInstrument : public Instrument
{
  private:
    std::vector<Row> rhRows_;
    std::vector<Row> lhRows_;
    std::vector<short> dynamics_;
    std::string variableName_;
    std::string displayName_;
    std::string shortName_;
    int num_;

public:
    MultiClefInstrument(InstrumentData data, BoulezData boulez, MultiClefData MCdata, Range r);
    virtual ~MultiClefInstrument();

    /**
     * @brief Generates code for multiclef instruments. 
     * Handles needing 2 hands and 2 staves
     * 
     * @param lilypondCode Vector reference to fill up with lines of lilypond
     */
    std::vector<std::string>  generateCode();

    /**
     * @brief Generates the appropriate staff header for both hands. 
     * Is delineated by a | character to split right and left hands
     * 
     * @return std::string 
     */
    std::string staffHeader();

    /**
     * @brief Generates the correct score box for a multi clef instrument
     * 
     * @return std::string Score box code. 
     */
    std::string instrumentScoreBox(bool specificPart);

        /**
     * @brief Get the Name object
     *
     * @return Get the name of the instrument;
     */
    std::string getName();

    /**
     * @brief  Gets the number of the instrument
     * 
     */
    int getNum();

    // /**
    //  * @brief Makes the individual part
    //  *
    //  * @param filename Filename to write to;
    //  */
    // void makePart(std::string filename);
};

#endif // MULTI_CLEF_HPP_INCLUDED