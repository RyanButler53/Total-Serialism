#include "instrumentDefinitions.hpp"

using namespace std;

Violin::Violin(InstrumentData data, std::vector<Row> rows, vector<short> dynamics, int num, BoulezData boulez) : 
SingleClefInstrument(data, boulez, {rows, "Violin", "violin", "vln", dynamics, "treble", "c'",num}, {Note("g", 0), Note("a", 4)}){};

Viola::Viola(InstrumentData data, std::vector<Row> rows, vector<short> dynamics, int num, BoulezData boulez) : 
SingleClefInstrument(data, boulez, {rows, "Viola", "viola", "vla", dynamics, "alto", "c'",num}, {Note("c", 0), Note("g", 2)}){};

Cello::Cello(InstrumentData data, std::vector<Row> rows, vector<short> dynamics, int num, BoulezData boulez) : 
SingleClefInstrument(data, boulez, {rows, "Cello", "cello", "vlc",  dynamics, "bass", "c",num}, {Note("c", -1), Note("e", 3)}){};

Bass::Bass(InstrumentData data, std::vector<Row> rows, vector<short> dynamics, int num, BoulezData boulez) : 
SingleClefInstrument(data, boulez, {rows, "String Bass", "bass", "cb", dynamics, "bass", "c",num}, {Note("e", -1), Note("d", 3)}){};

AltoSax::AltoSax(InstrumentData data, std::vector<Row> rows, vector<short> dynamics, int num, BoulezData boulez) :
SingleClefInstrument(data, boulez, {rows, "Alto Saxophone", "altosax", "a sax", dynamics, "treble", "c'", num}, {Note("cs", 0), Note("af", 2)}){};

TenorSax::TenorSax(InstrumentData data, std::vector<Row> rows, vector<short> dynamics, int num, BoulezData boulez) : 
SingleClefInstrument(data, boulez, {rows, "Tenor Saxophone", "tenorsax", "t sax", dynamics, "treble", "c'", num}, {Note("af", -1), Note("e", 2)}){};

BariSax::BariSax(InstrumentData data, std::vector<Row> rows, vector<short> dynamics, int num, BoulezData boulez) : 
SingleClefInstrument(data, boulez, {rows, "Bari Saxophone", "barisax", "b sax", dynamics, "bass", "c", num}, {Note("cs", 0), Note("af", 2)}){};

Oboe::Oboe(InstrumentData data, std::vector<Row> rows, vector<short> dynamics, int num, BoulezData boulez) : 
SingleClefInstrument(data, boulez, {rows, "Oboe", "oboe", "ob", dynamics, "treble", "c'", num}, {Note("bf", 0), Note("g", 3)}){};

Bassoon::Bassoon(InstrumentData data, std::vector<Row> rows, vector<short> dynamics, int num, BoulezData boulez) : 
SingleClefInstrument(data, boulez, {rows, "Bassoon", "bassoon", "fag", dynamics, "bass", "c,", num}, {Note("bf", -2), Note("g", 2)}){};

Clarinet::Clarinet(InstrumentData data, std::vector<Row> rows, vector<short> dynamics, int num, BoulezData boulez) : 
SingleClefInstrument(data, boulez, {rows, "Clarinet", "clarinet", "cl", dynamics, "treble", "c'", num}, {Note("d", 0), Note("bf", 3)}){};

Piccolo::Piccolo(InstrumentData data, std::vector<Row> rows, vector<short> dynamics, int num, BoulezData boulez) : 
SingleClefInstrument(data, boulez, {rows, "Piccolo", "piccolo", "picc", dynamics, "treble", "c''", num}, {Note("d", 1), Note("c", 4)}){};

Flute::Flute(InstrumentData data, std::vector<Row> rows, vector<short> dynamics, int num, BoulezData boulez) : 
SingleClefInstrument(data, boulez, {rows, "Flute", "flute", "fl", dynamics, "treble", "c'", num}, {Note("c", 1), Note("f", 3)}){};

Trombone::Trombone(InstrumentData data, std::vector<Row> rows, vector<short> dynamics, int num, BoulezData boulez) :
SingleClefInstrument(data, boulez, {rows, "Trombone", "trombone", "tb", dynamics, "bass", "c",num}, {Note("e", -1), Note("f", 2)}){};

Trumpet::Trumpet(InstrumentData data, std::vector<Row> rows, vector<short> dynamics, int num, BoulezData boulez) :
SingleClefInstrument(data, boulez, {rows, "Trumpet", "trumpet", "tr", dynamics, "treble", "c'",num}, {Note("e", 0), Note("d", 3)}){};

FrenchHorn::FrenchHorn(InstrumentData data, std::vector<Row> rows, vector<short> dynamics, int num, BoulezData boulez) :
SingleClefInstrument(data, boulez, {rows, "French Horn", "frenchhorn", "cor", dynamics, "bass", "c,",num}, {Note("a", -2), Note("f", 2)}){};

Tuba::Tuba(InstrumentData data, std::vector<Row> rows, vector<short> dynamics, int num, BoulezData boulez) :
SingleClefInstrument(data, boulez, {rows, "Tuba", "tuba", "tb", dynamics, "bass", "c,",num}, {Note("d", -2), Note("f", 1)}){};