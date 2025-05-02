#ifndef JOB_STATE_H
#define JOB_STATE_H

#include <windows.h>
#include <string>
#include <map>

struct JobInfo {
    DWORD pid;
    std::wstring name;
    std::wstring status;
    HANDLE handle;
};

extern std::map<DWORD, JobInfo> backgroundJobs;

#endif