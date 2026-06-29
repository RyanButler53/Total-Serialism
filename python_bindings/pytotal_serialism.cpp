#include <nanobind/nanobind.h>
#include <nanobind/stl/vector.h>
#include <nanobind/stl/string.h>
#include <nanobind/stl/filesystem.h>
#include <nanobind/operators.h>
#include <sstream>
#include <string>
#include "serialismGenerator.hpp"

namespace nb = nanobind;

using namespace nb::literals;

NB_MODULE(pytotal_serialism, m) {
    m.doc() = "Bindings for the Total Serialism Python gui";

    // Structs: Generator Inputs, SinglePartData, MultiPartData, run();

    nb::class_<GeneratorInputs>(m, "Inputs", "Generator Inputs")
    .def(nb::init<>(), "Constructs an empty inputs with no parameters")
    .def("__repr__", [](const GeneratorInputs& in){
        std::stringstream s;
        s << in.outputFilename_;
        return s.str();
        })
    .def_rw("pitches", &GeneratorInputs::pitches_ ,"Numbers of the pitches")
    .def_rw("rhythms", &GeneratorInputs::rhythms_ ,"Numbers of the rhythms")
    .def_rw("articulations", &GeneratorInputs::articulations_ ,"Numbers of articulations")
    .def_rw("tempo", &GeneratorInputs::tempo_ ,"Tempo")
    .def_rw("timeSig", &GeneratorInputs::timeSig_ ,"Time signature")
    .def_rw("title", &GeneratorInputs::title_ ,"Title")
    .def_rw("composer", &GeneratorInputs::composer_ ,"Composer name")
    .def_rw("outputPath", &GeneratorInputs::outputPath_ ,"Output directory")
    .def_rw("outputFilename", &GeneratorInputs::outputFilename_ ,"Filename of the score")
    .def_rw("singleParts", &GeneratorInputs::singleParts_ ,"Data for parts of single instruments")
    .def_rw("multiParts", &GeneratorInputs::multiParts_ ,"Data for multi instrument parts")
    .def_rw("boulezFactor", &GeneratorInputs::boulezFactor_ ,"Boulez randomness factor")
    .def_rw("parts", &GeneratorInputs::parts ,"Boolean whether not to export individual parts or not");


    nb::class_<PartData>(m, "SinglePartData", "Data for single part data")
    .def(nb::init<>(), "Constructs an empty Part Data with no parameters")
    .def("__repr__", [](const PartData& p){
        std::stringstream s;
        s << p.instrument;
        return s.str();
    })
    .def_rw("instrument", &PartData::instrument, "Instrument name")
    .def_rw("rowNums", &PartData::rowNums, "Row numbers")
    .def_rw("rowTypes", &PartData::rowTypes, "Row types")
    .def_rw("dynamics", &PartData::dynamics, "Dynamics");

    nb::class_<MultiPartData>(m, "MultiPartData", "Data for Piano and Harp")
    .def(nb::init<>(), "Constructs an empty Multi part data with no parameters")
    .def("__repr__", [](const MultiPartData& p){
        std::stringstream s;
        s << p.instrument;
        return s.str();
    })
    .def_rw("instrument", &MultiPartData::instrument, "Instrument name")
    .def_rw("rightRowNums", &MultiPartData::rightRowNums, "Row numbers Right")
    .def_rw("rightRowTypes", &MultiPartData::rightRowTypes, "Row types Right")
    .def_rw("leftRowNums", &MultiPartData::leftRowNums, "Row numbers left")
    .def_rw("leftRowTypes", &MultiPartData::leftRowTypes, "Row types left")
    .def_rw("dynamics", &MultiPartData::dynamics, "Dynamics");

    m.def("run", &TotalSerialism::run, "Driver function to run from the inputs");
};