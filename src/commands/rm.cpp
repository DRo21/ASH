#include "commands/rm.h"
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

void run_rm(const std::vector<std::string>& args) {
    if (args.size() < 2) {
        std::cerr << "rm: missing operand\n";
        return;
    }

    for (size_t i = 1; i < args.size(); ++i) {
        const std::string& path = args[i];
        try {
            if (fs::is_directory(path)) {
                std::cerr << "rm: cannot remove '" << path << "': Is a directory\n";
                continue;
            }

            if (fs::remove(path)) {
                std::cout << "rm: removed '" << path << "'\n";
            }
            else {
                std::cerr << "rm: cannot remove '" << path << "'\n";
            }
        }
        catch (const fs::filesystem_error& e) {
            std::cerr << "rm: " << e.what() << "\n";
        }
    }
}
