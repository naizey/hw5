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
    // Base case: word is fully built
    if (index == current.size()) 
    {
        if (floating.empty() && dict.find(current) != dict.end()) 
        {
            results.insert(current);
        }
        return;
    }

    // If fixed letter, skip to next
    if (current[index] != '-') 
    {
        findWord(current, index + 1, floating, dict, results);
        return;
    }

    // Try placing floating letters first
    for (size_t i = 0; i < floating.size(); ++i) 
    {
        char c = floating[i];
        current[index] = c;
        string nextFloating = floating;
        nextFloating.erase(i, 1); // remove used floating letter
        findWord(current, index + 1, nextFloating, dict, results);
    }

    // Try placing non-floating letters
    for (char c = 'a'; c <= 'z'; ++c) 
    {
        if (floating.find(c) != string::npos) 
            continue; // don't use floating again
        current[index] = c;
        findWord(current, index + 1, floating, dict, results);
    }
}