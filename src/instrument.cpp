#include "instrument.hpp"

using namespace std;

Instrument::Instrument(AnalysisMatrix *pitch, AnalysisMatrix *rhythm, AnalysisMatrix *articulation, std::vector<short> dynamics) : pitches_{pitch}, rhythms_{rhythm}, articulations_{articulation}, dynamicsRow_{dynamics} {}

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
    const short totalDuration = 16; // ts_.num16ths();
    string lilypondCode = "";
    for (size_t note = 0; note < 12; ++note)
    {
        short noteDuration = rhythms[note];
        string pitch = pitchMap_[pitches[note]];
        string articulation = articulationMap_[articulations[note]];
        string jitter = ""; //boulezJitter();
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