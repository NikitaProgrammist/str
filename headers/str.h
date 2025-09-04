// str.h -- заголовочный файл для str.cpp

#ifndef STR_H
#define STR_H

int myPuts(const char * s);
char * myStrchr(char * const s, const int c);
size_t myStrlen(const char * s);
char * myStrcpy(char * dest, const char * src);
char * myStrncpy(char * dest, const char * src, size_t n);
char * myStrcat(char * dest, const char * src);
char * myStrncat(char * dest, const char * src, size_t n);
char * myFgets(char * s, int size, FILE * stream);
char * myStrdup(const char * s);
size_t myGetline(char ** lineptr, size_t * n, FILE * stream);
char * myStrstr(char * const haystack, char * const needle);
char * myStrstrRK(char * const haystack, char * const needle);
char * myStrstrBMH(char * const haystack, char * const needle);
long long random(long long q);
long long myPow(long long x, long long q, size_t m);
long long strHash(char * const str, long long x, long long q, size_t len);

#endif
