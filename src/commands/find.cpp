#include "commands/find.h"
#include <iostream>
#include <filesystem>
#include <string>

namespace fs = std::filesystem;

void run_find(const std::vector<std::string>& args) {
    fs::path start_path = ".";
    std::string target_name;

    if (args.size() == 2) {
        target_name = args[1];
    }
    else if (args.size() == 3) {
        start_path = args[1];
        target_name = args[2];
    }
    else {
        std::cerr << "Usage: find [path] <filename>\n";
        return;
    }

    try {
        for (const auto& entry : fs::recursive_directory_iterator(start_path)) {
            if (entry.path().filename() == target_name) {
                std::cout << entry.path().string() << "\n";
            }
        }
    }
    catch (const fs::filesystem_error& e) {
        std::cerr << "find: " << e.what() << "\n";
    }
}
