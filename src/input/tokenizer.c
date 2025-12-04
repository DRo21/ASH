#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "input.h"

Command *read_and_parse_input(void)
{
    char *line = NULL;
    size_t len = 0;

    if (getline(&line, &len, stdin) == -1)
    {
        free(line);
        return NULL;
    }

    Command *cmd = malloc(sizeof(Command));
    cmd->argc = 0;
    cmd->argv = NULL;
    free(line);
    return cmd;
}
