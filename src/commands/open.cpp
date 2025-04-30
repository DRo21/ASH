#include "open.h"
#include <iostream>
#include <cstdlib>
#include <vector>

#ifdef _WIN32
#include <windows.h>
#else
#include <cstdlib>
#endif

void run_open(const std::vector<std::string>& args) {
    if (args.size() < 2) {
        std::cerr << "open: missing file operand\n";
        return;
    }

    std::string filepath = args[1];

#ifdef _WIN32
    if (ShellExecuteA(NULL, "open", filepath.c_str(), NULL, NULL, SW_SHOWNORMAL) <= (HINSTANCE)32) {
        std::cerr << "Failed to open file: " << filepath << std::endl;
    }
#elif defined(__APPLE__)
    std::string command = "open " + filepath;
    int result = std::system(command.c_str());
    if (result != 0) {
        std::cerr << "Failed to open file: " << filepath << std::endl;
    }
#else
    std::string command = "xdg-open " + filepath;
    int result = std::system(command.c_str());
    if (result != 0) {
        std::cerr << "Failed to open file: " << filepath << std::endl;
    }
#endif
}