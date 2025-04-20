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


// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    set<string> result;

    //base case 1 - if none found, all blank
    if(in.find('-') == string::npos)
    {
        //create a copy to alter in this base case, not the rest of the cases 
        string temp = in;
        bool valid = true; //keeps track of floating letters

        //check if there are floating letters
        //loop through all floating letters
        for(char c : floating)
        {
            bool found = false; //keeps track of if letter is found correctly
            //loop through letters in word
            for(size_t i = 0; i < temp.length(); i++)
            {
                //if the letter is floating
                if(temp[i] == c)
                {
                    //
                    temp[i] = '-';
                    found = true;
                    break;
                }
            }

            //if the letter is not found, return empty set
            if(!found)
            {
                valid = false;
                break;
            }
        }

        //if the word is valid (contains all floating letters) and is in the dictionary, add it
        if(valid && dict.find(in) != dict.end())
        {
            result.insert(in); 
        }

        return result;
    }


    //case 2 - if there is a fixed letter

    //first open position
    size_t openSpot = in.find('-');

    if(in[openSpot] != '-')
    {
        //build substring
        string word = in; //copy to change
        word[openSpot] = in[openSpot]; //replace open spot w letter
        set<string> substring = wordle(word, floating, dict);
        result.insert(substring.begin(), substring.end()); 
        return result;
    }

    //"guess" all letters for each spot
    for(char c = 'a'; c <= 'z'; c++)
    {
        string word = in; //copy to change
        word[openSpot] = c; //replace open spot w letter
        set<string> substring = wordle(word, floating, dict); 
        result.insert(substring.begin(), substring.end());

    }

    return result;


}

// Define any helper functions here
