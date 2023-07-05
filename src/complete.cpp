#include <iostream>
#include <vector>
#include <fstream>
#include "complete.hpp"

bool isCompleteWord(const std::string& incomplete, const std::string& complete)
{
    if(complete.size() <= incomplete.size()) {
        return false;
    }
    for(int i = 0; i < incomplete.size(); i++) {
        if(incomplete[i] == complete[i]) {
            continue;
        }
        return false;
    }
    return true;
}

std::vector<std::string> complete(const std::string& input, const std::string& path)
{
    std::ifstream dict(path);
    std::vector<std::string> output;
    std::string word;
    if(dict.is_open()) {
        while(dict >> word) {
            if(isCompleteWord(input, word)) {
                output.push_back(word);
            }
        }
    } else {
        std::cout << "[Error] Could not open dictionary \"" << path << "\"" << std::endl;
    }
    return output;
}
