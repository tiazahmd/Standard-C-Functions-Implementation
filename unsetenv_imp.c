#define _GNU_SOURCE
#include <stdlib.h>
#include "tlpi_hdr.h"

extern char **environ;

int unsetenv_imp(const char *name) {
    char **ep, **sp;
    size_t len = strlen(name);
    if (name == NULL || name[0] == '\0' || strchr(name, '=') != NULL) {
        errno = EINVAL;
        return -1;
    }

    for (ep = environ; *ep != NULL; ep++) {
        if (strncmp(name, *ep, len) == 0 && (*ep)[len] == '=') {
            for (sp = ep; *sp != NULL; sp++) {
                *sp = *(sp + 1);
            }
        }
    }
    
    return 0;
}