#include <iostream>
#include <vector>
#include <unordered_map>
#include <cctype>
#include "unscramble.hpp"

using namespace std;

bool isAnagram(const string& word1, const string& word2)
{
    if(word1.size() != word2.size()) {
        return false;
    }
    // get frequencies of characters in word1 and word2
    unordered_map<char, int> freq1;
    unordered_map<char, int> freq2;
    for (const auto& c : word1) {
        freq1[c]++;
    }
    for (const auto& c : word2) {
        freq2[c]++;
    }
    return freq1 == freq2; // if key and values are equal, return true
}

vector<string> unscramble(const vector<string>& dictionary, const string& target)
{
    vector<string> output;
    for(int i = 0; i < dictionary.size(); i++) {
        if(isAnagram(target, dictionary[i])) {
            output.push_back(dictionary[i]);
        }
    }
    return output;
}