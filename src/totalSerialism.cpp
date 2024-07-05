#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <future>
#include "analysisMatrix.hpp"
#include "serialismGenerator.hpp"

#define PARALLEL true

using namespace std;

void printCommands();

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

    vector<string> rightCode;
    vector<string> leftCode;
    // Parallelize!

    #if PARALLEL
    auto gen = [&generator](bool rh, vector<string>& lilypondCode)
    {
        generator->generatePiece(rh, lilypondCode);
    };

    // Do right and left in parallel
    thread right(gen, true, std::ref(rightCode));
    gen(false, leftCode);
    

    right.join();
    #else
    generator->generatePiece(true, rightCode);
    generator->generatePiece(false, leftCode);
    #endif
    // Continue working on the main thread if right hand isn't finished
    outputFile << header;
    // right.join
    for (auto &line : rightCode)
    {
        outputFile << line;
    }
    for (auto& line:leftCode){
        outputFile << line;
    }

    delete generator;
    return 0;
}

void printCommands(){
    cout << "Command Line options: " << endl;
    cout << "-s [SEED]: Sets the seed for random music to SEED. Cannot specify output or input files" << endl;
    cout << "-i [INPUT-FILENAME]: Sets the input filename for generating sheet music." << endl;
    cout << "-o [OUTPUT-FILENAME]: Specifies the output name of the score. " << endl;
}