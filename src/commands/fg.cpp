#include "commands/fg.h"
#include <iostream>
#include <map>
#include <string>

#ifdef _WIN32
#include <windows.h>
#include "job_state.h"

extern std::map<DWORD, JobInfo> backgroundJobs;

void run_fg(const std::vector<std::string>& args) {
    if (args.size() < 2) {
        std::cerr << "fg: Usage: fg <pid>\n";
        return;
    }

    DWORD pid = std::stoul(args[1]);
    auto it = backgroundJobs.find(pid);
    if (it == backgroundJobs.end()) {
        std::cerr << "fg: No such job with PID " << pid << "\n";
        return;
    }

    JobInfo& job = it->second;
    std::wcout << L"fg: Bringing job to foreground: " << job.name << L" [" << job.pid << L"]\n";

    ResumeThread(job.handle);
    WaitForSingleObject(job.handle, INFINITE);

    job.status = L"Exited";
    CloseHandle(job.handle);
    backgroundJobs.erase(it);
}
#else
void run_fg(const std::vector<std::string>& args) {
    std::cerr << "fg: Not implemented on non-Windows systems in this simulation\n";
}
#endif
