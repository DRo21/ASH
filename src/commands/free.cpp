#include "commands/free.h"
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/sysinfo.h>
#endif

void run_free(const std::vector<std::string>& args) {
    std::cout << "Memory\t\tTotal\tUsed\tFree\n";

#ifdef _WIN32
    MEMORYSTATUSEX memInfo;
    memInfo.dwLength = sizeof(memInfo);

    if (GlobalMemoryStatusEx(&memInfo)) {
        DWORDLONG totalPhys = memInfo.ullTotalPhys;
        DWORDLONG freePhys = memInfo.ullAvailPhys;
        DWORDLONG usedPhys = totalPhys - freePhys;

        std::cout << "Physical\t"
            << totalPhys / (1024 * 1024) << "M\t"
            << usedPhys / (1024 * 1024) << "M\t"
            << freePhys / (1024 * 1024) << "M\n";
    }
    else {
        std::cerr << "free: failed to get memory info\n";
    }

#else
    struct sysinfo info;
    if (sysinfo(&info) == 0) {
        unsigned long total = info.totalram * info.mem_unit / (1024 * 1024);
        unsigned long free = info.freeram * info.mem_unit / (1024 * 1024);
        unsigned long used = total - free;

        std::cout << "Physical\t"
            << total << "M\t"
            << used << "M\t"
            << free << "M\n";
    }
    else {
        perror("free");
    }
#endif
}
