#####################################################################
# Michael Hayworth
# 3/11/2022
#####################################################################
# two_sum.py
# Given two arrays, finds two elements such that
# they add up to a target
#####################################################################

#####################################################################
# Imports
#####################################################################
import sys
import typing
import re

#####################################################################
# twoSum -> find two elements that add up to target
#    Parameter: nums -> array of integers
#               target -> integer that elements add up to
#    Returns: array with indices of elements that add up to target
#####################################################################
def twoSum(nums: typing.List[int], target: int) -> typing.List[int] :
    # List to hold addresses of numbers
    numbers = {}

    # Iterate over list
    for i in range(len(nums)) :
        # Calculate difference between target and the current number
        diff = target - nums[i]

        # If the difference is in the list, we know they add up to
        # make the target
        if diff in numbers :
            return [i, numbers[diff]]
        
        # If not, add the index of the current number to the list
        numbers[nums[i]] = i
            
#####################################################################
# buildList -> builds list from string
#    Parameter: string -> string to build list from
#    Returns: built list of integers
#####################################################################
def buildList(string) :
    # Split the string on ,
    list = string.split(',')

    # Append every element to the result
    result = []
    for x in list :
        result.append(int(x))
    
    return result

#####################################################################
# assertion -> throw an error if a boolean is not true
#    Parameters: boolean -> if false, then throws an error
#                errorString -> string to print if error is thrown
#####################################################################
def assertion(boolean, errorString) :
    # Print error and exit if assertion is false
    if boolean is False:
        print("ERROR: " + errorString)
        exit(1)

#####################################################################
# main -> main flow of the program
#####################################################################
def main() :
    # Ensure the correct input
    assertion(sys.argv.__len__() == 2, "Incorrect input")
    
    # Open file and read input
    with open(sys.argv[1]) as f :
        line = f.readline()
    
    # Split input on delimiters
    split = re.split(r"\[|\]| ", line)

    # Get array and target from split input
    array = buildList(split[3])
    target = int(split.pop())

    # Run and print algorithm
    result = twoSum(array, target)
    print(result)

# Run the main flow
main()