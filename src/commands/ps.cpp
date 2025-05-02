#include "commands/ps.h"
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#include <tlhelp32.h>

void run_ps(const std::vector<std::string>& args) {
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snapshot == INVALID_HANDLE_VALUE) {
        std::cerr << "ps: Failed to take process snapshot\n";
        return;
    }

    PROCESSENTRY32 pe;
    pe.dwSize = sizeof(PROCESSENTRY32);

    if (!Process32First(snapshot, &pe)) {
        std::cerr << "ps: Failed to retrieve process info\n";
        CloseHandle(snapshot);
        return;
    }

    std::cout << "PID\tProcess Name\n";
    std::cout << "---------------------------\n";
    do {
        std::wcout << pe.th32ProcessID << "\t" << pe.szExeFile << "\n";
    } while (Process32Next(snapshot, &pe));

    CloseHandle(snapshot);
}

#else
#include <dirent.h>
#include <fstream>
#include <string>
#include <unistd.h>
#include <sstream>

void run_ps(const std::vector<std::string>& args) {
    std::cout << "PID\tProcess Name\n";
    std::cout << "---------------------------\n";

    DIR* proc = opendir("/proc");
    if (!proc) {
        std::cerr << "ps: Failed to open /proc\n";
        return;
    }

    struct dirent* entry;
    while ((entry = readdir(proc)) != nullptr) {
        if (entry->d_type == DT_DIR) {
            std::string pid_str(entry->d_name);
            if (std::all_of(pid_str.begin(), pid_str.end(), ::isdigit)) {
                std::ifstream cmdline("/proc/" + pid_str + "/comm");
                std::string name;
                if (std::getline(cmdline, name)) {
                    std::cout << pid_str << "\t" << name << "\n";
                }
            }
        }
    }
    closedir(proc);
}
#endif
