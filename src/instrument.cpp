#include "instrument.hpp"

using namespace std;

Instrument::Instrument(InstrumentData data, BoulezData boulez, Range r) : 
pitches_{data.pitches_}, 
rhythms_{data.rhythms_}, 
articulations_{data.articulations_},
ts_{data.ts_},
rng_{boulez.rng_},
boulezDist_{boulez.boulezDist_},
boulezMutex_{boulez.boulezMutex_},
low_{r.low_},
high_{r.high_}
{}

string Instrument::rowToLilypond(Row r, short dynamic, short& leftoverDuration){
    // Get the piches, rhythms and articulations for the row. 
    vector<short> pitches = pitches_->getRow(r);
    vector<short> rhythms = rhythms_->getRow(r);
    vector<short> articulations = articulations_->getRow(r);
    // Increment Durations: 1-12 instead of 0-11
    for (auto &duration : rhythms) {
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
        pitch += boulezJitter();
        pitch = clamp(pitch);
        // "Curried" form of full duration since pitch and articulation are the same
        auto fd = [this, &pitch, &articulation](short duration)
        {
            return fullDuration(duration, pitch, articulation);
        };
        
        if (noteDuration < leftoverDuration)
        { // fit entire note in measure
            lilypondCode += fd(noteDuration);
            lilypondCode += " ";
            leftoverDuration -= noteDuration;
        }
        else if (noteDuration == leftoverDuration)
        { // End of bar case.
            lilypondCode += fd(noteDuration);
            lilypondCode += " |\n";
            leftoverDuration = totalDuration;
        } else { // Split note into n bars case
            // Use up the rest of the duration in the current bar. 
            lilypondCode += fd(leftoverDuration);
            short remaining = noteDuration - leftoverDuration; // total - used
            lilypondCode += "~ |\n";
            // There is still more than a full bar of duration left.
            while (remaining > totalDuration) {
                lilypondCode += fd(totalDuration);
                remaining -= totalDuration;
                lilypondCode += "~ |\n";
            }
            if (totalDuration == remaining) { // exactly one bar left
                lilypondCode += fd(remaining);
                lilypondCode += " |\n";
                leftoverDuration = totalDuration;
            } else { // less than 1 bar left. 
                lilypondCode += fd(remaining);
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
                lilypondCode.erase(codelen - 3);
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

string Instrument::fullDuration(short duration, string absPitch, string articulation){
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
        return first16 + fullDuration(duration - 16, absPitch, articulation);
    }
    return "";
}

void Instrument::clearSfz(std::string& str) {
    const string from = "\\sfz";
    const string to = "";
    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // Move past the last replaced substring
    }
}

std::string Instrument::clamp(std::string n){
    Note note = Note(n);
    if (note < low_) {
        while (note < low_)
        {
            note = note.raise();
        }
    }
    else if (note > high_)
    {
        while (note > high_){
            note = note.lower();
        }
    }
    return note.str();
}

std::string Instrument::boulezJitter(){

    std::unique_lock lock{boulezMutex_};
    double value = boulezDist_(rng_);
    lock.unlock(); // unlocking here is faster than scoped_lock
    int octave = std::round(value);
    octave = std::clamp(octave, -2, 2);
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
        cerr << "Never Should reach here" << endl;
        break;
    }
    return "";
}

std::string Instrument::header(std::string title, std::string composer){
    std::string header = "\\header {\n\t title = \"";
    header += title;
    header += "\"\n\tsubtitile = \"Algorithmic Composition\"";
    // header += subtitile;
    header += "\n\tinstrument = \"";
    header += getName() + " " + to_string(getNum()) + "\"";
    header += "\n\tcomposer = \"";
    header += composer;
    header += "\"\n\ttagline = ##f}\n\n";
    return header;
}

void Instrument::makePart(std::string filename, std::string title, std::string composer){
    string fileContents = "\\version \"2.24.1\"\n\\language \"english\"\n\n";
    fileContents += "\\include \"definitions.ily\"\n\n";
    fileContents += header(title, composer);
    fileContents += "\\score {\n";
    fileContents += instrumentScoreBox(true);
    fileContents += "\t\\layout {\n\tindent = 2 \\cm\n\tshort-indent = 1\\cm\n\t}\n";
    fileContents += "}\n";
    std::ofstream out(filename);
    out << fileContents << endl;
}