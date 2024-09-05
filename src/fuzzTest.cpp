#include "fuzzTest.hpp"
#include <iostream>
#include <string>
#include <stddef.h>
#include <filesystem>
#include <fstream>
#include <vector>
#include <thread>

using namespace std;
namespace fs = std::filesystem;

int main(int argc, char** argv){
    size_t numTests = 10;
    size_t maxConcurrent = 5;
    if (argc < 2)
    {
        std::cout << "No args given" << std::endl;
        std::cout << "Running 10 Tests with 5 processes" << std::endl;
    }
    else if (argc < 3)
    {
        numTests = stoi(argv[1]);
        cout << "No number of processes given. Calling 5 processes at once" << endl;
    } else if (argc < 4){
        numTests = stoi(argv[1]);
        maxConcurrent = stoi(argv[2]);
    } else {
        cout << "Usage: build/fuzzTest <numTests> <maxConcurrent>" << endl;
        exit(1);
    }

    if (fs::exists("fuzz")){
        fs::remove_all("fuzz");
    }
    fs::create_directory("fuzz");

    launch(numTests, maxConcurrent);
    evaluate(numTests);
}
void launch(size_t numTests, size_t maxConcurrent){

    long seed = 1;
    ThreadPool t(maxConcurrent);
    for (size_t seed = 1; seed < numTests+1; seed++) {
        t.submit([seed] { threadFunc(seed); });
    }
    t.run();
    // Wait for all tests to run in parallel
    while(!t.isDone()){}
}

void evaluate(size_t numTests)
{
    vector<int> failedTests;
    vector<string> passedTests;
    for (size_t test = 1; test < numTests + 1; ++test) {
        string filename = "fuzz/err" + to_string(test) + ".txt";
        fstream file{filename};
        if (file.peek() != std::ifstream::traits_type::eof()){
            failedTests.push_back(test);
        } else {
            passedTests.push_back(filename);
            // Clear out the ly, error log, pdf of passed tests
            string s = to_string(test);
            fs::remove("fuzz/" + s + ".ly");
            fs::remove("fuzz/" + s + ".pdf");
            fs::remove("fuzz/err" + s + ".txt");
        }
    }
    for (const auto& pass : passedTests){
        std::filesystem::remove(pass);
    }
    if (failedTests.empty()){
        std::string message = "All " + to_string(numTests - 1) + " Tests Pass!";
        std::cout << "\033[;32mAll " << numTests << " Tests Pass!\033[0m" << endl;
        // Clear out entire fuzz test directory
        fs::remove_all("fuzz");
    }
    else
    {
        for (const auto& fail : failedTests){
            std::cout << "\033[1;31mFailed random test with seed " << fail << "\033[0m" << endl;
            std::cout << "Lilypond Error log can be found in the file \"fuzz/err" 
                    << fail << ".txt\"\n" << endl;
            std::cout << "Command to recreate failure: sh score.sh " << fail << std::endl;
        }
    }
}

void threadFunc(int s){
    std::string seed_str = to_string(s);
    std::string filename = "fuzz/" + seed_str + ".ly";
    std::string lpCommand = "lilypond -f pdf -o fuzz -l WARN fuzz/" + seed_str + ".ly 2>fuzz/err" + seed_str + ".txt";
    SerialismGenerator gen = SerialismGenerator(s, filename, 1);
    gen.run();
    // SECURITY NOTE: NO USER ACCESS TO THIS COMMAND
    system(lpCommand.data());
}