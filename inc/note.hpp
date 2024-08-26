#ifndef NOTE_HPP_INCLUDED
#define NOTE_HPP_INCLUDED
#include <string>

/**
 * @brief Class to represent a note. 
 * Notes are represented with a Pitch and an Octave. 
 * The octaves are NOT represented with typical numbers, they are represented
 *  with the number of commas and apostrophes required in lilypond
 * 
 * Class allows for raising and lowering an octave and converting to strings
 * 
 */
class Note
{
private:
    
    /**
     * @brief enum with all possible pitch types plus an invalid pitch
     * to default to or cause errors. 
     * 
     */
    enum class Pitch
    {
        C = 0,
        CS = 1,
        D = 2,
        EF = 3,
        E = 4,
        F = 5,
        FS = 6,
        G = 7,
        AF = 8,
        A = 9,
        BF = 10,
        B = 11,
        INVALID = 12
    };

    Pitch pitch_;
    int octave_;
    std::string str_;

    /**
     * @brief Converts a string to a pitch name
     * 
     * @param s string to convert
     * @return Pitch the pitch that is represented by the pitch. Invalid ones 
     * return Pitch::INVALID
     */
    Pitch strToPitch(std::string s);

public:
    // Constructors
    Note(std::string pitch, int octave);
    Note(Pitch pitch, int octave, std::string str);
    Note(std::string note);
    ~Note() = default;

    // Utility functions
    /**
     * @brief Gets the lilypond string equivalent of the note
     * 
     * @return std::string string equivalet
     */
    std::string str();

    /**
     * @brief Raises the note by an octave
     * 
     * @return Note Raised note. Can be updated to use the ++ operator
     */
    Note raise();

    /**
     * @brief Lowers the note by 1 octave
     * 
     * @return Note, lowered note. Can become the -- operator. 
     */
    Note lower();

    // Comparison Operators
    // Defining the higher note to be the higher sounding pitched note. 
    // All operators are defined for testing and completeness
    bool operator<(const Note &other) const;
    bool operator==(const Note &other)const ;
    bool operator!=(const Note &other) const;
    bool operator>(const Note &other) const;
};

#endif // NOTE_HPP_INCLUDED
