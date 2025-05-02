#include "commands/killall.h"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>

#ifdef _WIN32
#include <windows.h>
#include <tlhelp32.h>

void run_killall(const std::vector<std::string>& args) {
    if (args.size() < 2) {
        std::cerr << "killall: missing process name\n";
        return;
    }

    const std::string targetProcess = args[1];
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snapshot == INVALID_HANDLE_VALUE) {
        std::cerr << "killall: Failed to take snapshot\n";
        return;
    }

    PROCESSENTRY32 pe;
    pe.dwSize = sizeof(PROCESSENTRY32);

    if (!Process32First(snapshot, &pe)) {
        std::cerr << "killall: Failed to read process entry\n";
        CloseHandle(snapshot);
        return;
    }

    bool found = false;
    do {
        if (targetProcess == pe.szExeFile) {
            HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, pe.th32ProcessID);
            if (hProcess) {
                if (TerminateProcess(hProcess, 1)) {
                    std::cout << "Terminated process " << pe.szExeFile << " (PID: " << pe.th32ProcessID << ")\n";
                    found = true;
                }
                else {
                    std::cerr << "killall: Failed to terminate process " << pe.szExeFile << " (PID: " << pe.th32ProcessID << ")\n";
                }
                CloseHandle(hProcess);
            }
        }
    } while (Process32Next(snapshot, &pe));

    CloseHandle(snapshot);

    if (!found) {
        std::cerr << "killall: No processes found with the name " << targetProcess << "\n";
    }
}

#else
#include <signal.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>

void run_killall(const std::vector<std::string>& args) {
    if (args.size() < 2) {
        std::cerr << "killall: missing process name\n";
        return;
    }

    const std::string targetProcess = args[1];
    DIR* procDir = opendir("/proc");
    if (!procDir) {
        std::cerr << "killall: Failed to open /proc\n";
        return;
    }

    struct dirent* entry;
    bool found = false;
    while ((entry = readdir(procDir)) != nullptr) {
        if (entry->d_type == DT_DIR && std::all_of(entry->d_name, entry->d_name + strlen(entry->d_name), ::isdigit)) {
            std::string pid = entry->d_name;
            std::string commPath = "/proc/" + pid + "/comm";
            std::ifstream commFile(commPath);

            if (!commFile) continue;

            std::string processName;
            std::getline(commFile, processName);

            if (processName == targetProcess) {
                pid_t pidNum = std::stoi(pid);
                if (kill(pidNum, SIGTERM) == 0) {
                    std::cout << "Terminated process " << processName << " (PID: " << pidNum << ")\n";
                    found = true;
                }
                else {
                    std::cerr << "killall: Failed to terminate process " << processName << " (PID: " << pidNum << ")\n";
                }
            }
        }
    }

    closedir(procDir);

    if (!found) {
        std::cerr << "killall: No processes found with the name " << targetProcess << "\n";
    }
}
#endif
