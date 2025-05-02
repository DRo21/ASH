#include "commands/du.h"
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

void run_du(const std::vector<std::string>& args) {
    if (args.size() < 2) {
        std::cerr << "du: missing operand\n";
        return;
    }

    fs::path target = args[1];

    if (!fs::exists(target)) {
        std::cerr << "du: " << target << ": No such file or directory\n";
        return;
    }

    uintmax_t totalSize = 0;

    if (fs::is_regular_file(target)) {
        totalSize = fs::file_size(target);
    }
    else {
        for (auto& entry : fs::recursive_directory_iterator(target, fs::directory_options::skip_permission_denied)) {
            if (fs::is_regular_file(entry.path())) {
                totalSize += fs::file_size(entry.path());
            }
        }
    }

    std::cout << (totalSize / (1024 * 1024)) << "M\t" << target.string() << "\n";
}
