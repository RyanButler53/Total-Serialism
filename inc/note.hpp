#ifndef NOTE_HPP_INCLUDED
#define NOTE_HPP_INCLUDED
#include <string>

class Note
{
private:
    /* data */
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

public:
    Note(std::string pitch, int octave);
    ~Note() = default;

    std::string str();
    bool operator<(const Note &other) const;
    bool operator==(const Note &other)const ;
    bool operator!=(const Note &other) const;
    bool operator>(const Note &other) const;
};

#endif // NOTE_HPP_INCLUDED
