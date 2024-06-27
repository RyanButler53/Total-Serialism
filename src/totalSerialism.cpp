#include <iostream>
#include <fstream>
#include <string>
#include "analysisMatrix.hpp"
#include "serialismGenerator.hpp"

using namespace std;

void printCommands();

int main(int argc, char** argv){
    SerialismGenerator* generator;
    string outputFilename = "";
    string inputFilename = "";
    size_t seed = 0;
    if (argc == 3)
    { // gave input and output file
        outputFilename = argv[1];
        inputFilename = argv[2];
    }
    else if (argc == 2)
    { // gave seed
        seed = stoull(argv[1]);
    }
    else {
        cerr << "Incorrect Script use" << endl;
        exit(1);
    }

    // Construct appropriate generator
    if (seed == 0){ // Gave inputfile, no output or seed. 
        generator = new SerialismGenerator(inputFilename);
    }
    else {
        generator = new SerialismGenerator(seed);
        outputFilename = "random_score_seed_" + to_string(seed) + ".ly";
    }

    ofstream outputFile(outputFilename);
    string header = generator->header();
    
    // Parallelize!
    vector<string> rh = generator->generatePiece(true);
    vector<string> lh = generator->generatePiece(false);
    outputFile << header;
    for (auto &line : rh)
    {
        outputFile << line;
    }
    for (auto& line:lh){
        outputFile << line;
    }

    delete generator;
    return 0;
}

void printCommands(){
    cout << "Command Line options: " << endl;
    cout << "-s [SEED]: Sets the seed for random music to SEED. Cannot specify output or input files" << endl;
    cout << "-i [INPUT-FILENAME]: Sets the input filename for generating sheet music." << endl;
    cout << "-o Specifies the output name of the score. " << endl;
}