#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "types.h"
#include "execution.h"
#include "input.h"
#include "builtins.h"

void execute_command(Command *cmd) {
    if (!cmd || !cmd->name) return;

    size_t count = 0;
    Builtin *builtins = get_builtins(&count);

    for (size_t i = 0; i < count; i++) {
        if(strcmp(cmd->name, builtins[i].name) == 0) {
            builtins[i].func(cmd);
            return;
        }
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        return;
    } else if (pid == 0) {
        execvp(cmd->name, cmd->args);
        perror("execvp");
        exit(EXIT_FAILURE);
    } else {
        int status;
        waitpid(pid, &status, 0);
    }
}
