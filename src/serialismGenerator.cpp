#include "serialismGenerator.hpp"
#include <chrono>
#include <iostream>
#include <fstream>
#include <regex>
#include <sstream>
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
            rhRows_.push_back(Row(rowTypes[row], sequences[3][num]));
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
            lhRows_.push_back(Row(rowTypes[row], sequences[4][num]));
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
}

SerialismGenerator::~SerialismGenerator()
{
    delete pitches_;
    delete rhythms_;
    delete articulations_;
}

string SerialismGenerator::fullDuration(short duration, string jitter, string pitch, string articulation){
    string absPitch = pitch + jitter;
    assert(duration > 0);
    switch (duration)
    { // Might be a better way of handling this recursively.
    case 1:
        return absPitch  + "16"  + articulation;
    case 2: 
        return absPitch + "8" + articulation;
    case 3: 
        return absPitch  + "8." + articulation;
    case 4: 
        return absPitch  + "4" + articulation;
    case 5:
        return absPitch + "4" + articulation + "~" + absPitch + "16";
    case 6:
        return absPitch + "4." + articulation;
    case 7:
        return absPitch + "4.." + articulation;
    case 8:
        return absPitch + "2" + articulation;
    case 9:
        return absPitch + "2" + articulation + "~" + absPitch + "16";
    case 10:
        return absPitch + "2" + articulation + "~" + absPitch + "8";
    case 11:
        return absPitch + "2" + articulation + "~" + absPitch + "8.";   
    case 12:
        return absPitch + "2." + articulation;
    case 13:
        return absPitch + "2." + articulation + "~" + absPitch + "16";
    case 14:
        return absPitch + "2.." + articulation;
    case 15:
        return absPitch + "2..." + articulation;
    case 16:
        return absPitch + "1" + articulation;
    default: // 17+ 16ths left. Most 16ths allowed is 30 per measure
        string first16 = absPitch + "1" + articulation + "~";
        return first16 + fullDuration(duration - 16, jitter, pitch, articulation);
    }
    return "";
}


string SerialismGenerator::rowToLilypond(Row r, short dynamic, short& leftoverDuration){
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
    const short totalDuration = ts_.num16ths();
    string lilypondCode = "";
    for (size_t note = 0; note < 12; ++note)
    {
        short noteDuration = rhythms[note];
        string pitch = pitchMap_[pitches[note]];
        string articulation = articulationMap_[articulations[note]];
        string jitter = boulezJitter();
        if (noteDuration < leftoverDuration)
        { // fit entire note in measure
            lilypondCode += fullDuration(noteDuration, jitter, pitch, articulation); // clean up with lambdas????
            lilypondCode += " ";
            leftoverDuration -= noteDuration;
        }
        else if (noteDuration == leftoverDuration)
        { // End of bar case.
            lilypondCode += fullDuration(noteDuration, jitter, pitch, articulation);
            lilypondCode += " |\n";
            leftoverDuration = totalDuration;
        } else { // Split note into n bars case
            // Use up the rest of the duration in the current bar. 
            lilypondCode += fullDuration(leftoverDuration, jitter, pitch, articulation);
            short remaining = noteDuration - leftoverDuration; // total - used
            lilypondCode += "~ |\n";
            // There is still more than a full bar of duration left.
            while (remaining > totalDuration) {
                lilypondCode += fullDuration(totalDuration, jitter, pitch, articulation);
                remaining -= totalDuration;
                lilypondCode += "~ |\n";
            }
            if (totalDuration == remaining) { // exactly one bar left
                lilypondCode += fullDuration(remaining, jitter, pitch, articulation);
                lilypondCode += " |\n";
                leftoverDuration = totalDuration;
            } else { // less than 1 bar left. 
                lilypondCode += fullDuration(remaining, jitter, pitch, articulation);
                lilypondCode += " ";
                leftoverDuration = totalDuration - remaining;
            }
        }

        // Add Dynamic if necessary
        if (note == 0 and dynamic >= 0){
            clearSfz(lilypondCode);
            size_t codelen = lilypondCode.length();
            if (lilypondCode.substr(codelen - 3) == " |\n")
            {
                lilypondCode.erase(codelen- 3);
                lilypondCode += dynamicMap_[dynamic] + " |\n";
            } else if (lilypondCode.substr(codelen - 1) == "\n"){
                lilypondCode.erase(codelen- 2);
                lilypondCode += dynamicMap_[dynamic] + " |\n";

            } else {
                lilypondCode += dynamicMap_[dynamic] + " ";
            }
        }
    }

    lilypondCode += "\n";
    return lilypondCode;
}

void SerialismGenerator::generatePiece(bool rh, vector<string>& lilypondCode){

    // Staff Header
    string timeSigStr = to_string(ts_.getNumBeats()) + "/" + to_string(ts_.getBeatLen());
    if (rh)
    {
        stringstream staffStart;
        staffStart << "<< \\new Staff \\fixed c'{\\clef treble \\time " << timeSigStr << " \\tempo 4 = " << tempo_ << "\n";
        
        lilypondCode.push_back(staffStart.str());
    } else {
        stringstream staffStart;
        
        staffStart << "    \\new Staff \\fixed c{\\clef bass \\time " << timeSigStr << "\n";
        lilypondCode.push_back(staffStart.str());
    }

    // Notes
    short leftover16ths = ts_.num16ths();
    for (size_t rowInd = 0; rowInd < 12; ++rowInd) { // Change this to have varying length pieces
        short dynamic = -1;
        string lilypondRow;
        if (rh) {
            dynamic = dynamicsRow_[rowInd];
            lilypondRow = rowToLilypond(rhRows_[rowInd], dynamic,leftover16ths);
        } else {
            lilypondRow = rowToLilypond(lhRows_[rowInd], dynamic, leftover16ths);
        }
        lilypondCode.push_back(lilypondRow);
    }
    
    // End of piece. Clean up the remainder at the end of the piece
    if (leftover16ths == ts_.num16ths()){ // no leftover 16ths.
        lilypondCode.push_back("\n \\fine}\n");
    } else {
        string remainingPiece = fullDuration(leftover16ths, "", "r", "");
        lilypondCode.back().append(remainingPiece + "|\n \\fine}\n");
    }

    if (!rh) {
        lilypondCode.push_back(">>");
    }
}

string SerialismGenerator::header(){
    string header = "\\version \"2.24.1\"\n\\language \"english\"\n\n";
    header += "\\header {\n   title = \"";
    header += title_;
    header += "\"\n   subtitle = \"Algorithmic Composition\"\n   instrument = \"Piano\"\n   "; // may get changed
    header += "composer = \"";
    header += composer_;
    header += "\"\n";
    header += "  tagline = ##f}\n";
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


void SerialismGenerator::clearSfz(std::string& str) {
    const string from = "\\sfz";
    const string to = "";
    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // Move past the last replaced substring
    }
}