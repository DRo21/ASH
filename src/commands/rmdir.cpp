#include "rmdir.h"
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

void run_rmdir(const std::vector<std::string>& args) {
    if (args.size() < 2) {
        std::cerr << "rmdir: missing operand\n";
        return;
    }

    for (size_t i = 1; i < args.size(); ++i) {
        const std::string& dir = args[i];
        try {
            if (fs::remove(dir)) {
                std::cout << "rmdir: removed directory '" << dir << "'\n";
            }
            else {
                std::cerr << "rmdir: '" << dir << "' is not empty or doesn't exist\n";
            }
        }
        catch (const fs::filesystem_error& e) {
            std::cerr << "rmdir: " << e.what() << "\n";
        }
    }
}
