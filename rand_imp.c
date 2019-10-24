#include <stdio.h>
#include <time.h>

int rand_imp(void) {
    static unsigned int next = 1;
    next = time(0) % 100;
    next = next * 1103515245 + 12345;
    return (unsigned int) (next / 65536) % 32768;
}