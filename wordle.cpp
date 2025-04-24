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

set<string> wordle(const string& in, const string& floating, const set<string>& dict)
{
    set<string> results; //init return set
    std::string input = in; //send in a copy 
    findWord(0, input, floating, dict, results); //pass in index, 
    return results; 
}

void findWord(int index, string input, string& floating, const set<string>& dict, set<string>& results)
{
    //base case - word has all letters found (floating letters are used)
    if(index == input.size()) 
    {
        //if all the floating letters are used and if current is a valid word
        if(floating.empty() && dict.find(input) != dict.end()) 
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
        findWord(input, index + 1, floating, dict, results);
    }

    else 
    {
        //count the number of dashes to reduce the amount of letters guessed, no wasted checks)
        int num_dashes = 0;
        for(int i = 0; i < input.size(); ++i)
        {
            //increment the number of dashes in "in"
            if(input[i] == '-')
            {
                num_dashes++;
            }
        }

        //guess dash letters by putting in floating letters 
        for(int i = 0; i < floating.size(); ++i) 
        {
            //try first floating letter
            input[index] = floating[i]; //set letter to the first floating
            //get the rest of the letters
            std::string next = floating.substr(0, i) + floating.substr(i + 1); //save the floating letters
            findWord(index + 1, input, next, dict, results); //feed in next as the floating argument
        }

        //condition is necessary to make efficient
        if(num_dashes > floating.size()) //if there are more dashes than letters left to guess from...
        {
            for(char c = 'a'; c <= 'z'; ++c) //now guess through alphabet, since its not a floating letter
            {
                if(floating.find(c) != std::string::npos) //dont guess a letter thats in floating (or what is left of it)
                {
                    continue;
                }
                input[index] = c; //guess the letter
                findWord(index + 1, input, floating, dict, results); //recurse again
            }
        }
    }
    
}