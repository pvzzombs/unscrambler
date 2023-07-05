#include "cli.hpp"
#include "path.hpp"
#include "unscramble.hpp"
#include "substring.hpp"
#include "complete.hpp"

void printConfig(const std::unordered_map<std::string, std::string>& config)
{
    for(const auto& i : config) {
        std::cout << i.first << ": " << i.second << std::endl;
    }
}

template<typename T>
void print(const std::vector<T>& v)
{
    for(int i = 0; i < v.size(); i++) {
        std::cout << v[i] << std::endl;
    }
}

std::string toLower(std::string str)
{
    for(int i = 0; i < str.size(); i++) {
        str[i] = tolower(str[i]);
    }
    return str;
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
    std::cout << "-L, --Language          Set language" << std::endl;
    std::cout << "--set-dictionary-path   Set the path where unscrambler will look for dictionaries" << std::endl;
    std::cout << "--set-default-language  Set the default language" << std::endl;
    std::cout << "SUPPORTED LANGUAGES:" << std::endl;
    std::cout << "English" << std::endl;
    std::cout << "Filipino" << std::endl;
    std::cout << "CONFIG OPTIONS:" << std::endl;
    printConfig(config);
}

void changeConfigValue(const std::string& config_path, const std::string& find, const std::string& new_val)
{
    std::string new_config = path::join(path::sourcePath(), "config_temp.txt");
    std::ifstream input(config_path);
    std::ofstream output(new_config);

    std::string temp;
    if(input.is_open() && output.is_open()) {
        while(getline(input, temp)) {
            if(!temp.empty() && temp[0] == '#') {
                output << temp << std::endl;
                continue;
            }

            size_t f = temp.find(find);
            if(f != std::string::npos) {
                output << find << " = \"" << new_val << "\"" << std::endl;
            } else {
                output << temp << std::endl;
            }
        }

        input.close();
        output.close();

        path::remove(config_path);
        path::rename(new_config, "config.txt");
    } else {
        throw std::runtime_error("[Error] Could not open file");
    }
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
    try {
        cli.setValidFlags({"-h", "--help", "-u", "--unscramble", "-c", 
        "--complete", "-s", "--substring", "-L", "--Language", "--config-path", 
        "--set-dictionary-path", "--set-default-language"});

        std::string config_path = getConfigPath(cli);
        std::unordered_map<std::string, std::string> config = readConfig(config_path);

        if(cli.isFlagActive({"-h", "--help"})) {
            showHelp(program_name, config);
            return 0;
        }

        if(cli.isFlagActive("--set-dictionary-path")) {
            std::string new_path = cli.getValueOf("--set-dictionary-path");
            if(!new_path.empty()) {
                changeConfigValue(config_path, "DictionaryPath", new_path);
                std::cout << "[Success] Dictionary path is been changed successfully" << std::endl;
                return 0;
            }
        }

        if(cli.isFlagActive("--set-default-language")) {
            std::string new_language = cli.getValueOf("--set-default-language");
            if(!new_language.empty()) {
                changeConfigValue(config_path, "DefaultLanguage", new_language);
                std::cout << "[Success] Default language has been changed successfully" << std::endl;
                return 0;
            }
        }

        std::string language;
        if(cli.isFlagActive({"-L", "--Language"})) {
            language = cli.getValueOf({"-L", "--Language"});
        }

        if(language.empty()) {
            language = config.at("DefaultLanguage");
        }

        std::vector<std::string> result;
        std::string word;
        std::string dictionary_path = path::join({path::sourcePath(), config.at("DictionaryPath"), toLower(language) + ".txt"});

        if(cli.isFlagActive({"-u", "--unscramble"})) {
            word = cli.getValueOf({"-u", "--unscramble"});
            result = unscramble(word, dictionary_path, cli);
        } else if(cli.isFlagActive({"-s", "--substring"})) {
            word = cli.getValueOf({"-s", "--substring"});
            result = substring(word, dictionary_path);
        } else if(cli.isFlagActive({"-c", "--complete"})) {
            word = cli.getValueOf({"-c", "--complete"});
            result = complete(word, dictionary_path);
        }

        std::cout << "Language: " << language << std::endl;
        std::cout << "Word: " << word << std::endl;
        std::cout << "=====MATCHES====" << std::endl;
        if(result.empty()){
            std::cout << "<No words match>" << std::endl;
        } else {
            print(result);
        }

    } catch(const CLIException& e) {
        std::cout << e.what() << std::endl;
        return 1;
    } catch(const std::runtime_error& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }

    return 0;
}