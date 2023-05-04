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

bool isFile(const string& path)
{
    filesystem::path p = path;
    return filesystem::is_regular_file(p);
}

bool isFolder(const string& path)
{
    filesystem::path p = path;
    return filesystem::is_directory(p);
}

bool isDirectorySeparator(char ch)
{
    char preferred = std::filesystem::path::preferred_separator;
    if(ch == preferred || ch == '/' && preferred == '\\') {
        return true;
    }
    return false;
}

char directorySeparator()
{
    return filesystem::path::preferred_separator;
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
    return filesystem::weakly_canonical(p1 / p2).string();
}