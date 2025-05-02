#include "commands/df.h"
#include <iostream>
#include <string>

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/statvfs.h>
#endif

void run_df(const std::vector<std::string>& args) {
#ifdef _WIN32
    ULARGE_INTEGER freeBytesAvailable, totalBytes, totalFreeBytes;
    if (GetDiskFreeSpaceExA(nullptr, &freeBytesAvailable, &totalBytes, &totalFreeBytes)) {
        auto toGB = [](ULARGE_INTEGER bytes) { return bytes.QuadPart / (1024 * 1024 * 1024); };

        std::cout << "Filesystem\tSize\tUsed\tFree\n";
        std::cout << "C:/\t\t"
            << toGB(totalBytes) << "G\t"
            << toGB(totalBytes) - toGB(totalFreeBytes) << "G\t"
            << toGB(totalFreeBytes) << "G\n";
    }
    else {
        std::cerr << "df: error retrieving disk space info\n";
    }
#else
    struct statvfs stat;
    if (statvfs("/", &stat) != 0) {
        perror("df");
        return;
    }

    unsigned long total = (stat.f_blocks * stat.f_frsize) / (1024 * 1024);
    unsigned long free = (stat.f_bfree * stat.f_frsize) / (1024 * 1024);
    unsigned long used = total - free;

    std::cout << "Filesystem\tSize\tUsed\tFree\n";
    std::cout << "/\t\t" << total << "M\t" << used << "M\t" << free << "M\n";
#endif
}
