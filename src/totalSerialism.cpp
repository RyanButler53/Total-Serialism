#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <regex>
#include "serialismGenerator.hpp"

using namespace std;

int main(int argc, char** argv){
    SerialismGenerator* generator;
    string outputFilename = "";
    string inputFilename = "";
    size_t seed = 0;

    if (argc == 1) { // no args given
        outputFilename = "random_score.ly";
        generator = new SerialismGenerator(outputFilename);

    } else if (argc == 2) { // gave seed
        seed = stoull(argv[1]);
        outputFilename = "random_score_seed_" + to_string(seed) + ".ly";
        generator = new SerialismGenerator(seed, outputFilename);

    } else if (argc == 3) { // gave input and output file
        outputFilename = argv[1];
        inputFilename = argv[2];        
        generator = new SerialismGenerator(inputFilename, outputFilename);
    }

    generator->run();
    delete generator;

    return 0;
}
