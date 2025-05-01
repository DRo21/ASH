#include "commands/ln.h"
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

void run_ln(const std::vector<std::string>& args) {
    if (args.size() < 3) {
        std::cerr << "Usage: ln [-s] <target> <link_name>" << std::endl;
        return;
    }

    bool symbolic = false;
    size_t offset = 0;

    if (args[1] == "-s") {
        symbolic = true;
        offset = 1;
    }

    fs::path target = args[1 + offset];
    fs::path link_name = args[2 + offset];

    try {
        if (symbolic) {
            fs::create_symlink(target, link_name);
        }
        else {
            if (fs::is_directory(target)) {
                std::cerr << "ln error: hard links to directories are not supported.\n";
                return;
            }
            fs::create_hard_link(target, link_name);
        }
    }
    catch (const fs::filesystem_error& e) {
        std::cerr << "ln error: " << e.what() << std::endl;
    }
}
