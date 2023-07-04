#include <unordered_map>
#include <fstream>
#include "cli.hpp"
#include "unscramble.hpp"

using namespace std;

bool isAnagram(const std::string& word1, const std::string& word2, const CLI& cli)
{
    bool substring = cli.isFlagActive({"-s", "--substring"});
    if(substring) {
        if(word1.size() < word2.size()) {
            return false;
        }
    } else {
        if(word1.size() != word2.size()) {
            return false;
        }
    }
    // get frequencies of characters in word1 and word2
    std::unordered_map<char, int> freq1;
    std::unordered_map<char, int> freq2;
    for (const auto& c : word1) {
        freq1[c]++;
    }
    for (const auto& c : word2) {
        freq2[c]++;
    }
    if(substring) {
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

std::vector<std::string> unscramble(const std::string& target, const std::string& path, const CLI& cli)
{
    std::ifstream dict(path);
    std::vector<std::string> output;
    std::string word;
    if(dict.is_open()) {
        while(dict >> word) {
            if(isAnagram(target, word, cli)) {
                output.push_back(word);
            }
        }
    } else {
        throw std::runtime_error("[Error] Could not open dictionary");
    }
    return output;
}