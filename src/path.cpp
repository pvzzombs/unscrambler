#include <string>
#include <filesystem>
#include <unistd.h>
#include <windows.h>
#include "path.hpp"

using namespace std;

bool pathExists(const string& path)
{
    return filesystem::exists(filesystem::path(path));
}

bool invalidFilenameChar(char ch)
{
    switch(ch) {
        case '#':
        case '%':
        case '&':
        case '{':
        case '}':
        case '\\':
        case '/':
        case '<':
        case '>':
        case '*':
        case '?':
        case '~':
        case '!':
        case '\'':
        case '\"':
        case ':':
        case '@':
        case '`':
        case '|':
        case '=':
            return true;
        default:
            return false;
    }
}

bool isDirectorySeparator(char ch)
{
    #ifdef _WIN32
        if(ch == '/' || ch == '\\') {
            return true;
        } else {
            return false;
        }
    #elif __linux__
        if(ch == '/') {
            return true;
        } else {
            return false;
        }
    #elif __APPLE__
        if(ch == ':') {
            return true;
        } else {
            return false;
        }
    #else
        std::cerr << "[Error] Unknown Operating System" << std::endl;
        return false;
    #endif
}

string getCallPath()
{
    char currentPath[FILENAME_MAX];
    getcwd(currentPath, FILENAME_MAX);
    return string(currentPath);
}

string getExecutableFilePath()
{
    char path[MAX_PATH];
    GetModuleFileName(NULL, path, MAX_PATH);
    string p(path);
    filesystem::path pth(p);
    return pth.parent_path().string();
}

string joinPath(const string& path, const string& child_path)
{
    filesystem::path p1(path);
    filesystem::path p2(child_path);

    if(p2.is_absolute()) {
        return p2.string();
    }

    string temp;
    for(int i = 0; i < child_path.size(); i++) {
        if(isDirectorySeparator(child_path[i]) || i == child_path.size()-1) {
            if(i == child_path.size()-1 && !isDirectorySeparator(child_path[i])) {
                temp.push_back(child_path[i]);
            }
            if(temp == ".") {
                p1 = filesystem::path(getCallPath());
            } else if(temp == "..") {
                p1 = p1.parent_path();
            } else {
                p1 /= temp;
            }
            temp.clear();
        } else {
            temp.push_back(child_path[i]);
        }
    }

    return p1.string();
}