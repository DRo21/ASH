#include "core/command_handler.h"
#include <unordered_map>
#include <functional>
#include <iostream>

#include "commands/all_commands.h"

bool run_command(const std::vector<std::string>& tokens) {
    if (tokens.empty()) return false;

    static const std::unordered_map<std::string, std::function<void(const std::vector<std::string>&)>> command_map = {
        {"ls", run_ls},
        {"cd", run_cd},
        {"pwd", [](const auto& args) { run_pwd(); }},
        {"help", [](const auto& args) { run_help(); }},
        {"open", run_open},
        {"clear", [](const auto& args) { run_clear(); }},
        {"mkdir", run_mkdir},
        {"rmdir", run_rmdir},
        {"rm", run_rm},
        {"touch", run_touch},
        {"echo", run_echo},
        {"history", [](const auto& args) { run_history(); }},
        {"cat", run_cat},
        {"cp", run_cp},
        {"find", run_find},
        {"mv", run_mv},
        {"ln", run_ln},
        {"more", run_more},
        {"less", run_less },
        {"tail", run_tail},
        {"head", run_head}
    };

    const std::string& cmd = tokens[0];
    auto it = command_map.find(cmd);

    if (it != command_map.end()) {
        it->second(tokens);
        return true;
    }
    return false;
}
