#ifndef TLPI_HDR_H
#define TLPI_HDR_H                  // Prevent accidental double inclusion of header

#include <sys/types.h>              // Type definitions used by many programs
#include <stdio.h>                  // Standard I/O functions
#include <stdlib.h>                 // Prototypes of commonly used library functions
#include <unistd.h>                 // Prototypes for many system calls
#include <errno.h>                  // Declares errno and defines error constants
#include <string.h>                 // Commonly used string handle functions

#include "get_num.h"                // Declares our functions for handling numeric arguments
                                    // such as getInt(), getLong()
#include "error_functions.h"        // Declares our error handling functions.

typedef enum { FALSE, TRUE } Boolean;

#define min(m,n) ((m) < (n) ? (m) : (n))        // if m < n, return m
#define max(m,n) ((m) > (n) ? (m) : (n))        // uf m > n, return m

// (condition) ? expression_1 : expression_2
// if condition is true, execute expression_1, else execute expression_2

#endif