#include "commands/tail.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

void run_tail(const std::vector<std::string>& args) {
    const int num_lines = 10;

    if (args.size() < 2) {
        std::cerr << "Usage: tail <filename>\n";
        return;
    }

    std::ifstream file(args[1]);
    if (!file.is_open()) {
        std::cerr << "tail: Cannot open file: " << args[1] << "\n";
        return;
    }

    std::vector<std::string> lines;
    std::string line;

    while (std::getline(file, line)) {
        lines.push_back(line);
    }

    int start_line = (lines.size() > num_lines) ? lines.size() - num_lines : 0;

    for (int i = start_line; i < lines.size(); ++i) {
        std::cout << lines[i] << "\n";
    }
}
