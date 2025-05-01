#include "cp.h"
#include <iostream>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

void run_cp(const std::vector<std::string>& args) {
    if (args.size() < 3) {
        std::cerr << "cp: missing file operand\n";
        return;
    }

    fs::path source = args[1];
    fs::path destination = args[2];

    try {
        if (fs::is_directory(source)) {
            if (!fs::exists(destination)) {
                fs::create_directory(destination);
            }
            for (const auto& entry : fs::directory_iterator(source)) {
                fs::copy(entry, destination / entry.path().filename());
            }
        }
        else {
            fs::copy(source, destination, fs::copy_options::overwrite_existing);
        }
        std::cout << "Copied " << source << " to " << destination << "\n";
    }
    catch (const fs::filesystem_error& e) {
        std::cerr << "cp: " << e.what() << "\n";
    }
}
