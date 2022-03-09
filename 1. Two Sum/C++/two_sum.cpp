///////////////////////////////////////////////////////////////////
// Michael Hayworth
// 3/9/2022
///////////////////////////////////////////////////////////////////
// two_sum.cpp
// Given two arrays, finds two elements such that
// they add up to a target
///////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////
// Includes
///////////////////////////////////////////////////////////////////
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

///////////////////////////////////////////////////////////////////
// Definitions
///////////////////////////////////////////////////////////////////
#define LINE_LEN 999

///////////////////////////////////////////////////////////////////
// Declarations
///////////////////////////////////////////////////////////////////
void oops(const char*);
vector<int> getVector(string);

///////////////////////////////////////////////////////////////////
// main() -> program entry point
//     Argument: input file name
///////////////////////////////////////////////////////////////////
int main(int argc, char* argv[]) {
    // Verify input parameter
    if(argc != 2)
        oops("Invalid input");

    // Open up input file
    ifstream input;
    input.open(argv[1]);

    // Verify that the file is open
    if(!input.is_open())
        oops("Could not open file");
    
    // Read in line
    string line = string(istreambuf_iterator<char>(input), istreambuf_iterator<char>());

    // Get the indext to start array string
    size_t begin = line.find('[');
    // Cut out the array string
    string vec = line.substr(begin + 1, line.find(']') - begin - 1);
    
    // Break the string into an integer vector
    vector<int> nums = getVector(vec);
    // Get the target
    string targetString = line.substr(line.find("target = ") + 9, line.length() - 1);
    int target = stoi(targetString);
    cout << nums[0] << endl;

    // Close file
    input.close();

    return 0;
}

///////////////////////////////////////////////////////////////////
// oops() -> error handling wrapper
//     Argument: message -> error message to print
///////////////////////////////////////////////////////////////////
void oops(const char* message) {
    // Print message and exit
    cerr << "ERROR: " << message << endl;
    exit(1);
}

///////////////////////////////////////////////////////////////////
// getVector() -> gets vector of integers from string
//     Argument: vectorString -> vector string with numbers
//     Return: vector of integers
///////////////////////////////////////////////////////////////////
vector<int> getVector(string vectorString) {
    
}