#pragma once

bool pathExists(const std::string& path);
bool invalidFilenameChar(char ch);
bool isDirectorySeparator(char ch);
std::string getCallPath();
std::string getExecutableFilePath();
std::string joinPath(const std::string& path, const std::string& child_path);