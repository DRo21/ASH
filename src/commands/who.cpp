#include "commands/who.h"
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#include <lmcons.h>
#else
#include <unistd.h>
#include <pwd.h>
#endif

void run_who(const std::vector<std::string>& args) {
#ifdef _WIN32
    char username[UNLEN + 1];
    DWORD size = UNLEN + 1;
    if (GetUserNameA(username, &size)) {
        std::cout << username << "\n";
    }
    else {
        std::cerr << "who: failed to get username\n";
    }
#else
    struct passwd* pw = getpwuid(getuid());
    if (pw) {
        std::cout << pw->pw_name << "\n";
    }
    else {
        std::cerr << "who: failed to get username\n";
    }
#endif
}
