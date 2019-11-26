#define _GNU_SOURCE
#include <grp.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>

#define SG_SIZE (NGROUPS_MAX + 1)

int initgroups_imp(const char *user, gid_t group) {
    gid_t suppGroups[SG_SIZE];
    int count = 0;
    static struct group *grp;
    while ((grp = getgrent()) != NULL) {
        if (grp->gr_mem[0] != NULL) {
            for (int i = 0; i < sizeof(grp->gr_mem); i++) {
                if (grp->gr_mem[i] == NULL) {
                    break;
                }
                if (strcmp(user, grp->gr_mem[i]) == 0) {
                    suppGroups[count] = grp->gr_gid;
                    count++;
                }
            }
        }
    }

    suppGroups[count] = group;
    count++;

    if (setgroups(count, suppGroups) == -1) {
        return -1;
    }
    
    return 0;
}