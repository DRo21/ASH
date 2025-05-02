#include "commands/w.h"
#include <iostream>
#include <chrono>

#ifdef _WIN32
#include <windows.h>
#include <lmcons.h>
#else
#include <unistd.h>
#include <pwd.h>
#include <sys/sysinfo.h>
#endif

void run_w(const std::vector<std::string>& args) {
#ifdef _WIN32
    char username[UNLEN + 1];
    DWORD size = UNLEN + 1;
    GetUserNameA(username, &size);

    ULONGLONG ms = GetTickCount64();
    uint64_t uptime = ms / 1000;
#else
    struct passwd* pw = getpwuid(getuid());
    const char* username = pw ? pw->pw_name : "unknown";

    struct sysinfo info;
    sysinfo(&info);
    uint64_t uptime = info.uptime;
#endif

    int hours = uptime / 3600;
    int minutes = (uptime % 3600) / 60;

    std::cout << "User: " << username << " | Uptime: " << hours << "h " << minutes << "m\n";
}
