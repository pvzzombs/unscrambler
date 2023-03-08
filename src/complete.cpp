#include <iostream>
#include <vector>
#include <fstream>
#include "complete.hpp"

using namespace std;

bool isCompleteWord(const string& incomplete, const string& complete)
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

vector<string> complete(const string& input, const string& path)
{
    ifstream dict(path);
    vector<string> output;
    string word;
    if(dict.is_open()) {
        while(dict >> word) {
            if(isCompleteWord(input, word)) {
                output.push_back(word);
            }
        }
    } else {
        cout << "[Error] Could not open dictionary \"" << path << "\"" << endl;
    }
    return output;
}
