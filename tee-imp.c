#include <ctype.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "tlpi_hdr.h"

extern int optind, optopt;
extern char *optarg;

#define printable(ch) (isprint((unsigned char) ch) ? ch : '#')
#define BUF_SIZE 1024

static void usageError(char *progname, char *msg, int opt) {
    if (msg != NULL && opt != 0) {
        fprintf(stderr, "%s (-%c)\n", msg, printable(opt));
    }
    fprintf(stderr, "Usage: %s [-p arg] [-x]\n", progname);
    exit(EXIT_FAILURE);
}

int main (int argc, char *argv[]) {
    int outputFD, opt, openFlags;
    mode_t filePerms;
    ssize_t numRead;
    char buf[BUF_SIZE];
    char *pstr;

    // Set file permission up to rw-rw-rw
    filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | 
                S_IROTH | S_IWOTH ;         // rw-rw-rw

    // If user provides an option
    while ((opt = getopt(argc, argv, ":a:")) != -1) {
        switch(opt) {
            default : fatal("Unexpected case in switch()");
            case ':': usageError(argv[0], "Missing argumnent", optopt);
            case '?': usageError(argv[0], "Unrecognized option", optopt);           
            case 'a':
                openFlags = O_CREAT | O_WRONLY | O_APPEND;
                while ((numRead = read(STDIN_FILENO, buf, BUF_SIZE)) > 0) {
                    if (write(STDOUT_FILENO, buf, numRead) != numRead) {
                        fatal("Couldn't write the whole buffer");
                    }
                    if (argc > 1) {
                        for (int i = 2; i < argc; i++) {
                            outputFD = open(argv[i], openFlags, filePerms);
                            if (write(outputFD, buf, numRead) != numRead) {
                                fatal("Couldn't write the whole buffer");
                            }
                        }
                    }
                }
        }
        
        if (numRead == -1) {
            errExit("read");
        }

        if (close(outputFD) == -1) {
            errExit("close output");
        }
        exit(EXIT_SUCCESS);
    }

    // No option flags
    openFlags = O_CREAT | O_WRONLY | O_TRUNC;

    while (1) {
        while ((numRead = read(STDIN_FILENO, buf, BUF_SIZE)) > 0) {
            if (write(STDOUT_FILENO, buf, numRead) != numRead) {
                fatal("Couldn't write the whole buffer");
            }
            if (argc > 1) {
                for (int i = 1; i < argc; i++) {
                    outputFD = open(argv[i], openFlags, filePerms);
                    if (write(outputFD, buf, numRead) != numRead) {
                        fatal("Couldn't write the whole buffer");
                    }
                }
                openFlags = O_CREAT | O_WRONLY | O_APPEND;
            }
        }
    }

    if (numRead == -1) {
        errExit("read");
    }

    if (close(outputFD) == -1) {
        errExit("close output");
    }

    exit(EXIT_SUCCESS);
}