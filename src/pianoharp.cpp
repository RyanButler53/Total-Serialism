#include "pianoharp.hpp"
#include "instrument.hpp"

using namespace std;

Piano::Piano(InstrumentData data, std::vector<Row> RHrows,std::vector<Row> LHrows, int num) : 
    MultiClefInstrument(data, {RHrows, LHrows, "Piano", "piano", num}) {};

Harp::Harp(InstrumentData data, std::vector<Row> RHrows,std::vector<Row> LHrows, int num) : 
    MultiClefInstrument(data, {RHrows, LHrows, "Harp", "harp", num}) {};

