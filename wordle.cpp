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
    set<string> results;
    findWord(in, 0, floating, dict, results);
    return results;
}

void findWord(string current, int index, string floating, const set<string>& dict, set<string>& results)
{
    //base case - word has all letters found (floating letters are used)
    if(index == current.size()) 
    {
        //if all the floating letters are used and if current is a valid word
        if(floating.empty() && dict.find(current) != dict.end()) 
        {
            //add to results
            results.insert(current);
        }
        return;
    }

    //if the letter is fixed, doesn't have a dash
    if(current[index] != '-') 
    {
        //go to next letter
        findWord(current, index + 1, floating, dict, results);
        return;
    }

    //keep track of dashes left till end
    int dashes_left = 0;
    for(size_t i = index; i < current.size(); ++i)
    {
        //increase dash count if on a dash "letter"
        if(current[i] == '-')
        {
            dashes_left++;
        }
    }

    if((int)floating.size() > dashes_left)
    {
        return;
    }

    //guess dash letters by putting in floating letters 
    for(size_t i = 0; i < floating.size(); ++i) 
    {
        char c = floating[i];
        current[index] = c; //set letter to the first floating
        string next = floating; //save the floating letters
        next.erase(i, 1); //remove the letter used in floating
        findWord(current, index + 1, next, dict, results); //feed in next as the floating argument
    }

    // Try placing non-floating letters
    if((int)floating.size() < dashes_left)
    {
        for (char c = 'a'; c <= 'z'; ++c) 
        {
            if(floating.find(c) != string::npos) 
            {
                continue; //don't use floating again
            }
            current[index] = c;
            findWord(current, index + 1, floating, dict, results);
        }
    }
}