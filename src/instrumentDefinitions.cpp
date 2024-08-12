#include "instrumentDefinitions.hpp"

using namespace std;

Violin::Violin(InstrumentData data, std::vector<Row> rows, int num) : 
SingleClefInstrument(data, {rows, "Violin", "violin", "treble", "c''",num}){};

Viola::Viola(InstrumentData data, std::vector<Row> rows, int num) : 
SingleClefInstrument(data, {rows, "Viola", "viola", "alto", "c'",num}){};

Cello::Cello(InstrumentData data, std::vector<Row> rows, int num) : 
SingleClefInstrument(data, {rows, "Cello", "cello", "bass", "c",num}){};

Bass::Bass(InstrumentData data, std::vector<Row> rows, int num) : 
SingleClefInstrument(data, {rows, "String Bass", "bass", "bass", "c",num}){};

AltoSax::AltoSax(InstrumentData data, std::vector<Row> rows, int num) :
SingleClefInstrument(data, {rows, "Alto Saxophone", "altosax", "treble", "c''", num}){};

TenorSax::TenorSax(InstrumentData data, std::vector<Row> rows, int num) : 
SingleClefInstrument(data, {rows, "Tenor Saxophone", "tenorsax", "treble", "c'", num}){};

BariSax::BariSax(InstrumentData data, std::vector<Row> rows, int num) : 
SingleClefInstrument(data, {rows, "Bari Saxophone", "barisax", "bass", "c", num}){};

Oboe::Oboe(InstrumentData data, std::vector<Row> rows, int num) : 
SingleClefInstrument(data, {rows, "Oboe", "oboe", "treble", "c''", num}){};

Bassoon::Bassoon(InstrumentData data, std::vector<Row> rows, int num) : 
SingleClefInstrument(data, {rows, "Bassoon", "bassoon", "bass", "c", num}){};

Clarinet::Clarinet(InstrumentData data, std::vector<Row> rows, int num) : 
SingleClefInstrument(data, {rows, "Clarinet", "clarinet", "treble", "c''", num}){};

Piccolo::Piccolo(InstrumentData data, std::vector<Row> rows, int num) : 
SingleClefInstrument(data, {rows, "Piccolo", "piccolo", "treble", "c''", num}){};

Flute::Flute(InstrumentData data, std::vector<Row> rows, int num) : 
SingleClefInstrument(data, {rows, "Flute", "flute", "treble", "c''", num}){};

Trombone::Trombone(InstrumentData data, std::vector<Row> rows, int num) :
SingleClefInstrument(data, {rows, "Trombone", "trombone", "bass", "c",num}){};

Trumpet::Trumpet(InstrumentData data, std::vector<Row> rows, int num) :
SingleClefInstrument(data, {rows, "Trumpet", "trombone", "treble", "c''",num}){};

FrenchHorn::FrenchHorn(InstrumentData data, std::vector<Row> rows, int num) :
SingleClefInstrument(data, {rows, "French Horn", "frenchhorn", "treble", "c",num}){};

Tuba::Tuba(InstrumentData data, std::vector<Row> rows, int num) :
SingleClefInstrument(data, {rows, "Tuba", "tuba", "bass", "c",num}){};