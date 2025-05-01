#include "commands/head.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

void run_head(const std::vector<std::string>& args) {
    const int num_lines = 10;

    if (args.size() < 2) {
        std::cerr << "Usage: head <filename>\n";
        return;
    }

    std::ifstream file(args[1]);
    if (!file.is_open()) {
        std::cerr << "head: Cannot open file: " << args[1] << "\n";
        return;
    }

    std::string line;
    int line_count = 0;

    while (std::getline(file, line)) {
        std::cout << line << "\n";
        line_count++;
        if (line_count >= num_lines) break;
    }
}
