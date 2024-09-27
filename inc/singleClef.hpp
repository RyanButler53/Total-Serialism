#ifndef SINGLE_CLEF_HPP_INCLUDED
#define SINGLE_CLEF_HPP_INCLUDED

#include "instrument.hpp"
#include "note.hpp"
#include <string>
#include <fstream>
#include <ostream>

/**
 * @brief Struct to hold all the data required for generating code for a single
 * clef instrument. 
 * 
 * rows_: Rows for the instrument
 * displayName_: Name for the score
 * variableName_: Name for the variable in the score. Cannot have whitespace
 * dynamicsRow_: Rows for the dynamics. 
 * clef_: Clef for staff header. Values should be 'treble', 'alto' or 'bass' 
 * octave_: Octave for lilypond to start in.  Often in the center of the instrument range
 * int num: Number for the instrument display
 * 
 */
struct SingleClefData
{
    std::vector<Row> rows_;
    std::string displayName_;
    std::string variableName_;
    std::vector<short> dynamicsRow_;
    std::string clef_;
    std::string octave_;
    int num_;
};


class SingleClefInstrument : public Instrument
{
  private:
    std::vector<Row> rows_;
    std::string displayName_;
    std::string variableName_;
    std::vector<short> dynamicsRow_;
    std::string clef_;
    std::string octave_;
    int num_;

  public:
    SingleClefInstrument(InstrumentData data, BoulezData boulez, SingleClefData SCdata, Range r);
    virtual ~SingleClefInstrument();

    /**
     * @brief Generates code for the instrument
     * 
     * @param lilypondCode Vector reference to add the lines of lilypond code. 
     */
    std::vector<std::string>  generateCode();

    /**
     * @brief Creates the appropriate staff header
     * 
     * @return std::string Header as a string. 
     */
    std::string staffHeader();
    
    /**
     * @brief Creates the score box entry for the specific instrument
     * 
     * @return std::string The score box for the instrument. 
     */
    std::string instrumentScoreBox();
    
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
    //  * @brief Makes the individual part score box file
    //  * 
    //  * @param filename Filename to write to
    //  */
    // void makePart(std::string filename);
};

#endif
