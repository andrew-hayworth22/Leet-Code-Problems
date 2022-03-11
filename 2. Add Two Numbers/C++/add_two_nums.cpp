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

using namespace std;

///////////////////////////////////////////////////////////////////
// Definitions
///////////////////////////////////////////////////////////////////
#define LINE_LEN 999

///////////////////////////////////////////////////////////////////
// List node definition
///////////////////////////////////////////////////////////////////
struct node {
    int val;
    node* next;
    node() : val(0), next(nullptr)                  {}
    node(int x) : val(x), next(nullptr)             {}
    node(int x, node* next) : val(x), next(next)    {}
};

///////////////////////////////////////////////////////////////////
// Declarations
///////////////////////////////////////////////////////////////////
void oops(const char*);
vector<int> getVector(string);
node* buildList(vector<int>&);
node* addTwoNumbers(node*, node*);
void printList(node*);

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

    // Build singly-linked lists with arrays
    node* l1 = buildList(array1);
    node* l2 = buildList(array2);

    // Run algorithm
    node* result = addTwoNumbers(l1, l2);

    // Print results
    printList(result);

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
// buildList() -> builds a singly-linked list with a vector of ints
//     Argument: vector -> vector of integers
//     Return: pointer to the first element of singly linked list
///////////////////////////////////////////////////////////////////
node* buildList(vector<int>& vec) {
    // First node of the list
    node* head = new node(vec.front());
    // Pointer to the previous node created
    node* prev = head;
    // Temporary node to 
    node* temp;

    // Iterate through the vector
    for(vector<int>::iterator it = vec.begin(); it != vec.end(); ++it) {
        // If we are past the first element, create node and set previous
        // pointer's next to the new node
        if(it != vec.begin()) {
            temp = new node(*it);
            prev->next = temp;
            prev = temp;
        }
    }
    return head;
}

///////////////////////////////////////////////////////////////////
// addTwoNumbers() -> adds numbers using singly linked list
//     Arguments: l1 and l2 -> singly linked list head nodes
//     Return: head node for resulting list
///////////////////////////////////////////////////////////////////
node* addTwoNumbers(node* l1, node* l2) {
    node* result = new node();
    node* resultCurr = result;

    // Iterate through all of the list elements of each
    while(l1 != nullptr || l2 != nullptr) {
        // If there are remaining elements in l1. add it to result
        if(l1 != nullptr) {
            resultCurr->val += l1->val;
            l1 = l1->next;
        }
        // If there are remaining elements in l2. add it to result
        if(l2 != nullptr) {
            resultCurr->val += l2->val;
            l2 = l2->next;
        }
        // Carry over the remainder to the next element
        if(resultCurr->val >= 10) {
            resultCurr->next = new node(resultCurr->val / 10);
            resultCurr->val %= 10;
        }
        // Initialize next result node if needed
        else if(l1 != nullptr || l2 != nullptr)
            resultCurr->next = new node();
        
        resultCurr = resultCurr->next;
    }

    return result;
}

///////////////////////////////////////////////////////////////////
// printList() -> prints a singly-linked list
//     Arguments: list -> head node of list to print
///////////////////////////////////////////////////////////////////
void printList(node* list) {
    string res = "[";

    while(list != nullptr) {
        res += to_string(list->val) + ",";
        list = list->next;
    }
    res[res.length() - 1] = ']';

    cout << res << endl;
}