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
vector<int> twoSum(vector<int>&, int);

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

    // Get the index to start of array
    size_t begin = line.find('[');
    // Cut out the array string for getVector()
    string vec = line.substr(begin + 1, line.find(']') - begin - 1);
    
    // Break the string into an integer vector
    cout << vec << endl;
    vector<int> nums = getVector(vec);

    // Get the target value
    string targetString = line.substr(line.find("target = ") + 9, line.length() - 1);
    int target = stoi(targetString);

    // Run the algorithm
    vector<int> result = twoSum(nums, target);

    // Print results
    cout << '[' << result[0] << ", " << result[1] << ']' << endl;

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
// getVector() -> gets vector of integers from string list
//     Argument: vectorString -> vector string with numbers
//         -> Format => 1, 2, 3 
//     Return: vector of integers
///////////////////////////////////////////////////////////////////
vector<int> getVector(string vectorString) {
    vector<int> res;
    string tempstr;
    int i = 0;

    //Iterate through each character of the string
    while(i < vectorString.length()) {
        // If character is a ',' then push and clear the temp string
        if(vectorString[i] == ',') {
            res.push_back(stoi(tempstr));
            tempstr = "";
        }
        // If not, add character to the temp string
        else
            tempstr += vectorString[i];
        
        ++i;
    }
    res.push_back(stoi(tempstr));

    return res;
}

///////////////////////////////////////////////////////////////////
// twoSum() -> finds two integers in vector that add up to target
//     Argument: array -> array of integers
//         -> Note: array must have exactly one solution
//     Return: two integers that add up to target in vector form
///////////////////////////////////////////////////////////////////
vector<int> twoSum(vector<int>& array, int target) {
    vector<int> res;

    // Indexes for the front and back of the array
    vector<int>::iterator front = array.begin();
    vector<int>::iterator back = prev(array.end());

    // Loop until the front is the last element in the array
    while(front != array.end()) {
        // Loop until the back is pointing to the front element
        while(back != front) {
            // If they add up to the target, return the two indeces
            if(*front + *back == target) {
                res.push_back(front - array.begin());
                res.push_back(back - array.begin());
                return res;
            }
            // Move back toward the front
            --back;
        }
        // Move front toward the back
        ++front;
        // Set the bck to the end
        back = prev(array.end());
    }

    return res;
}