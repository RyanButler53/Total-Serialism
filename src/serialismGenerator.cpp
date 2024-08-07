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

    // Pitch, Rhythm, Articulation, Right Hand, Left Hand, Dynamics
    vector<vector<short>> sequences{6};
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
    // Right Hand rows
    string s;
    getline(input, s);
    stringstream ss{s};
    for (size_t num = 0; num < 12; ++ num){
        string row;
        ss >> row;
        if (rowTypes.find(row) != rowTypes.end())
        {
            // rhRows_.push_back(Row(rowTypes[row], sequences[3][num]));
        } else {
            cerr << "Invalid Row: " << row << endl;
            exit(1);
        }
    }

    // Left Hand Rows
    string s2;
    getline(input, s2);
    stringstream ss2{s2};
    for (size_t num = 0; num < 12; ++num)
    { 
        string row;
        ss2 >> row;
        if (rowTypes.find(row) != rowTypes.end()){
            // lhRows_.push_back(Row(rowTypes[row], sequences[4][num]));
        } else {
            cerr << "Invalid Row: " << row << endl;
            exit(1);
        }
    }

    // TODO: Elminate repeated for loop

    pitches_ = new AnalysisMatrix(sequences[0]);
    rhythms_ = new AnalysisMatrix(sequences[1]);
    articulations_ = new AnalysisMatrix(sequences[2]);
    dynamicsRow_ = sequences[5];

    string tempo_str;
    string ts_str;
    getline(input, tempo_str);
    getline(input, ts_str);
    ts_ = TimeSignature(ts_str);
    tempo_ = stoi(tempo_str);
    getline(input, title_);
    getline(input, composer_);

}

void SerialismGenerator::initializeRandom(){
    rng_ = mt19937(seed_);
    boulezDist_ = std::normal_distribution<double>(0, boulezFactor_);
    // Get pitch, rhythm, articulation and dynamics rows
    vector<short> rowNums{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    shuffle(rowNums.begin(), rowNums.end(), rng_);
    vector<short> pitchRow = rowNums;
    shuffle(rowNums.begin(), rowNums.end(), rng_);
    vector<short> rhythmRow = rowNums;
    shuffle(rowNums.begin(), rowNums.end(), rng_);
    vector<short> articulationRow = rowNums;
    shuffle(rowNums.begin(), rowNums.end(), rng_);
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

    instrumentNames_.push_back("piano");
    instrumentNames_.push_back("violin");
    instrumentNames_.push_back("cello");
    instrumentNames_.push_back("bass");
    instrumentNames_.push_back("viola");
   
    // Assign Rows
    std::uniform_int_distribution<short> rtypeDist{0, 3};
    size_t numRowsNeeded = std::count(instrumentNames_.begin(), instrumentNames_.end(), "piano");
    numRowsNeeded += instrumentNames_.size();
    for (size_t row_i = 0; row_i < numRowsNeeded; ++row_i)
    {
        shuffle(rowNums.begin(), rowNums.end(), rng_);
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
    for (std::string& name : instrumentNames_){
        if (name == "piano") { // Or Harp
            std::vector<Row> rh = instrumentRows_[row_i];
            std::vector<Row> lh = instrumentRows_[row_i + 1];
            instruments_.push_back(factory_.createInstrument(rh, lh));
            ++row_i;
        } else {
            std::vector<Row> row = instrumentRows_[row_i];
            instruments_.push_back(factory_.createInstrument(name, row));
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
    header += "\"\n   subtitle = \"Algorithmic Composition\"\n   instrument = \"Piano\"\n   "; // may get changed
    header += "composer = \"";
    header += composer_;
    header += "\"\n";
    header += "  tagline = ##f}\n\n";
    header += "global = { \\time " + ts_.str() + " \\tempo 4 = ";
    header += to_string(tempo_) + "}\n\n";
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