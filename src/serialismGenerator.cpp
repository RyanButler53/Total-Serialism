#include "serialismGenerator.hpp"
#include <chrono>
#include <iostream>
#include <fstream>
#include <regex>
#include <sstream>
#include <algorithm>
#include <cmath>

using namespace std;

SerialismGenerator::SerialismGenerator(string outputFilename): 
    outputFilename_{outputFilename},
    seed_{time(0)},
    boulezFactor_{0.5}
    {
    initializeRandom();
}

SerialismGenerator::SerialismGenerator(long seed, string outputFilename, unsigned int numThreads):
    outputFilename_{outputFilename},
    numRows_{12}, 
    seed_{seed},
    boulezFactor_{0.5},
    maxThreads_{numThreads}
    {
    initializeRandom();
}

SerialismGenerator::SerialismGenerator(string inputfile, string outputFilename):
    outputFilename_{outputFilename},seed_{time(0)}, boulezFactor_(0.5)
    {
    // Set up rng, fileinput and row mapping
    rng_ = mt19937(seed_);
    fstream input = fstream(inputfile);

    // Pitch, Rhythm, Articulation
    vector<vector<short>> sequences{3};
    for (auto &seq : sequences)
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

    // Read in tempo, time sig, title, composer
    string tempo_str;
    string ts_str;
    string numRows_str;
    getline(input, tempo_str);
    getline(input, ts_str);
    ts_ = TimeSignature(ts_str);
    tempo_ = stoi(tempo_str);
    getline(input, title_);
    getline(input, composer_);
    getline(input, numRows_str);
    numRows_ = stoi(numRows_str);

    // Initialize Factory
    boulezDist_= std::normal_distribution<double>(0, 0);
    BoulezData boulezData{rng_, boulezDist_, boulezMutex_};
    factory_ = new InstrumentFactory(pitches_, rhythms_, articulations_, ts_, boulezData);

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
        if (name == "piano" or name == "harp") {
            vector<vector<Row>> pianoRows{2};
            for (size_t i = 0; i < 2; ++i)
            {
                vector<short> rowNums = getRowNums(input);
                vector<Row> rows = getRowTypes(input, rowNums);
                pianoRows[i] = rows;
            }
            vector<short> dynamics = getRowNums(input);
            int num = instrumentMap[name];
            instruments_.push_back(factory_->createInstrument(name, pianoRows[0], pianoRows[1], dynamics, num));
        } else {
            vector<short> rowNums = getRowNums(input);
            vector<Row> rows = getRowTypes(input, rowNums);
            vector<short> dynamics = getRowNums(input);
            int num = instrumentMap[name];
            instruments_.push_back(factory_->createInstrument(name, rows,dynamics, num));
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
    // Individual Dynamic Rows
    vector<vector<short>> dynamicRows;
    for (size_t i = 0; i < numIns; ++i){
        std::shuffle(rowNums.begin(), rowNums.end(), rng_);
        vector<short> row = rowNums;
        dynamicRows.push_back(row);
    }
    BoulezData boulez{rng_, boulezDist_, boulezMutex_};
    factory_ = new InstrumentFactory(pitches_, rhythms_, articulations_, ts_, boulez);
    size_t row_i = 0;
    size_t dynamic_i = 0;
    for (auto &[name, num] : instrumentNames_)
    {
        if (name == "piano" or name == "harp") { // Or Harp
            std::vector<Row> rh = instrumentRows_[row_i];
            std::vector<Row> lh = instrumentRows_[row_i + 1];
            std::vector<short> dynamics = dynamicRows[dynamic_i];
            instruments_.push_back(factory_->createInstrument(name, rh, lh, dynamics, num));
            ++row_i;
        } else {
            std::vector<Row> row = instrumentRows_[row_i];
            std::vector<short> dynamics = dynamicRows[dynamic_i];
            instruments_.push_back(factory_->createInstrument(name, row, dynamics, num));
        }
        ++row_i;
        ++dynamic_i;
    }
}

SerialismGenerator::~SerialismGenerator()
{
    // clean up matrices
    delete pitches_;
    delete rhythms_;
    delete articulations_;

    // Clean up instruments
    for (Instrument*& i : instruments_){
        delete i;
    }

    // Clean up factory
    delete factory_;
}

void SerialismGenerator::generatePiece(vector<string>& lilypondCode){
    lilypondCode.push_back(header());
    // Parallelize Here
    cout << maxThreads_ << endl;
    // maxThreads_ = 1;
    if (maxThreads_ > 1)
    {
        vector<vector<string>> instrumentCodes(instruments_.size());
        ThreadPool tp(maxThreads_);
        for (size_t i = 0; i < instruments_.size();++i)
        {
            Instrument*& insPtr = instruments_[i];
            vector<string> &code = instrumentCodes[i];
            tp.submit([i, &insPtr, &code]
                      { return insPtr->generateCode(code); });
        }
        // Wait for instruments to finish
        tp.run();
        while (!tp.isDone()){}

        // Combine into one big vector
        for (std::vector<string>& code : instrumentCodes){
            for (string& line : code){
                lilypondCode.push_back(line);
            }
        }
    }
    else
    {
        for (Instrument*& instrument : instruments_){
            instrument->generateCode(lilypondCode);
        }
    }

    lilypondCode.push_back(scoreBox());
}

string SerialismGenerator::header() const {
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
    if (instrumentNames_.size() > 9){
        header += "\\paper{\n\t#(set-paper-size \"11x17\")\n}\n\n";
    } else{
        header += "\\paper{\n\t#(set-paper-size \"letter\")\n}\n\n";
    }
    return header;
}

std::string SerialismGenerator::scoreBox() {
    std::string scoreBox = "\\score {\n\t<<\n";
    for (Instrument*& instrument : instruments_){
        scoreBox += instrument->scoreBox();
    }
    scoreBox += "\n\t>>\n}";
    return scoreBox;
}

std::vector<short> SerialismGenerator::getRowNums(std::fstream& input) const {
    vector<short> rowNums;
    string s;
    getline(input, s);
    stringstream ss{s};
    for (size_t num = 0; num < numRows_; ++num) {
        short value;
        ss >> value;
        rowNums.push_back(value);
    }
    return rowNums;
}
std::vector<Row> SerialismGenerator::getRowTypes(std::fstream& input, std::vector<short> rowNums) const {
    std::vector<Row> rows;
    string s;
    getline(input, s);
    stringstream ss{s};
    for (size_t num = 0; num < numRows_; ++num)
    {
        string type;
        ss >> type;
        rows.push_back(Row(rowTypes_.at(type), rowNums[num]));
    }
    return rows;
}

void SerialismGenerator::run(){
    vector<string> lilypondCode;
    generatePiece(lilypondCode);

    ofstream outputFile{outputFilename_};
    for (auto& line : lilypondCode){
        outputFile << line;
    }
}
