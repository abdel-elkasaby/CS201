#include <unistd.h>

size_t vstrlen(const char *);
char *vstrcpy(char *, const char *);
char *vstrcat(char *, const char *);

size_t vstrlen (const char *s) {
    size_t len = 0;

#ifdef ARRAY
    for (; s[len] != '\0'; len++);
    // while (s[len] != '\0') {
    //     len++;
    // }
#else //ARRAY
    //for (; *s != '\0'; len++, s++);
    while (*s != '\0') {
        len++;
        s++;
    }
#endif //ARRAY
    return len;

}

char *vstrcpy(char *dest, const char *src) {

#ifdef ARRAY
    int idx = 0;

    for(; src[idx] != '\0'; dest[idx] = src[idx], idx++);
    // while (src[idx] != '\0') {
    //     dest[idx] = src[idx];
    //     idx++;
    // }
    dest[idx] = '\0';
#else // ARRAY
    char *ptr = dest;
    while(*src != '\0') {
        *ptr++ = *src++;

    }
    *ptr = '\0';
#endif

    return dest;
}

char *vstrcat(char *dest, const char *src) {

#ifdef REUSE
    return vstrcpy(dest + vstrlen(dest), src), dest;
#else //!REUSE
# ifdef ARRAY
    size_t didx = vstrlen(dest);
    int sidx = 0;

    for(; src[sidx] != '\0'; dest[didx++] = src[sidx++]);
    dest[didx] = '\0';
# else //ARRAY
    char *ptr = dest + vstrlen(dest);

    for(; *src != '\0'; *ptr++ = *src++);
    *ptr = '\0';
# endif //ARRAY

    return dest;
#endif //REUSE
}