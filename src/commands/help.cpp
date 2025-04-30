#include "help.h"
#include <iostream>

void run_help() {
    std::cout << "Available commands:\n";
    std::cout << "  ls    - List directory contents\n";
    std::cout << "  cd    - Change directory\n";
    std::cout << "  pwd   - Print the current working directory\n";
    std::cout << "  help  - Display this help message\n";
    std::cout << "  exit  - Exit the shell\n";
}
