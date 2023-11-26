#include <iostream>
#include <fstream>
#include <string>
#include "analysisMatrix.hpp"
#include "serialismGenerator.hpp"

using namespace std;

void printCommands();

int main(int argc, char** argv){
    SerialismGenerator *generator;
    string outputFilename = "";
    string inputFilename = "";
    size_t seed = 0;
    if (argc == 1) // No command line arguments case
    {
        generator = new SerialismGenerator;
        outputFilename = "randomScore.ly";
        cout << "Outputting Lilypond to " << outputFilename << endl;
    } else {
        // Parse arguments;
        for (int arg_i = 1; arg_i < argc; ++arg_i)
        {
            if (!strcmp(argv[arg_i], "-o") and arg_i+1 != argc){
                outputFilename = argv[arg_i+1];
            } else if (!strcmp(argv[arg_i],"-i") and arg_i+1 != argc) {
                inputFilename = argv[arg_i+1];
            } else if (!strcmp(argv[arg_i],"-s") and arg_i+1 != argc){
                seed = strtoul(argv[arg_i+1], nullptr,10);
            } else if (!strcmp(argv[arg_i], "-h"))
            {
                printCommands();
                exit(0);
            }
        }

        // Construct appropriate generator
        if (seed == 0){ // Gave inputfile, no output or seed. 
            if (outputFilename == ""){
                cout << "No output file given." << endl;
            } else if (inputFilename == "") {
                cout << "No input file given." << endl;
            }
            generator = new SerialismGenerator(inputFilename);
        }
        else {
            generator = new SerialismGenerator(seed);
            outputFilename = "random_score_seed_" + to_string(seed) + ".ly";
        }
    }

    ofstream outputFile(outputFilename);
    string header = generator->header();
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