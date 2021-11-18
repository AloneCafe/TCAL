#include "utils.h"

inline void tcal_bcopy4rev(void *dest, const void *src, size_t len) {
    char *d = dest + len - 1;
    const char *s = src;
    while (len--)
        *d-- = *s++;
}

inline void tcal_brev(void *p, size_t len) {
    char *d = p + len - 1;
    char *s = p;
    size_t half = len / 2;
    while (half--) {
        char c = *(char *)s;
        *(char *)s++ = *(char *)d;
        *(char *)d-- = c;
    }
}

inline void tcal_bcopy(void *dest, const void *src, size_t len) {
    while (len--)
        *(char *)dest++ = *(char *)src++;
}

inline void tcal_bcopy4insert(void *dest, const void *src, size_t len) {
    char *d = (char *)dest + len - 1;
    const char *s = src + len - 1;
    while (len--)
        *d-- = *s--;
}

inline void tcal_bcopy4remove(void *dest, const void *src, size_t len) {
    while (len--)
        *(char *)dest++ = *(char *)src++;
}

inline void tcal_bzero(void *p, size_t len) {
    while (len--)
        *(char *)p++ = 0;
}
