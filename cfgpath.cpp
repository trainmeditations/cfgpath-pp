/*
 * This code is based off Adam Nielsen's cfgpath C header found at
 * https://github.com/Malvineous/cfgpath
 *
 * Following his code being public domain I have licensed this using the
 * unlicense http://unlicense.org/. Full license text is available in
 * the LICENSE file
 */

#include "cfgpath.hpp"

#include <sstream>
#include <stdexcept>
#include <cstdlib>

#ifdef _WIN32
#include <shlobj.h>
#include <direct.h>
const char _pathSep = '\\';
#endif

#ifdef __unix__
#include <sys/stat.h>
#include <errno.h>
const char _pathSep = '/';
#endif

using std::stringstream;

bool createDirectoryIfNotExist(const string& path) {
#ifdef WIN32
    return (_mkdir(path.c_str()) == 0 || errno == EEXIST);
#elif defined(__APPLE__)
#elif defined(__unix__)
    return (mkdir(path.c_str(), 0700) == 0 || errno == EEXIST);
#else
    throw std::logic_error("Incompatible OS");
#endif
}

string get_standard_config_path() {
    stringstream cfgPath;
    //Windows first, then Apple, then other *nixes
#ifdef WIN32
    //using ansi windows for now
    //assume appdata directory exists
    char _confPath[MAX_PATH];
    if (!SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_APPDATA, NULL, 0, _confPath))) {
        throw std::runtime_error("Unable to get standard config path from system");
    }
    cfgPath<< _confPath;
    cfgPath<< _pathSep;
#elif defined(__APPLE__)
#elif defined(__unix__)
    //Follow XDG Specification
    //Assume $XDG_CONFIG_HOME exists if it's set
    //Assume $HOME exists if it's set
    const char * _confHome = getenv("XDG_CONFIG_HOME");
    if (!_confHome) {
        //XDG_CONFIG_HOME isn't set. USE $HOME/.config
        _confHome = getenv("HOME");
        if (!_confHome) throw std::runtime_error("Unable to find home directory");
        cfgPath << _confHome;
        cfgPath << _pathSep;
        cfgPath << ".config";
        if (!createDirectoryIfNotExist(cfgPath.str()))
            throw std::runtime_error("Unable to create .config in user home");
    } else {
        cfgPath << _confHome;
    }
    cfgPath << _pathSep;
#else
    throw std::logic_error("Incompatible OS");
#endif
    return cfgPath.str();
}

bool createFileIfNotExist(const string& path) {
    return true;
}

string cfgpath::get_user_config_folder(const string& appname) {
    stringstream cfgPath;
    cfgPath << get_standard_config_path();
    cfgPath << appname;
    if (!createDirectoryIfNotExist(cfgPath.str()))
        throw std::runtime_error("Unable to create application config directory");
    cfgPath << _pathSep;
    return cfgPath.str();
}

string cfgpath::get_user_config_file(const string& appname, const string& extension) {
    stringstream cfgPath;
    cfgPath << get_standard_config_path() << appname << extension;
    return cfgPath.str();
}

string cfgpath::get_user_data_folder(const string& appname) {
    stringstream cfgPath;
    //Windows first, then Apple, then other *nixes
#ifdef WIN32
    //same path as config
    cfgPath << get_user_config_folder(appname);
#elif defined(__APPLE__)
#elif defined(__unix__)
    //Follow XDG Specification
    //Assume $XDG_DATA_HOME exists if it's set
    //Assume $HOME exists if it's set
    const char * _dataHome = getenv("XDG_DATA_HOME");
    if (!_dataHome) {
        //XDG_DATA_HOME isn't set. USE $HOME/.local/share
        _dataHome = getenv("HOME");
        if (!_dataHome) throw std::runtime_error("Unable to find home directory");
        cfgPath << _dataHome << _pathSep << ".local";
        if (!createDirectoryIfNotExist(cfgPath.str()))
            throw std::runtime_error("Unable to create .local in user home");
        cfgPath << _pathSep << "share";
        if (!createDirectoryIfNotExist(cfgPath.str()))
            throw std::runtime_error("Unable to create share in user home/.local");
    } else {
        cfgPath << _dataHome;
    }
    cfgPath << _pathSep << appname;
    if (!createDirectoryIfNotExist(cfgPath.str()))
        throw std::runtime_error("Unable to create application data directory");
    cfgPath << _pathSep;
#else
    throw std::logic_error("Incompatible OS");
#endif
    return cfgPath.str();
}

string cfgpath::get_user_cache_folder(const string& appname) {
    stringstream cfgPath;
    //Windows, Apple, other *nixes
#ifdef WIN32
    //using ansi windows for now
    //assume appdata directory exists
    char _cachePath[MAX_PATH];
    if (!SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_LOCAL_APPDATA, NULL, 0, _cachePath))) {
        throw std::runtime_error("Unable to get standard config path from system");
    }
    cfgPath << _cachePath;
    cfgPath << _pathSep;
    cfgPath << appname;
    if (!createDirectoryIfNotExist(cfgPath.str()))
        throw std::runtime_error("Unable to create application cache directory");
    cfgPath << _pathSep;
#elif defined(__APPLE__)
#elif defined(__unix__)
#else
    throw std::logic_error("Incompatible OS");
#endif
    return cfgPath.str();
}
