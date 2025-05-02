#include "commands/uptime.h"
#include <iostream>
#include <chrono>

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/sysinfo.h>
#endif

void run_uptime(const std::vector<std::string>& args) {
#ifdef _WIN32
    ULONGLONG ms = GetTickCount64();
    uint64_t seconds = ms / 1000;
#else
    struct sysinfo info;
    if (sysinfo(&info) != 0) {
        perror("uptime");
        return;
    }
    uint64_t seconds = info.uptime;
#endif

    int days = seconds / 86400;
    seconds %= 86400;
    int hours = seconds / 3600;
    seconds %= 3600;
    int minutes = seconds / 60;
    seconds %= 60;

    std::cout << "Uptime: ";
    if (days > 0) std::cout << days << "d ";
    if (hours > 0 || days > 0) std::cout << hours << "h ";
    if (minutes > 0 || hours > 0 || days > 0) std::cout << minutes << "m ";
    std::cout << seconds << "s\n";
}
