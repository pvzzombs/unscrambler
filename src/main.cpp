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
    unordered_map<string, string> config;
    ifstream file("D:/Documents/Codes/VS Code/C++/Unscrambler/config.txt");
    if(file.is_open()) {
        string line;
        while (getline(file, line)) {
            // Find the position of the separator
            size_t pos = line.find_first_of("=:");
            if (pos != string::npos) {
                // Extract the key and value from the line
                string key = line.substr(0, pos);
                string value;
                size_t value_start_pos = line.find_first_not_of(" \t", pos+1); // Start of the value
                if (value_start_pos != string::npos) { // Value exists
                    if (line[value_start_pos] == '\"') { // Enclosed in quotes
                        size_t value_end_pos = line.find_first_of("\"", value_start_pos+1); // End of the value
                        if (value_end_pos != string::npos) {
                            value = line.substr(value_start_pos+1, value_end_pos-value_start_pos-1); // Extract the value between the quotes
                        }
                    } else { // Not enclosed in quotes
                        size_t value_end_pos = line.find_first_of(" \t", value_start_pos); // End of the value
                        if (value_end_pos != string::npos) {
                            value = line.substr(value_start_pos, value_end_pos-value_start_pos); // Extract the value
                        } else {
                            value = line.substr(value_start_pos); // Extract the value until the end of the line
                        }
                    }
                }
                // Remove leading and trailing whitespace from the key and value
                key.erase(0, key.find_first_not_of(" \t"));
                key.erase(key.find_last_not_of(" \t") + 1);
                value.erase(0, value.find_first_not_of(" \t"));
                value.erase(value.find_last_not_of(" \t") + 1);
                // Add the key-value pair to the config map
                config[key] = value;
            }
        }
    } else {
        cout << "[Error] Could not open file" << endl;
    }
    return config;
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