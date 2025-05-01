#include "core/terminal.h"
#include "commands/more.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void run_more(const std::vector<std::string>& args) {
    if (args.size() < 2) {
        std::cerr << "Usage: more <filename>\n";
        return;
    }

    std::ifstream file(args[1]);
    if (!file) {
        std::cerr << "Could not open file: " << args[1] << "\n";
        return;
    }

    int page_size = get_terminal_height() - 1;
    std::string line;
    int line_count = 0;

    while (std::getline(file, line)) {
        std::cout << line << '\n';
        if (++line_count >= page_size) {
            std::cout << "--More-- (SPACE: page, ENTER: line, q: quit)";
            char ch = get_key();
            std::cout << "\r                                        \r";

            if (ch == 'q') break;
            else if (ch == '\n' || ch == '\r') line_count = page_size - 1;
            else line_count = 0;
        }
    }

    file.close();
}
