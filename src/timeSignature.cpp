#include "timeSignature.hpp"

TimeSignature::TimeSignature(std::string ts):str_{ts}
{
    // Split the ts string into numBeats and measureLength
    int slash = ts.find('/');
    numBeats_ = stoi(ts.substr(0, slash));
    beatLen_ = stoi(ts.substr(slash+ 1));

}

bool TimeSignature::isValid() const {
    if (beatLen_ == 2){
        return numBeats_ == 3; 
    } else if (beatLen_ == 4) {
        return (numBeats_ < 8 and numBeats_ > 0);
    } else if (beatLen_ == 8) {
        if (numBeats_ % 2 == 1 and (2 < numBeats_) and (numBeats_ < 16)){
            return true;
        } else {
            return numBeats_ == 6 or numBeats_ == 12;
        }
    } else {
        return false;
    }
}

std::string TimeSignature::str() const {
    return str_;
}

short TimeSignature::num16ths() const{
    return 16 / beatLen_ * numBeats_;
}

unsigned int TimeSignature::getNumBeats()const{
    return numBeats_;
}

unsigned int TimeSignature::getBeatLen() const {
    return beatLen_;
}