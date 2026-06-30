#pragma once

#include <vector>
#include <string>

/**
 * @brief Struct containing Part data
 * 
 */
struct PartData {
    std::string instrument;
    std::vector<short> rowNums;
    std::vector<std::string> rowTypes;
    std::vector<short> dynamics;
};

/**
 * @brief Struct containing part data for Piano and harp
 * 
 */
struct MultiPartData {
    std::string instrument;
    std::vector<short> rightRowNums;
    std::vector<std::string> rightRowTypes;
    std::vector<short> leftRowNums;
    std::vector<std::string> leftRowTypes;
    std::vector<short> dynamics;
};


/**
 * @brief Struct to hold the things that the serialism generator 
 * typically would get from an input file. 
 * 
 */
struct GeneratorInputs {
    std::vector<short> pitches_;
    std::vector<short> rhythms_;
    std::vector<short> articulations_;
    short tempo_;
    std::string timeSig_;
    std::string title_;
    std::string composer_;
    std::string outputPath_;
    std::string outputFilename_;
    std::vector<PartData> singleParts_;
    std::vector<MultiPartData> multiParts_;
    float boulezFactor_;
    bool parts;
};
