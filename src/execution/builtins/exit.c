#include <stdlib.h>
#include "types.h"
#include "builtins.h"

int exit_builtin(Command *cmd) {
    (void)cmd;
    exit(0);
    return 0;
}