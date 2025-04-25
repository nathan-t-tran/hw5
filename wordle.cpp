#ifndef RECCHECK
#include <iostream>
#include <algorithm>
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;

// Helper prototype
void recurseWordle(
    std::string current,
    const std::string& floating,
    const std::set<std::string>& dict,
    std::set<std::string>& results,
    size_t index
);

std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    std::set<std::string> results;
    std::string current = in;
    recurseWordle(current, floating, dict, results, 0);
    return results;
}

// Helper function
void recurseWordle(
    std::string current,
    const std::string& floating,
    const std::set<std::string>& dict,
    std::set<std::string>& results,
    size_t index)
{
    if (index == current.size()) {
        if (dict.find(current) != dict.end()) {
            // Check if all floating letters were used
            std::map<char, int> countFloating;
            for (char c : floating) countFloating[c]++;
            for (char c : current) {
                if (countFloating.find(c) != countFloating.end()) {
                    countFloating[c]--;
                    if (countFloating[c] == 0) {
                        countFloating.erase(c);
                    }
                }
            }
            if (countFloating.empty()) {
                results.insert(current);
            }
        }
        return;
    }

    if (current[index] != '-') {
        // Already filled, move to next index
        recurseWordle(current, floating, dict, results, index + 1);
        return;
    }

    // Try all letters a-z in this position
    for (char c = 'a'; c <= 'z'; ++c) {
        current[index] = c;
        std::string updatedFloating = floating;
        size_t pos = updatedFloating.find(c);
        if (pos != std::string::npos) {
            updatedFloating.erase(pos, 1); // consume floating letter
        }
        recurseWordle(current, updatedFloating, dict, results, index + 1);
    }

    current[index] = '-'; // backtrack (not necessary with string copy, but for clarity)
}