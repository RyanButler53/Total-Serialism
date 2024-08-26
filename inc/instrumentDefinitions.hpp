#ifndef INSTRUMENT_DEFINITIONS_HPP_INCLUDED
#define INSTRUMENT_DEFINITIONS_HPP_INCLUDED

#include "instrument.hpp"
#include "singleClef.hpp"
#include "note.hpp"

/***********
 * This file contains class declarations for all the instrments offered by
 * this total serialist music generator.  It is divided up into 3 sections:  
 * Strings, Woodwinds and Brass
 * 
 * Note that in serial style music, instruments don't transpose - generally
 * the sheet music is "as written". The two exceptions are String Bass and Piccolo
 * Bass sounds an octave lower than written and piccolo sounds an octave higher
 * than written.  This is done since they transpose by octaves and this reduces
 * ledger lines. 
 ***********/

// Strings

class Violin : public SingleClefInstrument {
  public:
    Violin(InstrumentData data, std::vector<Row> rows, std::vector<short> dynamics, int num, BoulezData boulez);
    ~Violin() = default;
};

class Viola : public SingleClefInstrument {
  public:
    Viola(InstrumentData data, std::vector<Row> rows, std::vector<short> dynamics, int num, BoulezData boulez);
    ~Viola() = default;
};


class Cello : public SingleClefInstrument {
  public:
    Cello(InstrumentData data, std::vector<Row> rows, std::vector<short> dynamics, int num, BoulezData boulez);
    ~Cello() = default;
};

// Bass music sounds 1 octave lower than it is written
class Bass : public SingleClefInstrument {
  public:
    Bass(InstrumentData data, std::vector<Row> rows, std::vector<short> dynamics, int num, BoulezData boulez);
    ~Bass() = default;
};

// Woodwinds

class AltoSax : public SingleClefInstrument {
  public:
    AltoSax(InstrumentData data, std::vector<Row> rows, std::vector<short> dynamics, int num, BoulezData boulez);
    ~AltoSax() = default;
};

class TenorSax : public SingleClefInstrument {
  public:
    TenorSax(InstrumentData data, std::vector<Row> rows, std::vector<short> dynamics, int num, BoulezData boulez);
    ~TenorSax() = default;
};

class BariSax : public SingleClefInstrument {
  public:
    BariSax(InstrumentData data, std::vector<Row> rows, std::vector<short> dynamics, int num, BoulezData boulez);
    ~BariSax() = default;

};

class Oboe : public SingleClefInstrument {
  public:
    Oboe(InstrumentData data, std::vector<Row> rows, std::vector<short> dynamics, int num, BoulezData boulez);
    ~Oboe() = default;
};

class Bassoon : public SingleClefInstrument {
  public:
    Bassoon(InstrumentData data, std::vector<Row> rows, std::vector<short> dynamics, int num, BoulezData boulez);
    ~Bassoon() = default;
};

class Clarinet : public SingleClefInstrument {
  public:
    Clarinet(InstrumentData data, std::vector<Row> rows, std::vector<short> dynamics, int num, BoulezData boulez);
    ~Clarinet() = default;
};

// Piccolo sounds one octave higher than written
class Piccolo : public SingleClefInstrument {
  public:
    Piccolo(InstrumentData data, std::vector<Row> rows, std::vector<short> dynamics, int num, BoulezData boulez);
    ~Piccolo() = default;
};

class Flute : public SingleClefInstrument {
  public:
    Flute(InstrumentData data, std::vector<Row> rows, std::vector<short> dynamics, int num, BoulezData boulez);
    ~Flute() = default;
};

// Brass

class Trombone : public SingleClefInstrument {
  public:
    Trombone(InstrumentData data, std::vector<Row> rows, std::vector<short> dynamics, int num, BoulezData boulez);
    ~Trombone() = default;
};

class Trumpet : public SingleClefInstrument {
  public:
    Trumpet(InstrumentData data, std::vector<Row> rows, std::vector<short> dynamics, int num, BoulezData boulez);
    ~Trumpet() = default;
};

class FrenchHorn : public SingleClefInstrument {
  public:
    FrenchHorn(InstrumentData data, std::vector<Row> rows, std::vector<short> dynamics, int num, BoulezData boulez);
    ~FrenchHorn() = default;
};

class Tuba : public SingleClefInstrument {
  public:
    Tuba(InstrumentData data, std::vector<Row> rows, std::vector<short> dynamics, int num, BoulezData boulez);
    ~Tuba() = default;
};

#endif // INSTRUMENT_DEFINITIONS_HPP_INCLUDED