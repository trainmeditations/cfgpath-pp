#include "cfgpath.hpp"
#include <iostream>

using namespace std;
using namespace cfgpath;

int main(int argc, char *argv[]) {
    cout << get_user_config_folder("test") << "\n";
    return 0;
}
