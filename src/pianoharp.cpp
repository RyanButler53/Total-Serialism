#include "pianoharp.hpp"
#include "instrument.hpp"

using namespace std;

Piano::Piano(InstrumentData data, vector<Row> RHrows,vector<Row> LHrows, vector<short> dynamics, int num, BoulezData boulez) : 
    MultiClefInstrument(data, boulez, {RHrows, LHrows, dynamics, "Piano", "piano", "pno", num}, {Note("a", -3), Note("c", 4)}) {};

Harp::Harp(InstrumentData data, vector<Row> RHrows,vector<Row> LHrows, vector<short> dynamics,int num, BoulezData boulez) : 
    MultiClefInstrument(data, boulez, {RHrows, LHrows, dynamics, "Harp", "harp", "arp", num},{Note("c", -3), Note("g",3)}) {};

