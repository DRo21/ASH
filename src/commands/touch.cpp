#include "touch.h"
#include <iostream>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

void run_touch(const std::vector<std::string>& args) {
    if (args.size() < 2) {
        std::cerr << "touch: missing file operand\n";
        return;
    }

    for (size_t i = 1; i < args.size(); ++i) {
        const std::string& filename = args[i];

        try {
            std::ofstream file(filename, std::ios::app);
            if (!file) {
                std::cerr << "touch: cannot create file '" << filename << "'\n";
            }
        }
        catch (const std::exception& e) {
            std::cerr << "touch: " << e.what() << "\n";
        }
    }
}
