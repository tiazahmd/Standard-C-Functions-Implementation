char *strcatimp (char *dst, char *src) {
    int len = 0;
    while (dst[len] != '\0') {
        len++;
    }
    
    while (*src) {
        *(dst + len++) = *src++;
    }
    *(dst + len) = '\0';
    return dst;
}