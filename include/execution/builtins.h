#ifndef BUILTINS_H
#define BUILTINS_H

#include <stddef.h>
#include "types.h"

typedef struct {
    const char *name;
    int (*func)(Command *cmd);
} Builtin;

Builtin *get_builtins(size_t *count);

#endif
