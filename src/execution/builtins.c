#include <stddef.h>
#include "builtins.h"
#include "types.h"

int cd_builtin(Command *cmd);
int echo_builtin(Command *cmd);
int exit_builtin(Command *cmd);

static Builtin builtins[] = {
    {"cd", cd_builtin},
    {"echo", echo_builtin},
    {"exit", exit_builtin},
};

Builtin *get_builtins(size_t *count) {
    if (count) *count = sizeof(builtins) / sizeof(Builtin);
    return builtins;
}
