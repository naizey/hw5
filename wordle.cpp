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
void findWord(std::string input, std::multiset<char> floating, const std::set<std::string>& dict, std::set<std::string>& results, size_t dash_count); 

set<string> wordle(const string& in, const string& floating, const set<string>& dict)
{
    std::set<std::string> results; //init return set
    std::string input = in; //send in a copy of string, since og is const
    //convert floating string to multiset 
    std::multiset<char> float_set(floating.begin(), floating.end());
    //std::string floats = floating; //send in a copy of floating letters

    size_t dash_count = 0;
    //finding all dashes in the input string
    for(int num = 0; num < input.length(); num++)
    {
        if(input[num] == '-') dash_count++;
    }
    findWord(input, float_set, dict, results, dash_count); //pass in index, 
    return results; 
}

void findWord(std::string input, std::multiset<char> floating, const std::set<std::string>& dict, std::set<std::string>& results, size_t dash_count)
{
    //check for if the floating is greater than numdashes
    if(floating.size() > dash_count)
    {
        return;
    }
    //base case - word has all letters found (floating letters are used)
    if(input.find('-') == string::npos) //if there is no dash in string
    {
        //if all the floating letters are used and if current is a valid word
        if(floating.size() == 0 && dict.find(input) != dict.end()) 
        {
            //add to results
            results.insert(input);
        }
        return;
    }

    // //if the letter is fixed, IE doesn't have a dash
    // if(input[index] != '-') 
    // {
    //     //go to next letter
    //     findWord(index + 1, input, floating, dict, results, dash_count); //decrease problem size
    //     //return; //added a return to kick out
    // }

    // else 
    // {
        //size_t num = 0; //count the number of dashes 
        //count the number of dashes to reduce the amount of letters guessed, no wasted checks)

//try all letters
//check if letter is in multiset
//if it is, erase it from the multiset
//do recursive call 
//if you erased smthn from floating set
//put it back in the multiset
        //guess dash letters by putting in floating letters 
        bool deleted = false;
        dash_count--;
        int index = input.find('-'); //find the first dash
        for(char c = 'a'; c <= 'z'; c++)
        {
            deleted = false;
            input[index] = c; //guess the letter
            if(floating.find(c) != floating.end()) //letter is in the floating set
            {
                //erase from floating set
                floating.erase(floating.find(c)); 
                deleted = true;
            }
            findWord(input, floating, dict, results, dash_count); //feed in next as the floating argument

            if(deleted) //put the letter back if it was deleted
            {
                floating.insert(c);
            }
        }
        return; 

        // }

    
}







 // for (std::multiset<char>::iterator it = floating.begin(); it != floating.end(); ++it) 
        // {
        //     char c = *it; //current floating letter we want to guess with 
        //     input[index] = c; //try placing the floating letter in the current dash

        //     //input[index] = floating[i]; //try first floating letter
        //     // //get the rest of the letters
        //     //std::string new_floats = floating.substr(0, i) + floating.substr(i + 1); //save the floating letters
        //     std::multiset<char> new_floats = floating; // Create a copy of the multiset
        //     new_floats.erase(new_floats.find(c)); // Remove one occurrence of the character
        //     findWord(index + 1, input, new_floats, dict, results); //feed in next as the floating argument
        // }

        // //condition is necessary to make efficient
        // if(numDashes(input) >= floating.size()) //if there are more dashes than letters left to guess from...
        // {
        //     for(char c = 'a'; c <= 'z'; c++) //now guess through alphabet, since its not a floating letter
        //     {
        //         input[index] = c; //guess the letter
        //         findWord(index + 1, input, floating, dict, results); //recurse again
        //     }





