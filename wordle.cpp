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
    //Check for any correct placed characters - if found, create a set and look for words with the correct character in that specific position
        //Afterwards, look at the given floating characters, look through set to find words that has the following characters in the word and put into a set   
    //Return set of words.

}

// Define any helper functions here
