#include "ls.h"
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

void run_ls(const std::vector<std::string>& args) {
    fs::path dir = ".";
    if (args.size() > 1) {
        dir = args[1];
    }

    try {
        for (const auto& entry : fs::directory_iterator(dir)) {
            std::cout << entry.path().filename().string() << "\n";
        }
    }
    catch (const fs::filesystem_error& e) {
        std::cerr << "ls: " << e.what() << "\n";
    }
}
