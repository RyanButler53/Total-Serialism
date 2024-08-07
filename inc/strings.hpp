#ifndef STRINGS_HPP_INCLUDED
#define STRINGS_HPP_INCLUDED

#include "instrument.hpp"
#include "singleClef.hpp"
#include "note.hpp"
#include "analysisMatrix.hpp"

class Violin : public SingleClefInstrument
{
private:
    std::vector<Row> rows_;
    const Note lowerBound_ = Note("g", 0);
    const Note upperBound_ = Note("a", 4);
    std::string instrumentName_ = "Violin";

public:
    Violin(InstrumentData data, std::vector<Row> rows);
    ~Violin() = default;

    std::string staffHeader();
    std::string scoreBox();
};

class Viola : public SingleClefInstrument
{
private:
    std::vector<Row> rows_;
    const Note lowerBound_ = Note("c", 0);
    const Note upperBound_ = Note("g", 2);
    std::string instrumentName_ = "Viola";

public:
    Viola(InstrumentData data, std::vector<Row> rows);
    ~Viola() = default;

    std::string staffHeader();
    std::string scoreBox();
};


class Cello : public SingleClefInstrument
{
private:
    std::vector<Row> rows_;
    const Note lowerBound_ = Note("c", -1);
    const Note upperBound_ = Note("e", 3);
    std::string instrumentName_ = "Cello";

public:
    Cello(InstrumentData data, std::vector<Row> rows);
    ~Cello() = default;

    std::string staffHeader();
    std::string scoreBox();
};


class Bass : public SingleClefInstrument
{
private:
    std::vector<Row> rows_;
    const Note lowerBound_ = Note("e", -1);
    const Note upperBound_ = Note("d", 3);
    std::string instrumentName_ = "Bass";

public:
    Bass(InstrumentData data, std::vector<Row> rows);
    ~Bass() = default;

    std::string staffHeader();
    std::string scoreBox();
};

#endif // STRINGS_HPP_INCLUDED