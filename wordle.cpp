#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void findWord(unsigned int index, std::string input, std::string floating, const std::set<std::string>& dict, std::set<std::string>& results);
int numDashes(const std::string& word);

set<string> wordle(const string& in, const string& floating, const set<string>& dict)
{
    std::set<std::string> results; //init return set
    std::string input = in; //send in a copy of string
    std::string floats = floating; //send in a copy of floating letters
    findWord(0, input, floats, dict, results); //pass in index, 
    return results; 
}

int numDashes(const std::string& word)
{
    int num = 0;
    for(int i = 0; i < word.length(); i++)
    {
        num += (int)(word[i] == '-');
    }
    return num;
}

void findWord(unsigned int index, std::string input, std::string floating, const std::set<std::string>& dict, std::set<std::string>& results)
{
    //base case - word has all letters found (floating letters are used)
    if(index == input.size()) 
    {
        //if all the floating letters are used and if current is a valid word
        if(floating.empty() == 0 && dict.find(input) != dict.end()) 
        {
            //add to results
            results.insert(input);
        }
        return;
    }

    //if the letter is fixed, IE doesn't have a dash
    if(input[index] != '-') 
    {
        //go to next letter
        findWord(index + 1, input, floating, dict, results);
        //return; //added a return to kick out
    }

    else 
    {
        //count the number of dashes to reduce the amount of letters guessed, no wasted checks)

        //guess dash letters by putting in floating letters 
        for(int i = 0; i < floating.length(); i++) 
        {
            input[index] = floating[i]; //try first floating letter
            // //get the rest of the letters
            std::string new_floats = floating.substr(0, i) + floating.substr(i + 1); //save the floating letters
            findWord(index + 1, input, new_floats, dict, results); //feed in next as the floating argument
        }

        //condition is necessary to make efficient
        if(numDashes(input) >= floating.length()) //if there are more dashes than letters left to guess from...
        {
            for(int c = (int)'a'; c <= (int)'z'; c++) //now guess through alphabet, since its not a floating letter
            {
                input[index] = char(c); //guess the letter
                findWord(index + 1, input, floating, dict, results); //recurse again
            }
        }
    }
    
}