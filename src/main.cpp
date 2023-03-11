#include <iostream>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <string>
#include "dictionary.hpp"
#include "substring.hpp"
#include "unscramble.hpp"
#include "complete.hpp"

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
    cout << "-c, --complete          Complete word" << endl;
    cout << "-s, --substring         Give the ordered substrings of the word" << endl;
    cout << "LANGUAGE: " << endl;
    cout << "-L, --Language          Specify language" << endl;
    cout << "SUPPORTED LANGUAGES:" << endl;
    cout << "English" << endl;
    cout << "Filipino" << endl;
    cout << "CONFIG:" << endl;
    printConfig(config);
}

unordered_map<string, string> readConfig()
{
    ifstream config("../../dictionary/config.txt");
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

void setOptions(vector<string>& args, unordered_map<string, bool>& options)
{
    for(int i = 0; i < args.size(); i++) {
        if(args[i][0] == '-' && options.find(args[i]) != options.end() && !options.at(args[i])) { // if args is found in options
            options[args[i]] = true;
        } else if(args[i][0] == '-' && (options.find(args[i]) == options.end() || options.at(args[i]))) {
            args.erase(args.begin()+i);
            i--;
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
    vector<string> args;
    unordered_map<string, string> config = readConfig();
    unordered_map<string, bool> options = {{"-h", 0}, {"--help", 0}, {"-u", 0}, {"--unscramble", 0}, {"-c", 0}, {"--complete", 0},
    {"-s", 0}, {"--substring", 0}, {"-L", 0}, {"--Language", 0}};
    string program_name = getProgramName(argv[0]);
    args.assign(argv+1, argv+argc);
    setOptions(args, options);
    // print(args);
    // cout << "===Options===" << endl;
    // print(options);
    if(args.empty() || options.at("-h") || options.at("--help")) {
        showHelp(program_name, config);
        return 0;
    }

    string dictionary_path;
    string target;
    string language = getLanguage(args, config);
    if(language.empty()) {
        return 0;
    }

    target = getWord(args);
    if(target.empty()) {
        cout << "[Error] No word specified" << endl;
        cout << "Try the '-h' option to see format" << endl;
        return 0;
    }

    dictionary_path = setDictionaryFile(language, config);

    vector<string> output;
    if(options.at("-u") || options.at("--unscramble")) {
        output = unscramble(target, dictionary_path, options);
    } else if(options.at("-c") || options.at("--complete")) {
        output = complete(target, dictionary_path);
    } else if(options.at("-s") || options.at("--substring")) {
        output = substring(target, dictionary_path);
    } else {
        cout << "[Error] No option specified for word" << endl;
        cout << "Try the '-h' option to see available options" << endl;
        return 0;
    }
    cout << "Language: " << language << endl;
    cout << "Word: " << target << endl;
    cout << "=====MATCHES====" << endl;
    print(output);
    return 0;
}
