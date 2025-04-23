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

    set<string> dictCopy;
    for(set<string>::iterator it = dict.begin(); it != dict.end(); ++it)
    {
        if(it->length() == in.length())
        {
            dictCopy.insert(*it);
        }
    }
    string current = in;
    findWord(in, current, 0, floating, dictCopy, results);
    return results;
}

void findWord(const string& input, string& current, size_t index, const string& floating, const set<string>& dict, set<string>& results)
{
    //base case - word has all letters found (floating letters are used)
    if(index == input.size()) 
    {
        //if all the floating letters are used and if current is a valid word
        if(dict.find(current) != dict.end())
        {
            results.insert(current);
        }
        return;
    }

    //if the letter is fixed, doesn't have a dash
    if(input[index] != '-') 
    {
        current[index] = input[index];
        //go to next letter
        findWord(input, current, index + 1, floating, dict, results);
        return;
    }

    //keep track of dashes left till end
    size_t dashes_left = 0;
    for(size_t i = index; i < input.size(); ++i)
    {
        //increase dash count if on a dash "letter"
        if(input[i] == '-')
        {
            dashes_left++;
        }
    }

    if(floating.size() > dashes_left)
    {
        return;
    }

    //guess dash letters by putting in floating letters 
    for(size_t i = 0; i < floating.size(); ++i) 
    {
        if(i > 0 && floating[i] == floating[i-1])
        {
            continue;
        }

        current[index] = floating[i]; //set letter to the first floating
        string next = floating.substr(0, i) + floating.substr(i+1); //save the floating letters
        findWord(input, current, index + 1, next, dict, results); //feed in next as the floating argument
    }

    // Try placing non-floating letters
    if(floating.size() < dashes_left)
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

    current[index] = '-'; //reset the current letter
}