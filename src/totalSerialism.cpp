#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <regex>
#include "analysisMatrix.hpp"
#include "timeSignature.hpp"
#include "instrument.hpp"
#include "piano.hpp"
#include "serialismGenerator.hpp"

using namespace std;

int main(int argc, char** argv){
    SerialismGenerator* generator;
    string outputFilename = "";
    string inputFilename = "";
    size_t seed = 0;

    if (argc == 1)
    { // no args given
        generator = new SerialismGenerator();
        outputFilename = "random_score.ly";
    }
    else if (argc == 2)
    { // gave seed
        seed = stoull(argv[1]);
        generator = new SerialismGenerator(seed);
        outputFilename = "random_score_seed_" + to_string(seed) + ".ly";
    }
    else if (argc == 3)
    { // gave input and output file
        outputFilename = argv[1];
        inputFilename = argv[2];        
        generator = new SerialismGenerator(inputFilename);
    }

    ofstream outputFile(outputFilename);
    string header = generator->header();
    std::string scoreBox = generator->scoreBox();
    // vector<string> rightCode;
    // vector<string> leftCode;
    vector<string> lilypondCode;
    // Parallelize!

    // auto gen = [&generator](bool rh, vector<string>& lilypondCode)
    // {
    //     generator->generatePiece(rh, lilypondCode);
    // };

    // Do right and left in parallel
    // std::thread right(gen, true, std::ref(rightCode));
    // gen(true, rightCode);
    // gen(false, leftCode);
    generator->generatePiece(lilypondCode);

    // Continue working on the main thread if right hand isn't finished
    outputFile << header;
    // right.join();

    // Write to file
    for (auto &line : lilypondCode) {
        outputFile << line;
    }
    // outputFile << "\n";
    // for (auto &line : leftCode)
    // {
    //     outputFile << line;
    // }
    // outputFile << scoreBox;

    delete generator;
    return 0;
}
