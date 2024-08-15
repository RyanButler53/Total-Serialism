#ifndef INSTRUMENT_DEFINITIONS_HPP_INCLUDED
#define INSTRUMENT_DEFINITIONS_HPP_INCLUDED

#include "instrument.hpp"
#include "singleClef.hpp"
#include "note.hpp"

// Strings

class Violin : public SingleClefInstrument
{
private:
    const Note lowerBound_ = Note("g", 0);
    const Note upperBound_ = Note("a", 4);

public:
    Violin(InstrumentData data, std::vector<Row> rows, std::vector<short> dynamics, int num);
    ~Violin() = default;

};

class Viola : public SingleClefInstrument
{
private:
    const Note lowerBound_ = Note("c", 0);
    const Note upperBound_ = Note("g", 2);

public:
    Viola(InstrumentData data, std::vector<Row> rows, std::vector<short> dynamics, int num);
    ~Viola() = default;
};


class Cello : public SingleClefInstrument
{
private:
    const Note lowerBound_ = Note("c", -1);
    const Note upperBound_ = Note("e", 3);

public:
    Cello(InstrumentData data, std::vector<Row> rows, std::vector<short> dynamics, int num);
    ~Cello() = default;
};


class Bass : public SingleClefInstrument
{
private:
    const Note lowerBound_ = Note("e", -1);
    const Note upperBound_ = Note("d", 3);

public:
    Bass(InstrumentData data, std::vector<Row> rows, std::vector<short> dynamics, int num);
    ~Bass() = default;
};

// Woodwinds

class AltoSax : public SingleClefInstrument
{
private:
    const Note lowerBound_ = Note("cs", 0);
    const Note upperBound_ = Note("af", 2);

public:
    AltoSax(InstrumentData data, std::vector<Row> rows, std::vector<short> dynamics, int num);
    ~AltoSax() = default;
};

class TenorSax : public SingleClefInstrument
{
private:
    const Note lowerBound_ = Note("af", -1);
    const Note upperBound_ = Note("e", 2);

public:
    TenorSax(InstrumentData data, std::vector<Row> rows, std::vector<short> dynamics, int num);
    ~TenorSax() = default;
};

class BariSax : public SingleClefInstrument
{
private:
    const Note lowerBound_ = Note("cs", 0);
    const Note upperBound_ = Note("af", 2);

public:
    BariSax(InstrumentData data, std::vector<Row> rows, std::vector<short> dynamics, int num);
    ~BariSax() = default;

};

class Oboe : public SingleClefInstrument
{
private:
    
    const Note lowerBound_ = Note("bf", 0);
    const Note upperBound_ = Note("g", 3);

public:
    Oboe(InstrumentData data, std::vector<Row> rows, std::vector<short> dynamics, int num);
    ~Oboe() = default;
};

class Bassoon : public SingleClefInstrument
{
private:
    
    const Note lowerBound_ = Note("bf", -2);
    const Note upperBound_ = Note("g", 2);

public:
    Bassoon(InstrumentData data, std::vector<Row> rows, std::vector<short> dynamics, int num);
    ~Bassoon() = default;
};

class Clarinet : public SingleClefInstrument
{
private:
    
    const Note lowerBound_ = Note("d", 0);
    const Note upperBound_ = Note("bf", 3);

public:
    Clarinet(InstrumentData data, std::vector<Row> rows, std::vector<short> dynamics, int num);
    ~Clarinet() = default;
};

class Piccolo : public SingleClefInstrument
{
private:
    
    const Note lowerBound_ = Note("d", 2);
    const Note upperBound_ = Note("c", 5);

public:
    Piccolo(InstrumentData data, std::vector<Row> rows, std::vector<short> dynamics, int num);
    ~Piccolo() = default;
};

class Flute : public SingleClefInstrument
{
private:
    
    const Note lowerBound_ = Note("c", 1);
    const Note upperBound_ = Note("f", 3);

public:
    Flute(InstrumentData data, std::vector<Row> rows, std::vector<short> dynamics, int num);
    ~Flute() = default;
};

// Brass

class Trombone : public SingleClefInstrument
{
private:
    const Note lowerBound_{"e", -1};
    const Note upperBound_{"f", 2};

public:
    Trombone(InstrumentData data, std::vector<Row> rows, std::vector<short> dynamics, int num);
    ~Trombone() = default;
};

class Trumpet : public SingleClefInstrument
{
private:
    const Note lowerBound_ = Note("e", 0);
    const Note upperBound_ = Note("d", 3);

public:
    Trumpet(InstrumentData data, std::vector<Row> rows, std::vector<short> dynamics, int num);
    ~Trumpet() = default;
};

class FrenchHorn : public SingleClefInstrument
{
private:
    const Note lowerBound_ = Note("a", -2);
    const Note upperBound_ = Note("f", 2);
public:
    FrenchHorn(InstrumentData data, std::vector<Row> rows, std::vector<short> dynamics, int num);
    ~FrenchHorn() = default;
};

class Tuba : public SingleClefInstrument
{
private:
    const Note lowerBound_ = Note("d", -1);
    const Note upperBound_ = Note("f", 1);

public:
    Tuba(InstrumentData data, std::vector<Row> rows, std::vector<short> dynamics, int num);
    ~Tuba() = default;
};

#endif // INSTRUMENT_DEFINITIONS_HPP_INCLUDED