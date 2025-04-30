#include "shell.h"
#include <sstream>
#include <vector>

std::vector<std::string> split(const std::string& input) {
    std::istringstream iss(input);
    std::vector<std::string> tokens;
    std::string word;
    while (iss >> word) {
        tokens.push_back(word);
    }
    return tokens;
}
