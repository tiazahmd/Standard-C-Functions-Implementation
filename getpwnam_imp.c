#include <pwd.h>
#include <ctype.h>
#include <stdio.h>

struct passwd *getpwnam_imp(const char *name) {
    static struct passwd *pwd;
    while ((pwd = getpwent()) != NULL) {
        if (strcmp(name, pwd->pw_name) == 0) {
            endpwent();
            return pwd;
        }
    }
    return NULL;
}