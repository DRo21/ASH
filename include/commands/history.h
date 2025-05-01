#ifndef HISTORY_H
#define HISTORY_H

#include <vector>
#include <string>

void run_history();
void add_to_history(const std::string& command);
const std::vector<std::string>& get_history();

#endif