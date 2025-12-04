#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "input.h"

#define MAX_LINE 1024

Command *read_and_parse_input(void)
{
    char line[MAX_LINE];

    if (!fgets(line, MAX_LINE, stdin)) {
        return NULL;
    }

    line[strcspn(line, "\n")] = 0;

    Command *cmd = malloc(sizeof(Command));
    if (!cmd) return NULL;

    cmd->name = NULL;
    for (int i = 0; i < MAX_ARGS; i++) {
        cmd->args[i] = NULL;
    }

    char *token = strtok(line, " ");
    int arg_index = 0;
    while (token && arg_index < MAX_ARGS - 1) {
        if (arg_index == 0) {
            cmd->name = strdup(token);
        }
        cmd->args[arg_index++] = strdup(token);
        token = strtok(NULL, " ");
    }
    cmd->args[arg_index] = NULL;

    return cmd;
}
