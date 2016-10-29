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

\
#ifdef _WIN32
#include <shlobj.h>
#include <direct.h>
const char _pathSep = '\\';
#endif

#ifdef __unix__
#include <sys/stat.h>
const char _pathSep = '/';
#endif

using std::stringstream;

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
        if (mkdir(cfgPath.str().c_str(), 0700) != 0 && errno != EEXIST)
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

string cfgpath::get_user_config_file(const string& appname) {
    stringstream cfgPath;
    cfgPath << get_standard_config_path();
    cfgPath << appname;
    if (!createFileIfNotExist(cfgPath.str()))
        throw std::runtime_error("Unable to create application config file");
    return cfgPath.str();
}
