#include "serialismGenerator.hpp"
#include <chrono>
#include <iostream>
#include <fstream>
#include <regex>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <unordered_map>

using namespace std;

SerialismGenerator::SerialismGenerator(): 
    seed_{time(0)},
    boulezFactor_{0.5}
    {
    initializeRandom();
}

SerialismGenerator::SerialismGenerator(long seed):
    seed_{seed},boulezFactor_{0} // 0.5
    {
    initializeRandom();
}

SerialismGenerator::SerialismGenerator(string inputfile):
    seed_{time(0)}, boulezFactor_(0.0)
    {
    // Set up rng, fileinput and row mapping
    rng_ = mt19937(seed_);
    fstream input = fstream(inputfile);
    std::unordered_map<string, RowType> rowTypes{
        {"P", RowType(P)},
        {"R", RowType(R)},
        {"I", RowType(I)},
        {"RI", RowType(RI)}};

    // Pitch, Rhythm, Articulation Dynamics
    vector<vector<short>> sequences{4};
    for (auto& seq : sequences)
    {
        string s;
        getline(input, s);
        stringstream ss{s};
        for (size_t num = 0; num < 12; ++num)
        {
            short value;
            ss >> value;
            seq.push_back(value);
        }
    }
    
    pitches_ = new AnalysisMatrix(sequences[0]);
    rhythms_ = new AnalysisMatrix(sequences[1]);
    articulations_ = new AnalysisMatrix(sequences[2]);
    dynamicsRow_ = sequences[3];

    // Read in tempo, time sig, title, composer
    string tempo_str;
    string ts_str;
    getline(input, tempo_str);
    getline(input, ts_str);
    ts_ = TimeSignature(ts_str);
    tempo_ = stoi(tempo_str);
    getline(input, title_);
    getline(input, composer_);

    // Initialize Factory
    factory_ = InstrumentFactory(pitches_, rhythms_, articulations_, dynamicsRow_, ts_);

    // Read in instruments
    std::unordered_map<std::string, int> instrumentMap;
    string numIns;
    getline(input, numIns);
    size_t numInstruments = stoi(numIns);
    for (size_t instrument_i = 0; instrument_i < numInstruments; ++instrument_i) {
        string name;
        getline(input, name);
        if (instrumentMap.find(name) == instrumentMap.end()){
            instrumentMap[name] = 1;
        } else {
            instrumentMap[name] += 1;
        }
        instrumentNames_.push_back({name,instrumentMap[name]});
        if (name == "piano" or name == "harp") { // or harp
            vector<vector<Row>> pianoRows;
            for (size_t i = 0; i < 2; ++i)
            {
                vector<Row> rows;
                vector<short> rowNums;
                string s;
                getline(input, s);
                stringstream ss{s};
                for (size_t num = 0; num < 12; ++num)
                {
                    short value;
                    ss >> value;
                    rowNums.push_back(value);
                }
                string s2;
                getline(input, s2);
                stringstream ss2{s2};
                for (size_t num = 0; num < 12; ++num)
                {
                    string type;
                    ss2 >> type;
                    rows.push_back(Row(rowTypes[type], rowNums[num]));
                }
                pianoRows.push_back(rows);
            }
            int num = instrumentMap[name];
            instruments_.push_back(factory_.createInstrument(name, pianoRows[0], pianoRows[1], num));
        } else {
            vector<Row> rows;
            vector<short> rowNums;
            string s;
            getline(input, s);
            stringstream ss{s};
            for (size_t num = 0; num < 12; ++num)
            {
                short value;
                ss >> value;
                rowNums.push_back(value);
            }
            string s2;
            getline(input, s2);
            stringstream ss2{s};
            for (size_t num = 0; num < 12; ++num)
            {
                string type;
                ss2 >> type;
                rows.push_back(Row(rowTypes[type], rowNums[num]));
            }
            int num = instrumentMap[name];
            instruments_.push_back(factory_.createInstrument(name, rows,num));
        }
    }
}

void SerialismGenerator::initializeRandom(){
    rng_ = mt19937(seed_);
    boulezDist_ = std::normal_distribution<double>(0, boulezFactor_);
    // Get pitch, rhythm, articulation and dynamics rows
    vector<short> rowNums{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    std::shuffle(rowNums.begin(), rowNums.end(), rng_);
    vector<short> pitchRow = rowNums;
    std::shuffle(rowNums.begin(), rowNums.end(), rng_);
    vector<short> rhythmRow = rowNums;
    std::shuffle(rowNums.begin(), rowNums.end(), rng_);
    vector<short> articulationRow = rowNums;
    std::shuffle(rowNums.begin(), rowNums.end(), rng_);
    dynamicsRow_ = rowNums; // Member Variable


    // Tempo
    std::uniform_int_distribution tempoDist{40, 240};
    tempo_ = tempoDist(rng_);

    // Initialize analysis matrices
    pitches_ = new AnalysisMatrix(pitchRow);
    rhythms_ = new AnalysisMatrix(rhythmRow);
    articulations_ = new AnalysisMatrix(articulationRow);
    const std::vector < std::string > validTimes{
                                     "1/4","3/8", "2/4", "5/8",
                                     "3/4", "7/4", "15/8","13/8",
                                     "6/8", "12/8", "6/4", "3/2",
                                     "7/8", "4/4", "9/8", "5/4", "11/8"
                                 };



    std::uniform_int_distribution tsDist{0, 16};
    ts_ = TimeSignature(validTimes[tsDist(rng_)]);

    title_ = "Random Composition";
    composer_ = "Seed = " + to_string(seed_);

    std::uniform_int_distribution<size_t> instrumentDist{1, instrumentList_.size()};

    size_t numIns = instrumentDist(rng_);
    vector<size_t> instrumentIndexes(instrumentList_.size());
    std::iota(instrumentIndexes.begin(), instrumentIndexes.end(), 0);
    std::shuffle(instrumentIndexes.begin(), instrumentIndexes.end(), rng_);
    std::sort(instrumentIndexes.begin(), instrumentIndexes.begin()+numIns);
    size_t numRowsNeeded = numIns;
    for (size_t i = 0; i < numIns; i++)
    {
        size_t instrument_i = instrumentIndexes[i];
        if (instrumentList_[instrument_i] == "piano" or instrumentList_[instrument_i] == "harp"){
            ++numRowsNeeded;
        }
        instrumentNames_.push_back({instrumentList_[instrument_i], 1});
    }

    // Assign Rows
    std::uniform_int_distribution<short> rtypeDist{0, 3};
    for (size_t row_i = 0; row_i < numRowsNeeded; ++row_i)
    {
        std::shuffle(rowNums.begin(), rowNums.end(), rng_);
        std::vector<Row> row;
        for (short &rowNum : rowNums)
        {
            short rtype = rtypeDist(rng_);
            row.push_back(Row(RowType(rtype), rowNum));
        }
        instrumentRows_.push_back(row);
    }

    factory_ = InstrumentFactory(pitches_, rhythms_, articulations_, dynamicsRow_, ts_);
    size_t row_i = 0;
    for (auto& [name, num] : instrumentNames_){
        if (name == "piano" or name == "harp") { // Or Harp
            std::vector<Row> rh = instrumentRows_[row_i];
            std::vector<Row> lh = instrumentRows_[row_i + 1];
            instruments_.push_back(factory_.createInstrument(name, rh, lh, num));
            ++row_i;
        } else {
            std::vector<Row> row = instrumentRows_[row_i];
            instruments_.push_back(factory_.createInstrument(name, row, num));
        }
        ++row_i;
    }
}

SerialismGenerator::~SerialismGenerator()
{
    // clean up memory
    delete pitches_;
    delete rhythms_;
    delete articulations_;
    for (Instrument*& i : instruments_){
        delete i;
    }
}

void SerialismGenerator::generatePiece(vector<string>& lilypondCode){
    lilypondCode.push_back(header());
    // Parallelize Here
    for (Instrument*& instrument : instruments_){
        instrument->generateCode(lilypondCode);
    }
    lilypondCode.push_back(scoreBox());
}

string SerialismGenerator::header(){
    string header = "\\version \"2.24.1\"\n\\language \"english\"\n\n";
    header += "\\header {\n   title = \"";
    header += title_;
    header += "\"\n   subtitle = \"Algorithmic Composition\"\n   instrument = \"Score\"\n   ";
    header += "composer = \"";
    header += composer_;
    header += "\"\n";
    header += "  tagline = ##f}\n\n";
    header += "global = { \\time " + ts_.str() + " \\tempo 4 = ";
    header += to_string(tempo_) + "}\n\n";
    if (instrumentNames_.size() > 10){
        header += "\\paper{\n\t#(set-paper-size \"11x17\")\n}\n\n";
    } else{
        header += "\\paper{\n\t#(set-paper-size \"letter\")\n}\n\n";
    }
    return header;
}

std::string SerialismGenerator::boulezJitter(){
    if (boulezFactor_ == 0.0){
        return "";
    }
    std::scoped_lock lock{boulezMutex_};
    double value = boulezDist_(rng_);
    int octave = std::round(value);
    std::clamp(octave, -2, 2);
    switch (octave)
    {
    case -2:
        return ",,";
    case -1:
        return ",";
    case 0:
        return "";
    case 1:
        return "'";
    case 2:
        return "''";
    default:
        // Clamp and round gaurantee an integer val between -2 and 2. 
        break;
    }
    return "";
}

std::string SerialismGenerator::scoreBox(){
    std::string scoreBox = "\\score {\n\t<<\n";
    for (Instrument*& instrument : instruments_){
        scoreBox += instrument->scoreBox();
    }
    scoreBox += "\n\t>>\n}";
    return scoreBox;
}