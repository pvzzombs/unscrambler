#include <iostream>
#include <vector>
#include <unordered_map>
#include "dictionary.hpp"

using namespace std;

bool isValidLanguage(string language) 
{
    for(int i = 0; i < language.size(); i++) {
        language[i] = tolower(language[i]);
    }
    if(language == "english") {
        return true;
    } else if(language == "filipino") {
        return true;
    } else {
        return false;
    }
}

string getLanguage(vector<string>& args, const unordered_map<string, string>& config)
{
    string language;
    if(args.size() > 1) {
        for(int i = 0; i < args.size(); i++) {
            if((args[i] == "-L" || args[i] == "--Language") && isalpha(args[i+1][0])) {
                language = args[i+1];
                args.erase(args.begin()+i, args.begin()+(i+2));
                break;
            } else if((args[i] == "-L" || args[i] == "--Language") && !isalpha(args[i+1][0])) {
                args.erase(args.begin()+i);
                break;
            }
        }
    }
    if(language.empty()) {
        language = config.at("DefaultLanguage");
    }
    if(!isValidLanguage(language)) {
        cout << "[Error] Language '" << language << "' is not supported" << endl;
        cout << "Try the '-h' option to see supported languages" << endl;
        return string();
    }
    return language;
}

string setDictionaryFile(string language, const unordered_map<string, string>& config)
{
    string dictionary = config.at("DictionaryPath");
    if(dictionary.back() != '/') {
        for(int i = dictionary.size()-1; i >= 0; i--) {
            if(dictionary[i] == '.') { // must be a file
                break;
            } else if(dictionary[i] == '/') {
                dictionary += "/";
                break;
            }
        }
    }
    for(int i = 0; i < language.size(); i++) {
        language[i] = tolower(language[i]);
    }
    if(language == "english") {
        dictionary += "english.txt";
    } else if(language == "filipino") {
        dictionary += "filipino.txt";
    }
    return dictionary;
}

