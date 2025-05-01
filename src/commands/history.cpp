#include "commands/history.h"
#include <iostream>

static std::vector<std::string> command_history;

void run_history() {
    for (size_t i = 0; i < command_history.size(); ++i) {
        std::cout << i + 1 << "  " << command_history[i] << "\n";
    }
}

void add_to_history(const std::string& command) {
    command_history.push_back(command);
}

const std::vector<std::string>& get_history() {
    return command_history;
}
