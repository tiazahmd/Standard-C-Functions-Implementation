int *intcpyimp(int *dst, int *src, const int number_of_items) {
    int i = 0;
    while (i < number_of_items) {
        *dst++ = *src++;
        i++;
    }
    return dst;
}