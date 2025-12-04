#ifndef TYPES_H
#define TYPES_H

#define MAX_ARGS 64

typedef struct {
    char *name;
    char *args[MAX_ARGS];
} Command;

#endif
