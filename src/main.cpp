#include <iostream>
#include <vector>
#include <fstream>
#include <unordered_map>
#include "unscramble.hpp"

using namespace std;

template<typename T>
void print(const vector<T>& v)
{
    for(int i = 0; i < v.size(); i++) {
        cout << v[i] << endl;
    }
}

template<typename K, typename V>
void print(const unordered_map<K, V>& m)
{
    for(const auto& i : m) {
        cout << i.first << " | " << i.second << endl;
    }
}

void printConfig(const unordered_map<string, string>& config)
{
    for(const auto& i : config) {
        cout << i.first << ": " << i.second << endl;
    }
}

void initializeDictionary(vector<string>& dict)
{
    ifstream dictionary("../../dictionary.txt");
    string temp;
    if(dictionary.is_open()) {
        while(dictionary >> temp) {
            dict.push_back(temp);
        }
    }
    dictionary.close();
}

void errorMessage(const string& error, const string& program)
{
    cout << "[Error] " << error << endl;
    cout << "Try: " << program << " -h" << endl;
}

void showHelp(const string& program, const unordered_map<string, string>& config)
{
    cout << "FORMAT: " << endl;
    cout << program << " <OPTIONS> <WORD>" << endl;
    cout << program << " -L <LANGUAGE> <OPTION> <WORD>" << endl;
    cout << "EXAMPLE:" << endl;
    cout << program << " -u srtekri" << endl;
    cout << program << " -L Filipino -u putnagnai" << endl;
    cout << "OPTIONS: " << endl;
    cout << "-h, --help              Show help text" << endl;
    cout << "-u, --unscramble        Unscramble word" << endl;
    cout << "-L, --Language          Select language" << endl;
    cout << "SUPPORTED LANGUAGES:" << endl;
    cout << "English" << endl;
    cout << "Filipino" << endl;
    cout << "CONFIG:" << endl;
    printConfig(config);
}

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

bool isForWord(const string& arg)
{
    if(arg == "-u" || arg == "--unscramble") {
        return true;
    } else if(arg == "-c" || arg == "--complete") {
        return true;
    } else {
        return false;
    }
}

unordered_map<string, string> readConfig()
{
    ifstream config("D:/Documents/Codes/VS Code/C++/Unscrambler/config.txt");
    unordered_map<string, string> m;
    string temp;
    if(config.is_open()) {
        while(getline(config, temp)) {
            if(temp[0] == '#' || temp[0] == ' ') {
                continue;
            }
            string key, value;
            int i = 0;
            while(i < temp.size() && (temp[i] != '=' && temp[i] != ':')) {
                key.push_back(temp[i]);
                i++;
            }
            while(key.back() == ' ') { // remove trailing whitespace
                key.pop_back();
            }
            i++; // move forward
            while(i < temp.size() && temp[i] == ' ') { // ignore whitespaces
                i++;
            }
            if(temp[i] == '"') {
                i++; // move forward
                while(i < temp.size() && temp[i] != '"') {
                    value.push_back(temp[i]);
                    i++;
                }
            } else {
                while(i < temp.size() && temp[i] != ' ') {
                    value.push_back(temp[i]);
                    i++;
                }
            }
            m.insert({key, value});
        }
    } else {
        cout << "[Error] Could not open configuration file" << endl;
    }
    config.close();
    return m;
}

string getProgramName(char c[])
{
    string name;
    name.assign(c);
    for(int i = name.size()-1; i >= 0; i--) {
        if(name[i] == '/' || name[i] == '\\') {
            name.assign(name.begin()+(i+1), name.end());
            break;
        }
    }
    return name;
}

void setOptions(const vector<string>& args, unordered_map<string, bool>& options)
{
    for(int i = 0; i < args.size(); i++) {
        if(options.find(args[i]) != options.end()) {
            options[args[i]] = true;
        }
    }
}

string getWord(const vector<string>& args)
{
    for(int i = 0; i < args.size(); i++) {
        if(isForWord(args[i]) && isalpha(args[i+1][0])) {
            string temp = args[i+1];
            for(int j = 0; j < temp.size(); j++) { // lowercase all characters
                temp[j] = tolower(temp[j]);
            }
            return temp;
        }
    }
    return string();
}

string getLanguage(const vector<string>& args, const unordered_map<string, string>& config)
{
    string language;
    for(int i = 0; i < args.size(); i++) {
        if((args[i] == "-L" || args[i] == "--Language") && isalpha(args[i+1][0])) {
            language = args[i+1];
            break;
        }
    }
    if(language.empty()) {
        return config.at("DefaultLanguage");
    }
    if(!isValidLanguage(language)) {
        cout << "[Error] Language '" << language << "' is not supported" << endl;
        cout << "Try the '-h' option to see supported languages" << endl;
        return string();
    }
    return language;
}

void setLanguageToDictionary(string language, string& dictionary)
{
    if(dictionary.back() != '/') {
        for(int i = dictionary.size()-1; i >= 0; i--) {
            if(dictionary[i] == '.') { // must be a file
                return;
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
}

int main(int argc, char* argv[])
{
    vector<string> args;
    unordered_map<string, string> config = readConfig();
    unordered_map<string, bool> options = {{"-h", 0}, {"--help", 0}, {"-u", 0}, {"--unscramble", 0}, {"-L", 0}, {"--Language", 0}};
    string program_name = getProgramName(argv[0]);
    args.assign(argv+1, argv+argc);
    setOptions(args, options);
    if(args.empty() || options.at("-h") || options.at("--help")) {
        showHelp(program_name, config);
        return 0;
    }

    string target = getWord(args);
    if(target.empty()) {
        errorMessage("No word specified", program_name);
        return 0;
    }

    string dictionary_path = config.at("DictionaryPath");
    string language = getLanguage(args, config);
    setLanguageToDictionary(language, dictionary_path);

    vector<string> output;
    if(options.at("-u") || options.at("--unscramble")) {
        output = unscramble(target, dictionary_path);
    }
    cout << "Language: " << language << endl;
    cout << "Word: " << target << endl;
    cout << "=====MATCHES====" << endl;
    print(output);
    return 0;
}