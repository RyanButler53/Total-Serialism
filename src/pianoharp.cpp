#include "pianoharp.hpp"
#include "instrument.hpp"

using namespace std;

Piano::Piano(InstrumentData data, vector<Row> RHrows,vector<Row> LHrows, vector<short> dynamics, int num) : 
    MultiClefInstrument(data, {RHrows, LHrows, dynamics, "Piano", "piano", num}) {};

Harp::Harp(InstrumentData data, vector<Row> RHrows,vector<Row> LHrows, vector<short> dynamics,int num) : 
    MultiClefInstrument(data, {RHrows, LHrows, dynamics, "Harp", "harp", num}) {};

