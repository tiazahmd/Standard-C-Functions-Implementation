#define _GNU_SOURCE
#include <stdlib.h>
#include "tlpi_hdr.h"

extern char **environ;

int setenv_imp(const char *name, const char *value, int overwrite) {
    size_t len = strlen(name) + strlen(value) + 2;
    char **ep;

    if (name == NULL || name[0] == '\0' || strchr(name, '=') != NULL) {
        errno = EINVAL;
        return -1;
    }
    
    if (getenv(name) != NULL && overwrite == 0) {
        return 0;
    }

    unsetenv(name);

    char *st = malloc(len);
    if (st == NULL) {
        return -1;
    }

    strcpy(st, name);
    strcat(st, "=");
    strcat(st, value);

    if (putenv(st) == -1) {
        errExit("putenv");
    }

    return 0;
}