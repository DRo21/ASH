#include "commands/less.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
char getch() {
    struct termios oldt {}, newt{};
    char ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = static_cast<char>(getchar());
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}
#endif

void run_less(const std::vector<std::string>& args) {
    if (args.size() < 2) {
        std::cerr << "Usage: less <filename>\n";
        return;
    }

    std::ifstream file(args[1]);
    if (!file.is_open()) {
        std::cerr << "less: Cannot open file: " << args[1] << "\n";
        return;
    }

    std::vector<std::string> lines;
    std::string line;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }

    const int page_size = 20;
    int current_line = 0;

    while (true) {
        for (int i = 0; i < page_size && current_line + i < lines.size(); ++i) {
            std::cout << lines[current_line + i] << "\n";
        }

        std::cout << "--Less-- (q = quit, space = next, b = back): ";
        char c =
#ifdef _WIN32
            _getch();
#else
            getch();
#endif
        std::cout << "\n";

        if (c == 'q') break;
        else if (c == ' ') {
            current_line += page_size;
            if (current_line >= lines.size()) break;
        }
        else if (c == 'b') {
            current_line -= page_size;
            if (current_line < 0) current_line = 0;
        }

        std::system("clear");
    }
}
