#include <sys/types.h>
#include <fcntl.h>
#include "tlpi_hdr.h"

int dup2_imp(int oldfd, int newfd) {
    if (fcntl(oldfd, F_GETFL) == -1) {
            errno = EBADF;
            return -1;
        }

    if (oldfd == newfd) {
        return newfd;
    }

    if (fcntl(newfd, F_GETFL) != -1) {
        if (close(newfd) == -1) {
            errExit("dup2 close");
        }
    }

    int nfd = fcntl(oldfd, F_DUPFD, newfd);
    if (nfd < 0) {
        errno = EBADF;
        return -1;
    }

    return nfd;
}