#include "note.hpp"

using namespace std;
Note::Note(string pitch, int octave): octave_{octave}
{
    if (pitch == "c"){
        pitch_ = Note::Pitch::C;
    } else if (pitch == "cs") {
        pitch_ = Note::Pitch::CS;
    }else if (pitch == "d") {
        pitch_ = Note::Pitch::D;
    }else if (pitch == "ef") {
        pitch_ = Note::Pitch::EF;
    }else if (pitch == "e") {
        pitch_ = Note::Pitch::E;
    }else if (pitch == "f") {
        pitch_ = Note::Pitch::F;
    }else if (pitch == "fs") {
        pitch_ = Note::Pitch::FS;
    }else if (pitch == "g") {
        pitch_ = Note::Pitch::G;
    }else if (pitch == "af") {
        pitch_ = Note::Pitch::AF;
    }else if (pitch == "a") {
        pitch_ = Note::Pitch::A;
    }else if (pitch == "bf") {
        pitch_ = Note::Pitch::BF;
    }else if (pitch == "b") {
        pitch_ = Note::Pitch::B;
    } else {
        pitch_ = Note::Pitch::INVALID;
    }
}

bool Note::operator<(const Note& other) const {
    if (octave_ == other.octave_){
        return pitch_ < other.pitch_;
    } else {
        return octave_ < other.octave_;
    }
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