#include <iostream>
#include <vector>
#include <unordered_map>
#include <fstream>
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

void errorMessage(const string& error, const string& program)
{
    cout << "[Error] " << error << endl;
    cout << "Try: " << program << " -h" << endl;
}

void showHelp(const string& program)
{
    cout << "FORMAT: " << endl;
    cout << program << " <OPTIONS> <WORD>" << endl;
    cout << "OPTIONS: " << endl;
    cout << "-h, --help              Show help text" << endl;
    cout << "-u, --unscramble        Unscramble word" << endl;
}

unordered_map<string, string> getConfigValues()
{
    ifstream config("../../config.txt");
    unordered_map<string, string> m;
    string temp;
    if(config.is_open()) {
        while(getline(config, temp)) {
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
                i++;
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
        if(isalpha(args[i][0])) {
            string temp = args[i];
            for(int j = 0; j < temp.size(); j++) { // lowercase all characters
                temp[j] = tolower(temp[j]);
            }
            return temp;
        }
    }
    return string();
}

int main(int argc, char* argv[])
{
    // vector<string> args;
    // unordered_map<string, bool> options = {{"-h", 0}, {"--help", 0}, {"-u", 0}, {"--unscramble", 0}};
    // string program_name = getProgramName(argv[0]);
    // args.assign(argv+1, argv+argc);
    // setOptions(args, options);
    // if(args.empty() || options.at("-h") || options.at("--help")) {
    //     showHelp(program_name);
    //     return 0;
    // }

    // string target = getWord(args);
    // cout << "Word: " << target << endl;
    // if(target.empty()) {
    //     errorMessage("No word specified", program_name);
    //     return 0;
    // }

    // vector<string> output;
    // if(options.at("-u") || options.at("--unscramble")) {
    //     output = unscramble(target);
    // }
    // print(output);
    unordered_map<string, string> configuration = getConfigValues();
    print(configuration);
    return 0;
}