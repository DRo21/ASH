#include "types.h"
#include "builtins.h"

int cd_builtin(Command *cmd) {
    if (!cmd->args[1]) return 0;
    if (chdir(cmd->args[1]) != 0) perror("cd");
    return 0;
}
