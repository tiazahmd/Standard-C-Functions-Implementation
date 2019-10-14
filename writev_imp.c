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

So the operation of `writev()` is going to be slightly different. At first, it
will create a big buffer, the size of the struct that has been passed to. It will
read (gather) all the data into that big buffer and then `write()` that big buffer.
This will ensure atomocity in the `write()` operation.

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

ssize_t writev_imp(int fd, const struct iovec *iov, int iovcnt) {
    ssize_t bytes = 0;
    ssize_t memBytes = 0;

    for (int i = 0; i < iovcnt; i++) {
        if (SSIZE_MAX - bytes < iov[i].iov_len) {
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

    char *buffer = buf;

    ssize_t copy = 0;
    ssize_t to_copy = bytes;
    ssize_t bytes_written = 0;

    for (int i = 0; i < iovcnt; i++) {
        copy = min (iov[i].iov_len, to_copy);

        memcpy(buffer, iov[i].iov_base, copy);

        buffer += copy;
        to_copy -= copy;
        if (to_copy == 0) {
            break;
        }
    }

    bytes_written = write(fd, buf, bytes);

    if (memBytes > MEM_SIZE) {
        free(buf);
    }

    return bytes_written;
}

int main(void) {
    int fd;
    struct iovec iov[5];
    char str1[BUF_SIZE];
    char str2[BUF_SIZE];
    char str3[BUF_SIZE];
    char str4[BUF_SIZE];
    char str5[BUF_SIZE];        
    ssize_t numRead, numWrote;

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

    while (numRead = readv(fd, iov, 5) > 0) {
        numWrote = writev_imp(2, iov, 5);
    }

    printf("\nBytes wrote: %ld\n", numWrote);
}