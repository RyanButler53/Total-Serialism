#ifndef TIME_SIGNATURE_HPP_INCLUDED
#define TIME_SIGNATURE_HPP_INCLUDED
#include <string>
#include <iostream>

/**
 * @brief Class to represent a musical time signature. 
 * 
 * Used to set the measure length for total serialist music
 * Time Signature is copied and shared throughout all instruments. 
 */
class TimeSignature
{
private:
    std::string str_;
    unsigned int numBeats_;
    unsigned int beatLen_;

public:
    TimeSignature() = default;
    explicit TimeSignature(std::string ts);
    ~TimeSignature() = default;

    // Gets the string equivalent for lilypond code
    std::string str() const;

    // Checks if a time signature is valid. 
    // Logic is complicated to eliminate searching through a list
    bool isValid() const;

    // Gets the number of 16ths in a measure. 
    short num16ths() const;

    // Getting data members
    unsigned int getNumBeats()const;
    unsigned int getBeatLen() const;
};

#endif // TIME_SIGNATURE_HPP_INCLUDED