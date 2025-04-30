#include "pwd.h"
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

void run_pwd() {
    try {
        std::cout << fs::current_path().string() << "\n";
    }
    catch (const fs::filesystem_error& e) {
        std::cerr << "pwd: " << e.what() << "\n";
    }
}
