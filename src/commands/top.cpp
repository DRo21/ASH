#ifdef _WIN32

#include "commands/top.h"
#include <windows.h>
#include <psapi.h>
#include <tlhelp32.h>
#include <iostream>
#include <iomanip>
#include <conio.h>
#include <thread>
#include <chrono>
#include <map>

ULONGLONG fileTimeToULL(const FILETIME& ft) {
    return (static_cast<ULONGLONG>(ft.dwHighDateTime) << 32) | ft.dwLowDateTime;
}

bool is_key_pressed() {
    return _kbhit() && _getch() == 'q';
}

void run_top(const std::vector<std::string>& args) {
    std::map<DWORD, ULONGLONG> lastProcTimes;
    ULONGLONG lastSystemTime = 0;

    while (true) {
        system("cls");

        FILETIME idleTime, kernelTime, userTime;
        GetSystemTimes(&idleTime, &kernelTime, &userTime);
        ULONGLONG currentSystemTime = fileTimeToULL(kernelTime) + fileTimeToULL(userTime);

        HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        if (snapshot == INVALID_HANDLE_VALUE) {
            std::cerr << "top: Failed to take snapshot\n";
            return;
        }

        PROCESSENTRY32 pe;
        pe.dwSize = sizeof(PROCESSENTRY32);

        std::wcout << std::left << std::setw(8) << L"PID"
            << std::setw(30) << L"Name"
            << std::setw(12) << L"Memory (KB)"
            << std::setw(10) << L"CPU (%)" << L"\n";
        std::wcout << std::wstring(70, L'-') << L"\n";

        if (Process32First(snapshot, &pe)) {
            do {
                HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pe.th32ProcessID);
                if (hProcess) {
                    PROCESS_MEMORY_COUNTERS pmc;
                    FILETIME createTime, exitTime, kernelTime, userTime;

                    if (GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc)) &&
                        GetProcessTimes(hProcess, &createTime, &exitTime, &kernelTime, &userTime)) {

                        ULONGLONG currentProcTime = fileTimeToULL(kernelTime) + fileTimeToULL(userTime);
                        ULONGLONG lastProcTime = lastProcTimes[pe.th32ProcessID];

                        double cpuPercent = 0.0;
                        ULONGLONG deltaSystem = currentSystemTime - lastSystemTime;
                        ULONGLONG deltaProc = currentProcTime - lastProcTime;

                        if (lastSystemTime != 0 && deltaSystem > 0) {
                            cpuPercent = static_cast<double>(deltaProc) / deltaSystem * 100.0;
                        }

                        lastProcTimes[pe.th32ProcessID] = currentProcTime;

                        std::wcout << std::left << std::setw(8) << pe.th32ProcessID
                            << std::setw(30) << pe.szExeFile
                            << std::setw(12) << (pmc.WorkingSetSize / 1024)
                            << std::setw(10) << std::fixed << std::setprecision(2) << cpuPercent << "\n";
                    }
                    CloseHandle(hProcess);
                }
            } while (Process32Next(snapshot, &pe));
        }

        lastSystemTime = currentSystemTime;
        CloseHandle(snapshot);

        std::cout << "\nPress 'q' to quit.\n";
        for (int i = 0; i < 10; ++i) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            if (is_key_pressed()) return;
        }
    }
}

#else

#include "commands/top.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <dirent.h>
#include <unistd.h>
#include <vector>
#include <string>
#include <termios.h>
#include <fcntl.h>
#include <thread>
#include <chrono>
#include <map>

struct CPUData {
    unsigned long utime = 0;
    unsigned long stime = 0;
};

void set_nonblocking(bool enable) {
    struct termios ttystate;
    tcgetattr(STDIN_FILENO, &ttystate);
    if (enable) {
        ttystate.c_lflag &= ~ICANON;
        ttystate.c_lflag &= ~ECHO;
        ttystate.c_cc[VMIN] = 1;
        tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);
        fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);
    }
    else {
        ttystate.c_lflag |= ICANON;
        ttystate.c_lflag |= ECHO;
        tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);
        fcntl(STDIN_FILENO, F_SETFL, 0);
    }
}

bool is_key_pressed() {
    char c;
    if (read(STDIN_FILENO, &c, 1) > 0) {
        return c == 'q';
    }
    return false;
}

unsigned long long read_total_cpu_time() {
    std::ifstream stat("/proc/stat");
    std::string line;
    if (std::getline(stat, line)) {
        std::istringstream ss(line);
        std::string cpu;
        unsigned long long total = 0, val;
        ss >> cpu;
        while (ss >> val) total += val;
        return total;
    }
    return 0;
}

void run_top(const std::vector<std::string>& args) {
    set_nonblocking(true);
    std::map<std::string, CPUData> last_cpu;
    unsigned long long last_total_cpu = read_total_cpu_time();

    while (true) {
        system("clear");

        std::cout << std::left << std::setw(8) << "PID"
            << std::setw(30) << "Name"
            << std::setw(12) << "Memory (KB)"
            << std::setw(10) << "CPU (%)" << "\n";
        std::cout << std::string(70, '-') << "\n";

        DIR* proc = opendir("/proc");
        if (!proc) {
            std::cerr << "top: Failed to open /proc\n";
            break;
        }

        struct dirent* entry;
        while ((entry = readdir(proc)) != nullptr) {
            if (entry->d_type == DT_DIR && std::all_of(entry->d_name, entry->d_name + strlen(entry->d_name), ::isdigit)) {
                std::string pid(entry->d_name);
                std::string stat_path = "/proc/" + pid + "/stat";
                std::string comm_path = "/proc/" + pid + "/comm";
                std::string statm_path = "/proc/" + pid + "/statm";

                std::ifstream stat_file(stat_path), comm_file(comm_path), statm_file(statm_path);
                if (!stat_file || !comm_file || !statm_file) continue;

                std::string name;
                unsigned long mem;
                if (!(std::getline(comm_file, name) && (statm_file >> mem))) continue;

                std::string dummy;
                unsigned long utime, stime;
                for (int i = 0; i < 13; ++i) stat_file >> dummy;
                stat_file >> utime >> stime;

                unsigned long long total_cpu = read_total_cpu_time();
                auto& prev = last_cpu[pid];
                unsigned long long delta_cpu = total_cpu - last_total_cpu;
                double cpu_percent = 0.0;

                if (delta_cpu > 0) {
                    cpu_percent = (static_cast<double>((utime + stime) - (prev.utime + prev.stime)) / delta_cpu) * 100.0;
                }

                prev.utime = utime;
                prev.stime = stime;

                std::cout << std::left << std::setw(8) << pid
                    << std::setw(30) << name
                    << std::setw(12) << (mem * getpagesize() / 1024)
                    << std::setw(10) << std::fixed << std::setprecision(2) << cpu_percent << "\n";
            }
        }

        closedir(proc);
        last_total_cpu = read_total_cpu_time();

        std::cout << "\nPress 'q' to quit.\n";
        for (int i = 0; i < 10; ++i) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            if (is_key_pressed()) {
                set_nonblocking(false);
                return;
            }
        }
    }

    set_nonblocking(false);
}

#endif
