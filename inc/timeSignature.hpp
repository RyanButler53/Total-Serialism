#ifndef TIME_SIGNATURE_HPP_INCLUDED
#define TIME_SIGNATURE_HPP_INCLUDED
#include <string>
#include <iostream>
enum class TimeSig
{
    TS_1_4,
    TS_3_8,
    TS_2_4,
    TS_5_8,
    TS_3_4,
    TS_6_8,
    TS_7_8,
    TS_4_4,
    TS_9_8,
    TS_5_4,
    TS_11_8,
    TS_12_8,
    TS_6_4,
    TS_3_2,
    TS_13_8,
    TS_7_4,
    TS_15_8
};

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