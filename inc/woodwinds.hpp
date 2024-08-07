#ifndef WOODWINDS_HPP_INCLUDED
#define WOODWINDS_HPP_INCLUDED

#include "instrument.hpp"
#include "singleClef.hpp"
#include "note.hpp"
#include "analysisMatrix.hpp"

class AltoSax : public SingleClefInstrument
{
private:
    std::vector<Row> rows_;
    const Note lowerBound_ = Note("cs", 0);
    const Note upperBound_ = Note("af", 2);
    std::string instrumentName_ = "Alto Saxophone";

public:
    AltoSax(InstrumentData data, std::vector<Row> rows);
    ~AltoSax() = default;

    std::string staffHeader();
    std::string scoreBox();
};

class TenorSax : public SingleClefInstrument
{
private:
    std::vector<Row> rows_;
    const Note lowerBound_ = Note("af", -1);
    const Note upperBound_ = Note("e", 2);
    std::string instrumentName_ = "Tenor Saxophone";

public:
    TenorSax(InstrumentData data, std::vector<Row> rows);
    ~TenorSax() = default;

    std::string staffHeader();
    std::string scoreBox();
};

class BariSax : public SingleClefInstrument
{
private:
    std::vector<Row> rows_;
    const Note lowerBound_ = Note("cs", 0);
    const Note upperBound_ = Note("af", 2);
    std::string instrumentName_ = "Bari Saxophone";

public:
    BariSax(InstrumentData data, std::vector<Row> rows);
    ~BariSax() = default;

    std::string staffHeader();
    std::string scoreBox();
};

class Oboe : public SingleClefInstrument
{
private:
    std::vector<Row> rows_;
    const Note lowerBound_ = Note("bf", 0);
    const Note upperBound_ = Note("g", 3);
    std::string instrumentName_ = "Oboe";

public:
    Oboe(InstrumentData data, std::vector<Row> rows);
    ~Oboe() = default;

    std::string staffHeader();
    std::string scoreBox();
};

class Bassoon : public SingleClefInstrument
{
private:
    std::vector<Row> rows_;
    const Note lowerBound_ = Note("bf", -2);
    const Note upperBound_ = Note("g", 2);
    std::string instrumentName_ = "Bassoon";

public:
    Bassoon(InstrumentData data, std::vector<Row> rows);
    ~Bassoon() = default;

    std::string staffHeader();
    std::string scoreBox();
};

class Clarinet : public SingleClefInstrument
{
private:
    std::vector<Row> rows_;
    const Note lowerBound_ = Note("d", 0);
    const Note upperBound_ = Note("bf", 3);
    std::string instrumentName_ = "Clarinet";

public:
    Clarinet(InstrumentData data, std::vector<Row> rows);
    ~Clarinet() = default;

    std::string staffHeader();
    std::string scoreBox();
};

class Piccolo : public SingleClefInstrument
{
private:
    std::vector<Row> rows_;
    const Note lowerBound_ = Note("d", 2);
    const Note upperBound_ = Note("c", 5);
    std::string instrumentName_ = "Piccolo";

public:
    Piccolo(InstrumentData data, std::vector<Row> rows);
    ~Piccolo() = default;

    std::string staffHeader();
    std::string scoreBox();
};

class Flute : public SingleClefInstrument
{
private:
    std::vector<Row> rows_;
    const Note lowerBound_ = Note("c", 1);
    const Note upperBound_ = Note("f", 3);
    std::string instrumentName_ = "Flute";

public:
    Flute(InstrumentData data, std::vector<Row> rows);
    ~Flute() = default;

    std::string staffHeader();
    std::string scoreBox();
};

#endif // WOODWINDS_HPP_INCLUDED