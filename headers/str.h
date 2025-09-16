// str.h -- заголовочный файл для str.cpp

#ifndef STR_H
#define STR_H

int myPuts(const char * string);
char * myStrchr(const char * string, const int symbol);
int myAtoi(char * string);
size_t myStrlen(const char * string);
char * myStrcpy(char * dest, const char * src);
char * myStrncpy(char * dest, const char * src, size_t n);
char * myStrcat(char * dest, const char * src);
char * myStrncat(char * dest, const char * src, size_t n);
char * myFgets(char * string, int size, FILE * stream);
char * myStrdup(const char * string);
size_t myGetline(char ** lineptr, size_t * n, FILE * stream);
char * myStrstr(const char * haystack, char * const needle);
char * myStrstrRK(const char * haystack, char * const needle);
char * myStrstrBMH(const char * haystack, char * const needle);
long long random(long long prime);
long long myPow(long long randomnum, long long prime, size_t len_substring);
long long strHash(const char * str, long long randomnum, long long prime, size_t len);
char * myStrtok(char * __restrict str, const char * __restrict delim);

#endif // STR_H
