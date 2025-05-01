#include "commands/mv.h"
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

void run_mv(const std::vector<std::string>& args) {
    if (args.size() != 3) {
        std::cerr << "Usage: mv <source> <destination>" << std::endl;
        return;
    }

    fs::path source = args[1];
    fs::path destination = args[2];

    try {
        if (fs::is_directory(destination)) {
            destination /= source.filename();
        }
        fs::rename(source, destination);
    }
    catch (const fs::filesystem_error& e) {
        std::cerr << "mv error: " << e.what() << std::endl;
    }
}
