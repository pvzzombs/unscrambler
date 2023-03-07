#include <iostream>
#include <vector>
#include <unordered_map>
#include <cctype>
#include <fstream>
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

vector<string> unscramble(const string& target)
{
    ifstream dict("../../dictionary/english.txt");
    vector<string> output;
    string word;
    while(dict.is_open() && dict >> word) {
        if(isAnagram(target, word)) {
            output.push_back(word);
        }
    }
    dict.close();
    return output;
}