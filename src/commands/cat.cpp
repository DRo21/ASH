#include "cat.h"
#include <iostream>
#include <fstream>

void run_cat(const std::vector<std::string>& args) {
    if (args.size() < 2) {
        std::cerr << "cat: missing file operand\n";
        return;
    }

    for (size_t i = 1; i < args.size(); ++i) {
        std::ifstream file(args[i]);
        if (!file) {
            std::cerr << "cat: cannot open file '" << args[i] << "'\n";
            continue;
        }

        std::string line;
        while (std::getline(file, line)) {
            std::cout << line << "\n";
        }
    }
}
