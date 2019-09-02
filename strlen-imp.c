/*** strlen implementation ***/
int strlenimp(char *word) {
    int count = 0;
    while (word[count] != '\0') {
        count++;
    }
    return count;
}