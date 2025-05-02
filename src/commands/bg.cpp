#include "commands/bg.h"
#include <iostream>
#include <map>
#include <string>

#ifdef _WIN32
#include <windows.h>
#include "job_state.h"

extern std::map<DWORD, JobInfo> backgroundJobs;

void run_bg(const std::vector<std::string>& args) {
    if (args.size() < 2) {
        std::cerr << "bg: Usage: bg <pid>\n";
        return;
    }

    DWORD pid = std::stoul(args[1]);
    auto it = backgroundJobs.find(pid);
    if (it == backgroundJobs.end()) {
        std::cerr << "bg: No such job with PID " << pid << "\n";
        return;
    }

    JobInfo& job = it->second;
    if (job.status == L"Stopped") {
        if (ResumeThread(job.handle) != (DWORD)-1) {
            job.status = L"Running";
            std::wcout << L"bg: Continued " << job.name << L" [" << job.pid << L"]\n";
        }
        else {
            std::cerr << "bg: Failed to resume process\n";
        }
    }
    else {
        std::cerr << "bg: Job is not stopped\n";
    }
}
#else
void run_bg(const std::vector<std::string>& args) {
    std::cerr << "bg: Not implemented on non-Windows systems in this simulation\n";
}
#endif
