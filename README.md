## Implementation of Standard C Library Fucntions
This is my take on implementing some standard C Library functions. So far, my implementations include the following functions:
- `strcat()`
- `strlen()`
- `strcpy()`
- `intcpy()` (This is my own function - integer copy. Using the same principles of `strcpy()`.)
- `tee()`

**Error Functions & Lib**: These two are helper library and outputs to compile codes. They are not necessary for all the implementations, but is necessary if a header or output file seems to be missing. Compile using the following: `gcc -I ../lib error_functions.o tee_imp.c -o tee-imp`.