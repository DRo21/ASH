#include <iostream>
#include <string>
#include "core/shell.h"
#include "commands/all_commands.h"
#include "core/command_handler.h"

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
        if (!run_command(tokens)) {
            int result = std::system(line.c_str());
            if (result != 0) {
                std::cerr << "Command failed: " << result << "\n";
            }
        }
    }
    return 0;
}