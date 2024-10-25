#include <iostream>
#include <fstream>
#include <string>
#include <getopt.h>
#include "serialismGenerator.hpp"

using namespace std;

int main(int argc, char** argv){

    std::unique_ptr<SerialismGenerator> generator;
    string outputFilename = "";
    string inputFilename = "";
    size_t seed = 0;
    bool parts = false;

    while (true){
        switch (getopt(argc, argv,"i:o:s:p")){
            case -1:
                break;
            case 'i':
                inputFilename = optarg;
                continue;
            case 'o':
                outputFilename = optarg;
                continue;
            case 's':
                seed = atoi(optarg);
                continue;
            case 'p':
                parts = true;
            default:
                break;
        }
        break;
    }

    // Deduce the constructor
    if (argc == 1) { // no args given
        outputFilename = "random_score.ly";
        generator = make_unique<SerialismGenerator>(outputFilename);
    } else if (seed) {
        outputFilename = "random_score_seed_" + to_string(seed) + ".ly";
        generator = make_unique<SerialismGenerator>(seed, outputFilename, 8, parts);
    } else if ((inputFilename!= "") or (outputFilename!= "")){
        generator = make_unique<SerialismGenerator>(inputFilename, outputFilename, parts);
    } else {
        cerr << "Incorrect Arguments: Input filename and Output filename must be specified" << endl;
        exit(1);
    }

    generator->run();

    return 0;
}
