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
    std::set<std::string> results; //init return set
    //std::string input = in; //send in a copy of string
    //std::string floats = floating; //send in a copy of floating letters
    findWord(0, in, floating, dict, results); //pass in index, 
    return results; 
}

int countDashes(const std::string& word, int index)
{
    int num = 0;
    for(int i = index; i < word.size(); i++)
    {
        if(word[i] == '-')
        {
            ++num;
        }
    }
    return num;
}

void findWord(int index, std::string input, std::string floating, const set<string>& dict, std::set<std::string>& results)
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
        findWord(input, index + 1, floating, dict, results);
        return; //added a return to kick out
    }

    // else 
    // {
        //count the number of dashes to reduce the amount of letters guessed, no wasted checks)
        int num_dashes = countDashes(input, index);

        //guess dash letters by putting in floating letters 
        std::set<char> letters_used;
        for(int i = 0; i < floating.length(); i++) 
        {
            char c = floating[i];
            if(letters_used.count(c))
            {
                continue;
            }
            letters_used.insert(c); //add to the set of letters used
            std::string next = input;
            next[index] = c;

            // //try first floating letter
            // input[index] = floating[i]; //set letter to the first floating
            // //get the rest of the letters
            std::string new_floats = floating.substr(0, i) + floating.substr(i + 1); //save the floating letters
            findWord(index + 1, next, new_floats, dict, results); //feed in next as the floating argument
        }

        //condition is necessary to make efficient
        if(num_dashes >= floating.length()) //if there are more dashes than letters left to guess from...
        {
            for(char c = 'a'; c <= 'z'; c++) //now guess through alphabet, since its not a floating letter
            {
                if(floating.find(c) != std::string::npos || letters_used.count(c)) //if the letter is a floating letter, skip it
                {
                    continue;
                }

                //redo same case
                std::string next = input;
                next[index] = c;

                //input[index] = char(c); //guess the letter
                findWord(index + 1, next, floating, dict, results); //recurse again
            }
        }
    // }
    
}