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
    string current,
    const string& floating,
    const set<string>& dict,
    set<string>& results,
    size_t index
);

set<string> wordle(
    const string& in,
    const string& floating,
    const set<string>& dict)
{
    set<string> results;
    string current = in;
    recurseWordle(current, floating, dict, results, 0);
    return results;
}

void recurseWordle(
    string current,
    const string& floating,
    const set<string>& dict,
    set<string>& results,
    size_t index)
{
    if (index >= current.size()) {
        if (dict.find(current) != dict.end() && floating.empty()) {
            results.insert(current);
        }
        return;
    }

    if (current[index] != '-') {
        recurseWordle(current, floating, dict, results, index + 1);
        return;
    }

    // Count remaining dashes
    int dashesLeft = 0;
    for (size_t i = index; i < current.size(); ++i) {
        if (current[i] == '-') dashesLeft++;
    }

    for (char c = 'a'; c <= 'z'; ++c) {
        // Check if using a non-floating letter is allowed
        bool isFloating = floating.find(c) != string::npos;
        if (!isFloating && floating.size() > dashesLeft - 1) {
            continue; // Not enough dashes left to place all floating letters
        }

        string updatedFloating = floating;
        if (isFloating) {
            size_t pos = updatedFloating.find(c);
            updatedFloating.erase(pos, 1); // consume floating
        }

        current[index] = c;
        recurseWordle(current, updatedFloating, dict, results, index + 1);
    }

    current[index] = '-'; // Optional reset (safe due to string copy)
}
