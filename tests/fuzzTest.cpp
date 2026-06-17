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

    fuzzTest(numTests, maxConcurrent);
}
void fuzzTest(size_t numTests, size_t maxConcurrent){

    long seed = 1;
    ThreadPool t(maxConcurrent);

    // Submit to Queue
    std::vector < std::future<bool>> futures(numTests);
    std::vector<size_t> failures;
    for (size_t seed = 1; seed < numTests + 1; seed++)
    {
        futures[seed-1] = t.submit([seed] {return threadFunc(seed); });
    }

    // Get the failed tests
    for (size_t i = 0; i < numTests; ++i)
    {
        bool result = futures[i].get();
        if (!result){
            failures.push_back(i + 1);
        }
    }

    // Evaluate
    if (failures.empty()){
        std::string message = "All " + to_string(numTests - 1) + " Tests Pass!";
        std::cout << "\033[;32mAll " << numTests << " Tests Pass!\033[0m" << endl;
        // Clear out entire fuzz test directory
        fs::remove_all("fuzz");
    }
    else
    {
        for (const auto& fail : failures){
            std::cout << "\033[1;31mFailed random test with seed " << fail << "\033[0m" << endl;
            std::cout << "Lilypond Error log can be found in the file \"fuzz/err" 
                    << fail << ".txt\"\n" << endl;
            std::cout << "Command to recreate failure: sh score.sh " << fail << std::endl;
        }
    }
}

bool threadFunc(int s){
    std::string seed_str = to_string(s);
    std::string filename = "fuzz/" + seed_str + ".ly";
    std::string lpCommand = "lilypond -f pdf -o fuzz -l WARN fuzz/" + seed_str + ".ly 2>fuzz/err" + seed_str + ".txt";
    SerialismGenerator gen = SerialismGenerator(s, filename, 1);
    gen.run();
    // SECURITY NOTE: NO USER ACCESS TO THIS COMMAND
    system(lpCommand.data());

    // Evaluate Individual Test
    filename = "fuzz/err" + seed_str+ ".txt";
    fstream file{filename};
    if (file.peek() != std::ifstream::traits_type::eof()){
        return false;
    }else {
        fs::remove("fuzz/" + seed_str + ".ly");
        fs::remove("fuzz/" + seed_str + ".pdf");
        fs::remove("fuzz/err" + seed_str + ".txt");
        return true;
    }
}