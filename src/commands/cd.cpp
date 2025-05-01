#include "commands/cd.h"
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

void run_cd(const std::vector<std::string>& args) {
    if (args.size() < 2) {
        std::cerr << "cd: missing operand\n";
        return;
    }
    try {
        fs::current_path(args[1]);
    }
    catch (const fs::filesystem_error& e) {
        std::cerr << "cd: " << e.what() << "\n";
    }
}
