#include "serialismGenerator.hpp"
#include <chrono>
#include <iostream>
#include <fstream>
#include <unordered_map>

using namespace std;

SerialismGenerator::SerialismGenerator(): seed_{time(0)}
{
    initializeRandom();
}

SerialismGenerator::SerialismGenerator(long seed): 
    seed_{seed}
    {
    initializeRandom();
}

SerialismGenerator::SerialismGenerator(string inputfile):seed_{time(0)}{
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
        for (size_t num = 0; num < 12; ++num){
            short value;
            input >> value;
            seq.push_back(value);
        }
    }

    // Right Hand rows
    for (size_t num = 0; num < 12; ++ num){
        string s;
        input >> s;
        if (rowTypes.find(s) != rowTypes.end())
        {
            rhRows_.push_back(Row(rowTypes[s], sequences[3][num]));
        }
        else
        {
            cerr << "Invalid Row: " << s << endl;
            exit(1);
        }
    }
    // Left Hand Rows
    for (size_t num = 0; num < 12; ++ num){
        string s;
        input >> s;
        if (rowTypes.find(s) != rowTypes.end()){
            lhRows_.push_back(Row(rowTypes[s], sequences[4][num]));
        } else {
            cerr << "Invalid Row: " << s << endl;
            exit(1);
        }
    }   

    // TODO: Elminate repeated for loop

    pitches_ = new AnalysisMatrix(sequences[0]);
    rhythms_ = new AnalysisMatrix(sequences[1]);
    articulations_ = new AnalysisMatrix(sequences[2]);
    dynamicsRow_ = sequences[5];
    input >> tempo_;
    input >> title_;
    input >> composer_;
}

void SerialismGenerator::initializeRandom(){
    rng_ = mt19937(seed_);

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

    // Row Numbers RH/LH
    shuffle(rowNums.begin(), rowNums.end(), rng_);
    vector<short> rhRowNums = rowNums;
    shuffle(rowNums.begin(), rowNums.end(), rng_);
    vector<short> lhRowNums = rowNums;

    // Row Types
    std::uniform_int_distribution<short> rtypeDist{0, 3};
    for (size_t rowInd = 0; rowInd < 12; ++rowInd)
    {
        short rhtype = rtypeDist(rng_);
        rhRows_.push_back(Row(RowType(rhtype), rhRowNums[rowInd]));
        short lhtype = rtypeDist(rng_);
        lhRows_.push_back(Row(RowType(lhtype), lhRowNums[rowInd]));
    }
        // Tempo
    std::uniform_int_distribution tempoDist{40, 240};
    tempo_ = tempoDist(rng_);

    // Initialize analysis matrices
    pitches_ = new AnalysisMatrix(pitchRow);
    rhythms_ = new AnalysisMatrix(rhythmRow);
    articulations_ = new AnalysisMatrix(articulationRow);

    title_ = "Random Composition";
    composer_ = "Seed = " + to_string(seed_);
}

SerialismGenerator::~SerialismGenerator()
{
    delete pitches_;
    delete rhythms_;
    delete articulations_;
}

string SerialismGenerator::fullDuration(short duration, string pitch, string articulation){
    switch (duration) {
    case 1:
        return pitch  + "16"  + articulation;
    case 2: 
        return pitch + "8" + articulation ;
    case 3: 
        return pitch  + "8." + articulation;
    case 4: 
        return pitch  + "4" + articulation;
    case 5:
        return pitch + "4" + articulation + "~" + pitch + "16";
    case 6:
        return pitch + "4." + articulation;
    case 7:
        return pitch + "4.." + articulation;
    case 8:
        return pitch + "2" + articulation;
    case 9:
        return pitch + "2" + articulation + "~" + pitch + "16";
    case 10:
        return pitch + "2" + articulation + "~" + pitch + "8";
    case 11:
        return pitch + "2" + articulation + "~" + pitch + "8.";   
    case 12:
        return pitch + "2." + articulation;
    default:
        return "";
    }
    return "";
}

string SerialismGenerator::rowToLilypond(Row r, short dynamic){
    // Get the piches, rhythms and articulations for the row. 
    vector<short> pitches = pitches_->getRow(r);
    vector<short> rhythms = rhythms_->getRow(r);
    vector<short> articulations = articulations_->getRow(r);
    // Increment Durations: 1-12 instead of 0-11
    for (auto &duration : rhythms)
    {
        ++duration;
    }

    // 16th notes remaining in the measure
    short availableDuration = 13;
    string lilypondCode = "";
    
    for (size_t note = 0; note < 12; ++note){
        short noteDuration = rhythms[note];
        string pitch = pitchMap_[pitches[note]];
        string articulation = articulationMap_[articulations[note]];
        if (noteDuration < availableDuration)
        { // fit entire note in measure
            lilypondCode += fullDuration(noteDuration, pitch, articulation);
            lilypondCode += " ";
            availableDuration -= noteDuration;
        }
        else if (noteDuration == availableDuration)
        { // End of bar case.
            lilypondCode += fullDuration(noteDuration, pitch, articulation);
            lilypondCode += " | ";
            availableDuration = 13;
        }
        else
        { // Split note into 2 bars case
            lilypondCode += fullDuration(availableDuration, pitch, articulation);
            short remaining = noteDuration - availableDuration; // total - used
            lilypondCode += "~ | ";
            lilypondCode += fullDuration(remaining, pitch, "");
            lilypondCode += " ";
            availableDuration = 13 - remaining;
        }

        if (note == 0 and dynamic >= 0){
            size_t codelen = lilypondCode.length();
            if (lilypondCode.substr(codelen - 2) == "z ")
            {
                lilypondCode.erase(lilypondCode.length() - 5);
            }
            lilypondCode += dynamicMap_[dynamic] + " ";
        }
    }
    lilypondCode += "\n";
    return lilypondCode;
}

void SerialismGenerator::generatePiece(bool rh, vector<string>& lilypondCode){
    vector<Row> &allRows = lhRows_;
    if (rh) {
        allRows = rhRows_;
        string staffStart = "<< \\new Staff \\fixed c'{\\clef treble \\time 13/16 \\tempo 4 = ";
        staffStart += to_string(tempo_);
        lilypondCode.push_back(staffStart + "\n");
    } else {
        string staffStart = "    \\new Staff \\fixed c{\\clef bass \\time 13/16\n";
        lilypondCode.push_back(staffStart);
    }
    for (size_t rowInd = 0; rowInd < allRows.size(); ++rowInd) {
        short dynamic = -1;
        if (rh)
        {
            dynamic = dynamicsRow_[rowInd];
        }
        string lilypondRow = rowToLilypond(allRows[rowInd], dynamic);
        lilypondCode.push_back(lilypondRow);
    }
    lilypondCode.push_back("         \\fine}\n");
    if (!rh) {
        lilypondCode.push_back(">>");
    }
}

string SerialismGenerator::header(){
    string header = "\\version \"2.24.1\"\n\\language \"english\"\n\n";
    header += "\\header {\n   title = \"";
    header += title_;
    header += "\"\n   subtitle = \"Algorithmic Composition\"\n   instrument = \"Piano\"\n   ";
    header += "composer = \"";
    header += composer_;
    header += "\"\n";
    header += "  tagline = ##f}\n";
    return header;
}

