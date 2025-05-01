#include "mkdir.h"
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

void run_mkdir(const std::vector<std::string>& args) {
    if (args.size() < 2) {
        std::cerr << "mkdir: missing operand\n";
        return;
    }

    for (size_t i = 1; i < args.size(); ++i) {
        const std::string& dir = args[i];
        try {
            if (fs::create_directory(dir)) {
                std::cout << "mkdir: created directory '" << dir << "'\n";
            }
            else {
                std::cerr << "mkdir: failed to create '" << dir << "' (already exists?)\n";
            }
        }
        catch (const fs::filesystem_error& e) {
            std::cerr << "mkdir: " << e.what() << "\n";
        }
    }
}
