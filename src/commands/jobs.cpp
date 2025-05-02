#ifdef _WIN32
#include "commands/jobs.h"
#include "job_state.h"
#include <iostream>
#include <windows.h>
#include <tlhelp32.h>
#include <map>
#include <iomanip>
#include <string>

std::map<DWORD, JobInfo> backgroundJobs;

extern std::map<DWORD, JobInfo> backgroundJobs;

bool isProcessRunning(DWORD pid) {
    HANDLE hProcess = OpenProcess(SYNCHRONIZE, FALSE, pid);
    if (!hProcess) return false;
    DWORD result = WaitForSingleObject(hProcess, 0);
    CloseHandle(hProcess);
    return result == WAIT_TIMEOUT;
}

void run_jobs(const std::vector<std::string>& args) {
    std::wcout << std::left << std::setw(8) << L"PID"
        << std::setw(30) << L"Name"
        << std::setw(15) << L"Status" << L"\n";
    std::wcout << std::wstring(53, L'-') << L"\n";

    for (auto it = backgroundJobs.begin(); it != backgroundJobs.end(); ) {
        DWORD pid = it->first;
        JobInfo& job = it->second;

        if (isProcessRunning(pid)) {
            job.status = L"Running";
        }
        else {
            job.status = L"Exited";
        }

        std::wcout << std::left << std::setw(8) << job.pid
            << std::setw(30) << job.name
            << std::setw(15) << job.status << L"\n";

        ++it;
    }
}

#else
#include "commands/jobs.h"
#include <iostream>
#include <fstream>
#include <dirent.h>
#include <unistd.h>
#include <string>

void run_jobs(const std::vector<std::string>& args) {
    DIR* procDir = opendir("/proc");
    if (!procDir) {
        std::cerr << "jobs: Failed to open /proc directory\n";
        return;
    }

    struct dirent* entry;
    std::cout << "Job ID  PID   Status    Command\n";
    std::cout << std::string(40, '-') << "\n";

    while ((entry = readdir(procDir)) != nullptr) {
        if (entry->d_type == DT_DIR && std::all_of(entry->d_name, entry->d_name + strlen(entry->d_name), ::isdigit)) {
            std::string pid = entry->d_name;
            std::string stat_path = "/proc/" + pid + "/stat";
            std::ifstream stat_file(stat_path);

            if (stat_file) {
                std::string ignore, status;
                std::getline(stat_file, ignore, '(');
                std::getline(stat_file, ignore, ')');
                stat_file >> ignore >> ignore >> ignore >> ignore >> status;
                std::string comm_path = "/proc/" + pid + "/comm";
                std::ifstream comm_file(comm_path);

                std::string comm_name;
                if (comm_file) {
                    std::getline(comm_file, comm_name);
                    std::cout << pid << "    " << status << "   " << comm_name << "\n";
                }
            }
        }
    }

    closedir(procDir);
}
#endif
