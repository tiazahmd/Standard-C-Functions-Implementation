/* This program copies the content of the first
file provided in the command line argument to the
second file provided in the command line argument
using I/O system calls.
It's execution is as follows: `./cp oldFile newFile` */

#include <sys/stat.h>
#include <fcntl.h>
#include "tlpi_hdr.h"

#define BUF_SIZE 1024

int main(int argc, char *argv[]) {
    int inputFd, outputFd, openFlags;
    mode_t filePerms;
    ssize_t numRead;
    char buf[BUF_SIZE];

    if (argc != 3 || (strcmp(argv[1], "--help") == 0)) {
        usageErr("%s old-file new-file\n", argv[0]);
    }

    // Open Input and Output files
    inputFd = open(argv[1], O_RDWR);
    if (inputFd == -1) {
        errExit("opening file %s", argv[1]);
    }

    openFlags = O_CREAT | O_WRONLY | O_TRUNC;
    filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | 
                S_IROTH | S_IWOTH ;         // rw-rw-rw
    outputFd = open(argv[2], openFlags, filePerms);
    if (outputFd == -1) {
        errExit("opening file %s", argv[2]);
    }

    // Transfer data until we encounter an error
    while ((numRead = read(inputFd, buf, BUF_SIZE)) > 0) {
        if (write(outputFd, buf, numRead) != numRead) {
            fatal("couldn't write the whole buffer");
        }
    }
    
    if (numRead == -1) {
        errExit("read");
    }

    if (close(inputFd) == -1) {
        errExit("close input");
    }

    if (close(outputFd) == -1) {
        errExit("close output");
    }

    exit(EXIT_SUCCESS);
}