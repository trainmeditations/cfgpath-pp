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

string cfgpath::get_user_config_folder(const string& appname) {
    //Windows first, then Apple, then other *nixes
    string cfgPath;
#ifdef WIN32
    //using ansi windows for now
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
    const char * _confHome = getenv("XDG_CONFIG_HOME");

#else
#endif
    return cfgPath;
}
