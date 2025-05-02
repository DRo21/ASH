#include "commands/uname.h"
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#include <sysinfoapi.h>
#else
#include <sys/utsname.h>
#endif

void run_uname(const std::vector<std::string>& args) {
#ifdef _WIN32
    std::cout << "Windows";

    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);

    std::string arch;
    switch (sysInfo.wProcessorArchitecture) {
    case PROCESSOR_ARCHITECTURE_AMD64: arch = "x86_64"; break;
    case PROCESSOR_ARCHITECTURE_INTEL: arch = "x86"; break;
    case PROCESSOR_ARCHITECTURE_ARM: arch = "ARM"; break;
    default: arch = "Unknown"; break;
    }

    std::cout << " (" << arch << ")\n";
#else
    struct utsname buffer;
    if (uname(&buffer) != 0) {
        perror("uname");
        return;
    }

    std::cout << buffer.sysname << " " << buffer.release << " " << buffer.machine << "\n";
#endif
}
