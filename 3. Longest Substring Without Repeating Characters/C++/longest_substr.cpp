///////////////////////////////////////////////////////////////////
// Michael Hayworth
// 3/10/2022
///////////////////////////////////////////////////////////////////
// add_two_nums.cpp
// Add two numbers using a singly linked list structure
///////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////
// Includes
///////////////////////////////////////////////////////////////////
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <math.h>

using namespace std;

///////////////////////////////////////////////////////////////////
// Declarations
///////////////////////////////////////////////////////////////////
void oops(const char*);
int lengthOfLongestSubstring(string);

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
    
    // Read in input line
    string line = string(istreambuf_iterator<char>(input), istreambuf_iterator<char>());

    // Close file
    input.close();

    // Run algorithm
    int result = lengthOfLongestSubstring(line);

    // Print result
    cout << result << endl;

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
// lengthOfLongestSubstring() -> gets length of longest substring
//                               without repeating characters
//     Argument: line -> line to scan for substring
//     Return: length of the substring
///////////////////////////////////////////////////////////////////
int lengthOfLongestSubstring(string line) {
    // Holds the locations of where characters were last seen
    vector<int> characters(128, 0);
    // Holds the final result
    int result = 0;
    // Holds the last location of a repeating character
    int k = 0;

    for(int i = 0; i < line.length(); ++i) {
        // Set k to the latest instance of a repeating character
        k = max(k, characters[line[i]]);
        // Set the last known position of this character in the array
        characters[line[i]] = i + 1;
        // Result is updated to either the previous result, or the length since the last repeating character
        result = max(result, i - k + 1);
    }

    return result;
}