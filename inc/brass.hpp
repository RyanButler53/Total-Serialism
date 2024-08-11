#ifndef BRASS_HPP_INCLUDED
#define BRASS_HPP_INCLUDED

#include "instrument.hpp"
#include "singleClef.hpp"
#include "note.hpp"
#include "analysisMatrix.hpp"

class Trombone : public SingleClefInstrument
{
private:
    std::vector<Row> rows_;
    const Note lowerBound_ = Note("e", -1);
    const Note upperBound_ = Note("f", 2);
    std::string instrumentName_ = "Trombone";

public:
    Trombone(InstrumentData data, std::vector<Row> rows);
    ~Trombone() = default;

    std::string staffHeader();
    std::string scoreBox();
};

class Trumpet : public SingleClefInstrument
{
private:
    std::vector<Row> rows_;
    const Note lowerBound_ = Note("e", 0);
    const Note upperBound_ = Note("d", 3);
    std::string instrumentName_ = "Trumpet";

public:
    Trumpet(InstrumentData data, std::vector<Row> rows);
    ~Trumpet() = default;

    std::string staffHeader();
    std::string scoreBox();
};

class FrenchHorn : public SingleClefInstrument
{
private:
    std::vector<Row> rows_;
    const Note lowerBound_ = Note("a", -2);
    const Note upperBound_ = Note("f", 2);
    std::string instrumentName_ = "French Horn";

public:
    FrenchHorn(InstrumentData data, std::vector<Row> rows);
    ~FrenchHorn() = default;

    std::string staffHeader();
    std::string scoreBox();
};

class Tuba : public SingleClefInstrument
{
private:
    std::vector<Row> rows_;
    const Note lowerBound_ = Note("d", -1);
    const Note upperBound_ = Note("f", 1);
    std::string instrumentName_ = "Tuba";

public:
    Tuba(InstrumentData data, std::vector<Row> rows);
    ~Tuba() = default;

    std::string staffHeader();
    std::string scoreBox();
};

#endif //BRASS_HPP_INCLUDED