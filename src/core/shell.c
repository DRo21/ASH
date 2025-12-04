#include <stdio.h>
#include <stdlib.h>
#include "shell.h"
#include "types.h"
#include "input.h"
#include "environment.h"

void init_shell(void)
{
    printf("Initializing shell...\n");
    init_environment();
}

void run_shell_loop(void)
{
    Command *cmd = NULL;

    while (1)
    {
        printf("$ ");
        cmd = read_and_parse_input();
        if (!cmd)
            break;

        execute_command(cmd);
        free(cmd);
    }
}

void cleanup_shell(void)
{
    printf("Cleaning up shell...\n");
    cleanup_environment();
}

int main(void)
{
    init_shell();
    run_shell_loop();
    cleanup_shell();
    return 0;
}
