#include "cli.hpp"
#include "path.hpp"
#include "substring.hpp"
#include "unscramble.hpp"
#include "complete.hpp"

void printConfig(const std::unordered_map<std::string, std::string>& config)
{
    for(const auto& i : config) {
        std::cout << i.first << ": " << i.second << std::endl;
    }
}

void showHelp(const std::string& program, const std::unordered_map<std::string, std::string>& config)
{
    std::cout << "USAGE: " << std::endl;
    std::cout << program << " <options> <word> [-L <language>]" << std::endl;
    std::cout << "OPTIONS: " << std::endl;
    std::cout << "-h, --help              Show help text" << std::endl;
    std::cout << "-u, --unscramble        Unscramble word" << std::endl;
    std::cout << "-c, --complete          Complete word" << std::endl;
    std::cout << "-s, --substring         Give the ordered substrings of the word" << std::endl;
    std::cout << "-L, --Language          Provide a language" << std::endl;
    std::cout << "SUPPORTED LANGUAGES:" << std::endl;
    std::cout << "English" << std::endl;
    std::cout << "Filipino" << std::endl;
    std::cout << "ADD CONFIGURATION FILE:" << std::endl;
    std::cout << "--config=\"path/to/config.txt\"" << std::endl;
    std::cout << "CONFIG OPTIONS:" << std::endl;
    printConfig(config);
}

std::string getConfigPath(const CLI& cli)
{
    std::string config_path = path::join(path::sourcePath(), "config.txt");
    if(path::exists(config_path)) {
        return config_path;
    }

    if(cli.isFlagActive("--config-path")) {
        std::string temp_path = cli.getValueOf("--config-path");
        if(path::exists(temp_path)) {
            path::copy(temp_path, path::sourcePath(), path::CopyOption::OverwriteExisting);
            return config_path;
        }
    }
    throw std::runtime_error("[Error] Could not find config file");
}

std::unordered_map<std::string, std::string> readConfig(std::string config_path)
{
    std::ifstream config(config_path);
    std::unordered_map<std::string, std::string> m;
    std::string temp;
    if(config.is_open()) {
        while(getline(config, temp)) {
            if(temp[0] == '#' || temp[0] == ' ') {
                continue;
            }
            std::string key, value;
            int i = 0;
            while(i < temp.size() && (temp[i] != '=' && temp[i] != ':')) { // move forward until we reach a separator
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
            while(value.back() == ' ') {
                value.pop_back();
            }
            m.insert({key, value});
        }
    } else {
        std::cout << "[Error] Could not open configuration file \"" << config_path << "\"" << std::endl;
    }
    config.close();
    return m;
}

int main(int argc, char* argv[])
{
    CLI cli(argc, argv);
    std::string program_name = cli.getProgramName();
    std::unordered_map<std::string, std::string> config = readConfig(getConfigPath(cli));
    try {
        cli.setValidFlags({"-h", "--help", "-u", "--unscramble", "-c", 
        "--complete", "-s", "--substring", "-L", "--Language", "--config-path", 
        "--set-dictionary-path", "--set-default-language"});

        if(cli.isFlagActive("-h") || cli.isFlagActive("--help")) {
            showHelp(program_name, config);
            return 0;
        }

        std::string language;
        if(cli.isFlagActive({"-L", "--Language"})) {
            language = cli.getValueOf({"-L", "--Language"});
        }

        std::string word;
        if(cli.isFlagActive({"-u", "--unscramble"})) {
            word = cli.getValueOf({"-u", "--unscramble"});
            
        }

    } catch(const CLIException& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
    return 0;
}