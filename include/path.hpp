#pragma once

bool pathExists(const std::string& path);
bool invalidFilenameChar(char ch);
bool isFile(const std::string& path);
bool isFolder(const std::string& path);
bool isDirectorySeparator(char ch);
char directorySeparator();
std::string getCallPath();
std::string getExecutableFilePath();
std::string joinPath(const std::string& path, const std::string& child_path);