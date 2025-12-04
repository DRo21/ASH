#include <stdio.h>
#include "types.h"
#include "builtins.h"

int echo_builtin(Command *cmd) {
    if (!cmd || !cmd->args) return 0;

    for (int i = 1; cmd->args[i]; i++) {
        printf("%s", cmd->args[i]);
        if (cmd->args[i+1]) printf(" ");
    }
    printf("\n");
    return 0;
}
