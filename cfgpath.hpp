/*
 * This code is based off Adam Nielsen's cfgpath C header found at
 * https://github.com/Malvineous/cfgpath
 *
 * Following his code being public domain I have licensed this using the
 * unlicense http://unlicense.org/. Full license text is available in
 * the LICENSE file
 */
#ifndef CFGPATH_HPP
#define CFGPATH_HPP

#include <string>
using std::string;

namespace cfgpath {

    const string defaultExt = ".ini";

/** Get an absolute path to a configuration folder, specific to this user.
 *
 * This function is useful for programs that need to store multiple
 * configuration files.  The output is a folder (which may not exist and will
 * need to be created) suitable for storing a number of files.
 *
 * The returned path will always end in a platform-specific trailing slash, so
 * that a filename can simply be appended to the path.
 *
 * Output is typically:
 *
 *   Windows: C:\Users\jcitizen\AppData\Roaming\appname\
 *   Linux: /home/jcitizen/.config/appname/
 *
 * @param appname
 *   Short name of the application.  Avoid using spaces or version numbers, and
 *   use lowercase if possible.
 *
 * @return
 *   A string containing the path
 *
 * @post The folder is created if needed.
 */
string get_user_config_folder(const string& appname);

/** Get an absolute path to a single configuration file, specific to this user.
 *
 * This function is useful for programs that need only a single configuration
 * file.  The file is unique to the user account currently logged in.
 *
 * Output is typically:
 *
 *   Windows: C:\Users\jcitizen\AppData\Roaming\appname.ini
 *   Linux: /home/jcitizen/.config/appname.conf
 *
 * @param appname
 *   Short name of the application.  Avoid using spaces or version numbers, and
 *   use lowercase if possible.
 *
 * @post The file may or may not exist.
 * @post The folder holding the file is created if needed.
 */
string get_user_config_file(const string& appname, const string& extension = defaultExt);

/** Get an absolute path to a data storage folder, specific to this user.
 *
 * This function is useful for programs that need to store larger amounts of
 * data specific to each user.  The output is a folder (which may not exist and
 * will need to be created) suitable for storing a number of data files.
 *
 * This path should be used for persistent, important data files the user would
 * want to keep.  Do not use this path for temporary files, cache files, or
 * other files that can be recreated if they are deleted.  Use
 * get_user_cache_folder() for those instead.
 *
 * The returned path will always end in a platform-specific trailing slash, so
 * that a filename can simply be appended to the path.
 *
 * Output is typically:
 *
 *   Windows: C:\Users\jcitizen\AppData\Roaming\appname-data\
 *   Linux: /home/jcitizen/.local/share/appname/
 *
 * @param appname
 *   Short name of the application.  Avoid using spaces or version numbers, and
 *   use lowercase if possible.
 *
 * @return
 *   String containing the path
 *
 * @post The folder is created if needed.
 */
string get_user_data_folder(const string& appname);

/** Get an absolute path to a temporary storage folder, specific to this user.
 *
 * This function is useful for programs that temporarily need to store larger
 * amounts of data specific to each user.  The output is a folder (which may
 * not exist and will need to be created) suitable for storing a number of
 * temporary files.  The files may be lost or deleted when the program
 * terminates.
 *
 * This path should be used for temporary, unimportant data files that can
 * safely be deleted after the program terminates.  Do not use this path for
 * any important files the user would want to keep.  Use get_user_data_folder()
 * for those instead.
 *
 * The returned path will always end in a platform-specific trailing slash, so
 * that a filename can simply be appended to the path.
 *
 * Output is typically:
 *
 *   Windows: C:\Users\jcitizen\AppData\Local\appname\
 *   Linux: /home/jcitizen/.cache/appname/
 *
 * @param appname
 *   Short name of the application.  Avoid using spaces or version numbers, and
 *   use lowercase if possible.
 *
 * @return
 *   String containing the path
 *
 * @post The folder is created if needed.
 */
string get_user_cache_folder(const string& appname);
}
#endif // CFGPATH_HPP
