#include "cfgpath.hpp"
#include <iostream>

using namespace std;
using namespace cfgpath;

const string EOL = "\n";

int main(int argc, char *argv[]) {
    cout << get_user_config_folder("test") << EOL;
    cout << get_user_config_file("test", ".ini") << EOL;
    return 0;
}
