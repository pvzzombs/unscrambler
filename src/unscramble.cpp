#include <iostream>
#include <vector>
#include <unordered_map>
#include <cctype>
#include <fstream>
#include "unscramble.hpp"

using namespace std;

bool isAnagram(const string& word1, const string& word2, const unordered_map<string, bool>& options = {})
{
    if(options.at("-s") || options.at("--substring")) { // substring option is on
        if(word1.size() < word2.size()) {
            return false;
        }
    } else {
        if(word1.size() != word2.size()) {
            return false;
        }
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
    if(options.at("-s") || options.at("--substring")) {
        for(const auto& i : freq2) {
            if(freq1.count(i.first) < 1) {
                return false;
            }
        }
        for(const auto& i : freq2) {
            if(freq1.at(i.first) < i.second) {
                return false;
            }
        }
        return true;
    } else {
        return freq1 == freq2;
    }
}

vector<string> unscramble(const string& target, const string& path, const unordered_map<string, bool>& options = {})
{
    ifstream dict(path);
    vector<string> output;
    string word;
    if(dict.is_open()) {
        while(dict >> word) {
            if(isAnagram(target, word, options)) {
                output.push_back(word);
            }
        }
    } else {
        cout << "[Error] Could not open dictionary \"" << path << "\"" << endl;
    }
    return output;
}