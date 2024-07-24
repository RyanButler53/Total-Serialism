#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>
#include <vector>

using namespace std;

int main(int argc, char **argv)
{
    if (argc == 1){
        std::cout << "No args given" << std::endl;
        cout << "\033[1;31mbold" << 5 << " text\033[0m\n";
        return 1;
    }
    int numTests = stoi(argv[1]);
    vector<int> failedTests;
    vector<string> passedTests;
    for (int test = 1; test < numTests + 1; ++test) {
        string filename = "fuzz/err" + to_string(test) + ".txt";
        fstream file{filename};
        if (file.peek() != std::ifstream::traits_type::eof()){
            failedTests.push_back(test);
        } else {
            passedTests.push_back(filename);
        }
    }
    for (const auto& pass : passedTests){
        std::filesystem::remove(pass);
    }
    if (failedTests.empty()){
        std::string message = "All " + to_string(numTests - 1) + " Tests Pass!";
        //"\033[1;31mbold" << 5 << " text\033[0m\n"
        std::cout << "\033[;32mAll " << numTests << " Tests Pass!\033[0m" << endl;
    }
    else
    {
        for (const auto& fail : failedTests){
            std::cout << "\033[1;31mFailed random test with seed " << fail << "\033[0m" << endl;
            std::cout << "Lilypond Error log can be found in the file \"fuzz/err" << fail << ".txt\"\n"
                    << endl;
        }
    }
    return 0;
}