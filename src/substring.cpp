#include <iostream>
#include <vector>
#include <fstream>

bool isSubstring(const std::string& word1, const std::string& word2) 
{
    if(word1.size() < word2.size()) {
        return false;
    }
    int i = 0;
    int j = 0;
    while(i < word1.size()) {
        if(word1[i] == word2[0]) { // traverse word1 until it matches the first character of word2
            while(i < word1.size() && j < word2.size()) { // traverse word1 and word2 at the same time
                if(word1[i] == word2[j]) { // continue if it consecutively matches characters
                    i++;
                    j++;
                } else { // if mismatch, traverse word1 with the current 'i' again until it finds the first character of word2
                    j = 0; // traverse word2 from the start again next time
                    break;
                }
            }
            if(j >= word2.size()) { // if 'j' finishes traversing word2, it means its a substring
                return true;
            }
        } else {
            i++;
        }
    }
    return false;
}

std::vector<std::string> substring(const std::string& target, const std::string& path)
{
    std::ifstream dict(path);
    std::vector<std::string> output;
    std::string word;
    if(dict.is_open()) {
        while(dict >> word) {
            if(isSubstring(target, word)) {
                output.push_back(word);
            }
        }
    } else {
        std::cout << "[Error] Could not open dictionary \"" << path << "\"" << std::endl;
    }
    return output;
}