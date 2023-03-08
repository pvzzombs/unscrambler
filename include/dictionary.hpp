#pragma once

bool isValidLanguage(std::string);
std::string getLanguage(std::vector<std::string>&, const std::unordered_map<std::string, std::string>&);
std::string setDictionaryFile(std::string, const std::unordered_map<std::string, std::string>&);
