/*
 * This code is based off Adam Nielsen's cfgpath C header found at
 * https://github.com/Malvineous/cfgpath
 *
 * Following his code being public domain I have licensed this using the
 * unlicense http://unlicense.org/. Full license text is available in
 * the LICENSE file
 */

#include "cfgpath.hpp"

#include <stdexcept>
#include <cstdlib>
\
#ifdef _WIN32
#include <shlobj.h>
#include <direct.h>
#endif

#ifdef __unix__
#include <sys/stat.h>
#endif

string cfgpath::get_user_config_folder(const string& appname) {
    //Windows first, then Apple, then other *nixes
    string cfgPath;
#ifdef WIN32
    //using ansi windows for now
    //assume appdata directory exists
    char _confPath[MAX_PATH];
    if (!SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_APPDATA, NULL, 0, _confPath))) {
        throw std::runtime_error("Unable to get standard config path from system");
    }
    cfgPath=_confPath;
    cfgPath+= '\\';
    cfgPath+=appname;
    if (_mkdir(cfgPath.c_str()) != 0 && errno != EEXIST) {
        throw std::runtime_error("Unable to create application config folder");
    }
    cfgPath+= '\\';
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
        cfgPath = _confHome;
        cfgPath += '/';
        cfgPath += ".config";
        if (mkdir(cfgPath.c_str(), 0700) != 0 && errno != EEXIST)
            throw std::runtime_error("Unable to create .config in user home");
    } else {
        cfgPath=_confHome;
    }
    cfgPath += '/';
    cfgPath += appname;
    if (mkdir(cfgPath.c_str(), 0700) != 0 && errno != EEXIST)
        throw std::runtime_error("Unable to create application config directory");
    cfgPath += '/';
#else
    throw std::logic_error("Incompatible OS");
#endif
    return cfgPath;
}
