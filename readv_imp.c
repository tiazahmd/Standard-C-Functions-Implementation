/*
Implement readv() and writev() using read(), write(), and suitable functions from the
malloc package.

`readv()` returns number of bytes read, 0 on EOF and -1 on error
`writev()` returns number of bytes written, 0 on EOF and -1 on error

In order to implement this, we need to know how `read()` and `write()` work. 
`read()` takes a file descriptor, reads `count` bytes of data and stores `count`
bytes of data in `buf`. For `readvd()`, the process is going to be the same,
but instead of storing it in `buf`, it will store in an array of `buffs`, so in
`buf[i]`. That `buf` is known as `iovec` in `readv()`.

*/

#include <sys/stat.h>
#include <fcntl.h>
#include <sys/uio.h>
#include <limits.h>
#include <alloca.h>
#include "tlpi_hdr.h"

#ifndef SSIZE_MAX
#define SSIZE_MAX LONG_MAX
#endif

#define BUF_SIZE 25
#define MEM_SIZE 1024

ssize_t readv_imp(int fd, const struct iovec *iov, int iovcnt) {
    ssize_t bytes = 0;
    ssize_t memBytes = 0;

    for (int i = 0; i < iov[i].iov_len; i++) {
        if (SSIZE_MAX - bytes < iov[i].iov_len ||
                                    iovcnt <= 0) {
            errno = EINVAL;
            return -1;
        } else {
            bytes += iov[i].iov_len;
        }
    }

    memBytes = bytes;
    char *buf;
    if (memBytes > MEM_SIZE) {
        buf = malloc(bytes);
    } else {
        buf = alloca(bytes);
    }

    if (buf == NULL) {
        return -1;
    }

    ssize_t bytes_read = 0;
    ssize_t copy = 0;
    
    bytes_read = read(fd, buf, bytes);
    if (bytes_read < 0) {
        return -1;
    }

    bytes = bytes_read;

    for (int i = 0; i < iovcnt; i++) {
        copy = min (iov[i].iov_len, bytes);

        memcpy(iov[i].iov_base, buf, copy);
        
        buf += copy;
        bytes -= copy;
        
        if (bytes == 0) {
            break;
        }
    }

    if (memBytes > MEM_SIZE) {
        free(buf);
    }

    return bytes_read;
}

int main(void) {
    int fd;
    struct iovec iov[5];
    char str1[BUF_SIZE];
    char str2[BUF_SIZE];
    char str3[BUF_SIZE];
    char str4[BUF_SIZE];
    char str5[BUF_SIZE];        
    ssize_t numRead;

    iov[0].iov_base = &str1;
    iov[0].iov_len = BUF_SIZE;

    iov[1].iov_base = &str2;
    iov[1].iov_len = BUF_SIZE;

    iov[2].iov_base = &str3;
    iov[2].iov_len = BUF_SIZE;

    iov[3].iov_base = &str4;
    iov[3].iov_len = BUF_SIZE;

    iov[4].iov_base = &str5;
    iov[4].iov_len = BUF_SIZE;

    fd = open("test.txt", O_RDWR | O_APPEND);

    numRead = readv_imp(fd, iov, 5);
    printf("Bytes read: %ld\n", numRead);

    if (close(fd) == -1) {
        errExit("close");
    }

    exit(EXIT_SUCCESS);
}