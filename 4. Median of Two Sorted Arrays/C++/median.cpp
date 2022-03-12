///////////////////////////////////////////////////////////////////
// Michael Hayworth
// 3/11/2022
///////////////////////////////////////////////////////////////////
// median.cpp
// Find the median of two ordered arrays
///////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////
// Includes
///////////////////////////////////////////////////////////////////
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <math.h>

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
double findMedianSortedArrays(vector<int>&, vector<int>&);

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

    // Get the index to start and end of first array
    size_t begin1 = line.find('[');
    size_t end1 = line.find(']');
    // Cut out the array string for first array
    string vec1 = line.substr(begin1 + 1, end1 - begin1 - 1);
    // Get the index to start and end of first array
    size_t begin2 = line.find('[', end1 + 1);
    size_t end2 = line.find(']', end1 + 1);
    // Cut out the array string for second array
    string vec2 = line.substr(begin2 + 1, end2 - begin2 - 1);

    // Build the two integer arrays
    vector<int> array1 = getVector(vec1);
    vector<int> array2 = getVector(vec2);

    // Run algorithm
    double result = findMedianSortedArrays(array1, array2);

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
    // Push the last number to the list
    res.push_back(stoi(tempstr));

    return res;
}

///////////////////////////////////////////////////////////////////
// findMedianSortedArrays() -> finds median of two sorted arrays
//     Argument: nums1 & nums2 -> two sorted arrays
//     Return: median of the two arrays
///////////////////////////////////////////////////////////////////
double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
    // Set up pointers
    vector<int>::iterator nums1Curr = nums1.begin();
    vector<int>::iterator nums2Curr = nums2.begin();
    vector<int>::iterator curr;
    vector<int>::iterator prev = nums1.end();

    // Find the middle value of the two arrays
    int loc = ceil((nums1.size() + nums2.size()) / (double)2);
    cout << nums1.size() << " " << nums2.size() << " " << loc << endl;

    for(int i = 0; i < loc; ++i) {
        if(nums1Curr != nums1.end() && nums2Curr != nums2.end()) {
            if(*nums1Curr < *nums2Curr) {
                curr = nums1Curr;
                ++nums1Curr;
            }
            else {
                curr = nums2Curr;
                ++nums2Curr;
            }
        }
        else if(nums1Curr != nums1.end()) {
            curr = nums1Curr;
            ++nums1Curr;
        }
        else {
            curr = nums2Curr;
            ++nums2Curr;
        }

        if(i == loc - 1 && (nums1.size() + nums2.size()) % 2 == 0) {
            if(prev == nums1.end()) {
                ++loc;
                prev = curr;
            }
        }
    }

    if((nums1.size() + nums2.size()) % 2 == 0) {
        return (*curr + *prev) / (double)2;
    }
    else
        return (double)*curr;
}