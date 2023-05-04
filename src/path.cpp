#include <string>
#include <filesystem>
#include <unistd.h>
#ifdef _WIN32
    #include <windows.h>
#endif
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
    char temp[MAX_PATH];
    string path;
    #ifdef _WIN32
        GetModuleFileName(NULL, temp, MAX_PATH);
        path = temp;
    #elif __linux__
        path = filesystem::canonical("/proc/self/exe");
    #else
        return getCallPath();
    #endif
    filesystem::path pth(path);
    return pth.parent_path().string();
}

string joinPath(const string& path, const string& child_path)
{
    filesystem::path p1(path);
    filesystem::path p2(child_path);
    return filesystem::weakly_canonical(p1 / p2).string();
}