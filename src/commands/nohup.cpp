#include "commands/nohup.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#endif

class NohupCommand {
public:
    void execute(const std::vector<std::string>& args) {
        if (args.empty()) {
            std::cerr << "nohup: missing command operand\n";
            return;
        }

        std::string outfile = "nohup.out";

#ifdef _WIN32
        std::string commandLine;
        for (const auto& arg : args) commandLine += arg + " ";

        HANDLE hFile = CreateFileA(outfile.c_str(), GENERIC_WRITE, FILE_SHARE_WRITE, nullptr,
            OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
        if (hFile == INVALID_HANDLE_VALUE) {
            std::cerr << "nohup: failed to open " << outfile << " for writing\n";
            return;
        }

        SetFilePointer(hFile, 0, nullptr, FILE_END);

        STARTUPINFOA si = { sizeof(si) };
        si.dwFlags |= STARTF_USESTDHANDLES;
        si.hStdOutput = hFile;
        si.hStdError = hFile;

        PROCESS_INFORMATION pi;
        BOOL success = CreateProcessA(
            nullptr, (LPSTR)commandLine.c_str(),
            nullptr, nullptr, TRUE,
            CREATE_NO_WINDOW, nullptr, nullptr, &si, &pi
        );

        if (!success) {
            std::cerr << "nohup: failed to run command\n";
        }
        else {
            std::cout << "nohup: process started in background (PID " << pi.dwProcessId << ")\n";
        }

        CloseHandle(hFile);
        CloseHandle(pi.hThread);
        CloseHandle(pi.hProcess);

#else

        pid_t pid = fork();
        if (pid < 0) {
            perror("nohup: fork failed");
            return;
        }

        if (pid == 0) {
            signal(SIGHUP, SIG_IGN);

            int fd = open(outfile.c_str(), O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (fd < 0) {
                perror("nohup: failed to open output file");
                exit(1);
            }

            dup2(fd, STDOUT_FILENO);
            dup2(fd, STDERR_FILENO);
            close(fd);

            std::vector<char*> argv;
            for (auto& arg : args) argv.push_back(&arg[0]);
            argv.push_back(nullptr);

            execvp(argv[0], argv.data());
            perror("nohup: exec failed");
            exit(1);
        }
        else {
            std::cout << "nohup: process started in background (PID " << pid << ")\n";
        }

#endif
    }
};

void run_nohup(const std::vector<std::string>& args) {
    NohupCommand nohup;
    nohup.execute(args);
}
