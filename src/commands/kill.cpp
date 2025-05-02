#include "commands/kill.h"
#include <iostream>
#include <cstdlib>

#ifdef _WIN32
#include <windows.h>

void run_kill(const std::vector<std::string>& args) {
    if (args.size() < 2) {
        std::cerr << "kill: missing PID\n";
        return;
    }

    DWORD pid = std::stoul(args[1]);
    HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, pid);
    if (!hProcess) {
        std::cerr << "kill: cannot open process " << pid << "\n";
        return;
    }

    if (!TerminateProcess(hProcess, 1)) {
        std::cerr << "kill: failed to terminate process " << pid << "\n";
    }
    else {
        std::cout << "Process " << pid << " terminated.\n";
    }

    CloseHandle(hProcess);
}

#else
#include <signal.h>
#include <unistd.h>

void run_kill(const std::vector<std::string>& args) {
    if (args.size() < 2) {
        std::cerr << "kill: missing PID\n";
        return;
    }

    pid_t pid = std::stoi(args[1]);
    if (kill(pid, SIGTERM) != 0) {
        perror("kill");
    }
    else {
        std::cout << "Process " << pid << " terminated.\n";
    }
}
#endif
