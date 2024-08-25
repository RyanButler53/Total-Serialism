#include "note.hpp"

using namespace std;
Note::Note(string pitch, int octave):pitch_{strToPitch(pitch)}, octave_{octave},str_{pitch}
{
    if (octave_ > 0){
        for (size_t x = 0; x < octave_; ++x){
            str_ += "'";
        }
    } else if (octave_ < 0){
        for (size_t x = 0; x < std::abs(octave_); ++x){
            str_ += ",";
        } 
    }
}

Note::Note(std::string str):pitch_{Note::Pitch::INVALID},octave_{0}, str_{str}{

    for (std::reverse_iterator i = str.rbegin(); i != str.rend(); ++i){
        if (*i == '\''){
            ++octave_;
        } else if (*i == ','){
            --octave_;
        } else{
            break;
        }
    }
    std::string pitchStr;
    pitchStr = str.substr(0, str.length() - abs(octave_));
    pitch_ = strToPitch(pitchStr);
}

Note::Note(Pitch pitch, int octave, std::string str) : pitch_{pitch}, octave_{octave}, str_{str} {}

Note::Pitch Note::strToPitch(std::string pitch){
    if (pitch == "c"){
        return Note::Pitch::C;
    } else if (pitch == "cs") {
        return Note::Pitch::CS;
    }else if (pitch == "d") {
        return Note::Pitch::D;
    }else if (pitch == "ef") {
        return Note::Pitch::EF;
    }else if (pitch == "e") {
        return Note::Pitch::E;
    }else if (pitch == "f") {
        return Note::Pitch::F;
    }else if (pitch == "fs") {
        return Note::Pitch::FS;
    }else if (pitch == "g") {
        return Note::Pitch::G;
    }else if (pitch == "af") {
        return Note::Pitch::AF;
    }else if (pitch == "a") {
        return Note::Pitch::A;
    }else if (pitch == "bf") {
        return Note::Pitch::BF;
    }else if (pitch == "b") {
        return Note::Pitch::B;
    } else {
        return Note::Pitch::INVALID;
    }
}

string Note::str(){
    return str_;
}

bool Note::operator<(const Note& other) const {
    if (octave_ == other.octave_){
        return pitch_ < other.pitch_;
    } else {
        return octave_ < other.octave_;
    }
}

Note Note::raise(){
    if (octave_ >= 0){
        str_ += "'";
    } else {
        str_.pop_back();
    }
    return Note(pitch_, octave_ + 1, str_);
}

Note Note::lower(){
    if (octave_ <= 0){
        str_ += ",";
    } else {
        str_.pop_back();
    }
    return Note(pitch_, octave_ - 1, str_);
}

bool Note::operator==(const Note& other) const {
    return (octave_ == other.octave_) and (pitch_ == other.pitch_);
}

bool Note::operator!=(const Note& other) const {
    return !(*this == other);
}

bool Note::operator>(const Note& other) const {
    if (*this != other){
        return !(*this < other);
    } else {
        return false;
    }
}