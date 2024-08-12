#ifndef TIME_SIGNATURE_HPP_INCLUDED
#define TIME_SIGNATURE_HPP_INCLUDED
#include <string>
#include <iostream>

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

    std::string str() const;
    bool isValid() const;
    short num16ths() const;
    unsigned int getNumBeats()const;
    unsigned int getBeatLen() const;
};

#endif // TIME_SIGNATURE_HPP_INCLUDED