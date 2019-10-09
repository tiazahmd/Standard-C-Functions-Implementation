#include <sys/types.h>
#include <fcntl.h>
#include "tlpi_hdr.h"

int dup_imp(int oldfd) {
    int nfd = fcntl(oldfd, F_DUPFD, 0);
    if (nfd < 0) {
        errno = EBADF;
        return -1;
    }

    return nfd;
}