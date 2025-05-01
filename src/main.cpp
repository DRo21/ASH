#include <iostream>
#include <string>
#include "shell.h"
#include "ls.h"
#include "cd.h"
#include "pwd.h"
#include "help.h"
#include "open.h"
#include "clear.h"
#include "mkdir.h"
#include "rmdir.h"
#include "rm.h"
#include "touch.h"
#include "echo.h"
#include "history.h"
#include "cat.h"

int main() {
    std::string line;

    while (true) {
        std::cout << "ASH> ";
        std::getline(std::cin, line);

        if (line.empty()) continue;
        add_to_history(line);

        auto tokens = split(line);
        const std::string& cmd = tokens[0];

        if (cmd == "exit") break;
        else if (cmd == "ls") run_ls(tokens);
        else if (cmd == "cd") run_cd(tokens);
        else if (cmd == "pwd") run_pwd();
        else if (cmd == "help") run_help();
        else  if (cmd == "open") run_open(tokens);
        else if (cmd == "clear") run_clear();
        else if (cmd == "mkdir") run_mkdir(tokens);
        else if (cmd == "rmdir") run_rmdir(tokens);
        else if (cmd == "rm") run_rm(tokens);
        else if (cmd == "touch") run_touch(tokens);
        else if (cmd == "echo") run_echo(tokens);
        else if (cmd == "history") run_history();
        else if (cmd == "cat") run_cat(tokens);
        else {
            int result = std::system(line.c_str());
            if (result != 0) {
                std::cerr << "Command failed: " << result << "\n";
            }
        }
    }
    return 0;
}
