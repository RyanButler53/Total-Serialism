#include "instrumentDefinitions.hpp"

using namespace std;

Violin::Violin(InstrumentData data, std::vector<Row> rows, vector<short> dynamics, int num) : 
SingleClefInstrument(data, {rows, "Violin", "violin", dynamics, "treble", "c''",num}){};

Viola::Viola(InstrumentData data, std::vector<Row> rows, vector<short> dynamics, int num) : 
SingleClefInstrument(data, {rows, "Viola", "viola", dynamics, "alto", "c'",num}){};

Cello::Cello(InstrumentData data, std::vector<Row> rows, vector<short> dynamics, int num) : 
SingleClefInstrument(data, {rows, "Cello", "cello", dynamics, "bass", "c",num}){};

Bass::Bass(InstrumentData data, std::vector<Row> rows, vector<short> dynamics, int num) : 
SingleClefInstrument(data, {rows, "String Bass", "bass", dynamics, "bass", "c",num}){};

AltoSax::AltoSax(InstrumentData data, std::vector<Row> rows, vector<short> dynamics, int num) :
SingleClefInstrument(data, {rows, "Alto Saxophone", "altosax", dynamics, "treble", "c''", num}){};

TenorSax::TenorSax(InstrumentData data, std::vector<Row> rows, vector<short> dynamics, int num) : 
SingleClefInstrument(data, {rows, "Tenor Saxophone", "tenorsax", dynamics, "treble", "c'", num}){};

BariSax::BariSax(InstrumentData data, std::vector<Row> rows, vector<short> dynamics, int num) : 
SingleClefInstrument(data, {rows, "Bari Saxophone", "barisax", dynamics, "bass", "c", num}){};

Oboe::Oboe(InstrumentData data, std::vector<Row> rows, vector<short> dynamics, int num) : 
SingleClefInstrument(data, {rows, "Oboe", "oboe", dynamics, "treble", "c''", num}){};

Bassoon::Bassoon(InstrumentData data, std::vector<Row> rows, vector<short> dynamics, int num) : 
SingleClefInstrument(data, {rows, "Bassoon", "bassoon", dynamics, "bass", "c", num}){};

Clarinet::Clarinet(InstrumentData data, std::vector<Row> rows, vector<short> dynamics, int num) : 
SingleClefInstrument(data, {rows, "Clarinet", "clarinet", dynamics, "treble", "c''", num}){};

Piccolo::Piccolo(InstrumentData data, std::vector<Row> rows, vector<short> dynamics, int num) : 
SingleClefInstrument(data, {rows, "Piccolo", "piccolo", dynamics, "treble", "c''", num}){};

Flute::Flute(InstrumentData data, std::vector<Row> rows, vector<short> dynamics, int num) : 
SingleClefInstrument(data, {rows, "Flute", "flute", dynamics, "treble", "c''", num}){};

Trombone::Trombone(InstrumentData data, std::vector<Row> rows, vector<short> dynamics, int num) :
SingleClefInstrument(data, {rows, "Trombone", "trombone", dynamics, "bass", "c",num}){};

Trumpet::Trumpet(InstrumentData data, std::vector<Row> rows, vector<short> dynamics, int num) :
SingleClefInstrument(data, {rows, "Trumpet", "trombone", dynamics, "treble", "c''",num}){};

FrenchHorn::FrenchHorn(InstrumentData data, std::vector<Row> rows, vector<short> dynamics, int num) :
SingleClefInstrument(data, {rows, "French Horn", "frenchhorn", dynamics, "treble", "c",num}){};

Tuba::Tuba(InstrumentData data, std::vector<Row> rows, vector<short> dynamics, int num) :
SingleClefInstrument(data, {rows, "Tuba", "tuba", dynamics, "bass", "c",num}){};