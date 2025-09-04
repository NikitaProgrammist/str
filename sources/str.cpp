// str.cpp -- собственные функции для строк

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "str.h"

int myPuts(const char * s) { // TODO rename s, i
  if (s == NULL) {
    return EOF;
  }

  size_t i = 0;
  while (s[i] != '\0') {
    putchar(s[i]); // TODO i++ here
    i++; // TODO remove
  }
  putchar('\n');
  return 0;
}

// TODO const char *
char * myStrchr(const char * s, const int c) { // TODO rename s, c, i
  size_t i = 0;
  while (s[i] != '\0') {
    if (c == s[i]) {
      return &s[i]; // TODO explicit cast to char *, &s[i] ----> s + i
    }
    i++;
  }
  return NULL;
}

size_t myStrlen(const char * s) {
  size_t i = 0;
  while (s[i] != '\0') { // TODO: *(s + i++), ++i
    i++;
  }
  return i;
}

char * myStrcpy(char * dest, const char * src) { // TODO rename i
  size_t i = 0;
  while ((dest[i] = src[i]) != '\0') {
    i++;
  }
  return dest;
}

char * myStrncpy(char * dest, const char * src, size_t n) {
  size_t i = 0;

  while (i < n && (dest[i] = src[i]) != '\0') {
    i++;
  }

  while (i < n) {
    dest[i] = '\0';
    i++;
  }

  return dest;
}

char * myStrcat(char * dest, const char * src) {
  size_t i = 0, j = 0;

  while (dest[i] != '\0') {
    i++;
  }

  while ((dest[i] = src[j]) != '\0') {
    i++;
    j++;
  }

  return dest;
}

char * myStrncat(char * dest, const char * src, size_t n) {
  size_t i = 0, j = 0;

  while (dest[i] != '\0') {
    i++;
  }

  while (j < n && (dest[i] = src[j]) != '\0') {
    i++;
    j++;
  }

  if (j == n) {
    dest[i] = '\0';
  }

  return dest;
}

char * myFgets(char * s, int size, FILE * stream) {
  int i = 0;

  while (i < size - 1) {
    s[i] = (char) getc(stream);
    if (s[i] == '\n' || s[i] == EOF) {
      i++;
      break;
    }
    i++;
  }
  s[i] = '\0';

  return s;
}

char * myStrdup(const char * s) {
  char * ds = (char *) malloc((myStrlen(s) + 1) * sizeof(char));

  if (ds != NULL) {
    myStrcpy(ds, s);
  }

  return ds;
}

size_t myGetline(char ** lineptr, size_t * n, FILE * stream) {
  if (*lineptr == NULL) {
    *lineptr = (char *) malloc(*n * sizeof(char));
  }

  size_t i = 0;
  char c = 0;

  while (i < *n && (c = (char) getc(stream)) != '\n' && c != EOF) {
    (*lineptr)[i] = c;
    i++;
  }

  if (i == *n) {
    while ((c = (char) getc(stream)) != '\n' && c != EOF) {
      *n += 1;
      *lineptr = (char *) realloc(*lineptr, *n * sizeof(char));
      (*lineptr)[i] = c;
      i++;
    }
  }

  if (i < *n - 1) {
    (*lineptr)[i++] = '\n';
    (*lineptr)[i] = '\0';
  }
  else {
    *n += 2;
    *lineptr = (char *) realloc(*lineptr, *n * sizeof(char));
    (*lineptr)[i++] = '\n';
    (*lineptr)[i] = '\0';
  }

  return *n - 1;
}

char * myStrstr(char * const haystack, char * const needle) {
  if (needle == NULL) {
    return haystack;
  }

  size_t i = 0;

  while (haystack[i] != '\0') {
    size_t j = 0;

    while (haystack[i + j] != '\0' && needle[j] != '\0' && haystack[i + j] == needle[j]) {
      j++;
    }

    if (needle[j] == '\0') {
      return haystack + i;
    }

    i++;
  }

  return NULL;
}

char * myStrstrRK(char * const haystack, char * const needle) {
  if (needle == NULL) {
    return haystack;
  }

  long long q = 1 << 31;
  q--;

  size_t m = myStrlen(needle);
  long long x = random(256);
  long long k = myPow(x, q, m - 1);
  long long hash_haystack = strHash(haystack, x, q, m);
  long long hash_needle = strHash(needle, x, q, m);

  size_t i = 0;
  while (haystack[i + m] != '\0') {
    if (hash_haystack == hash_needle) {

      size_t j = 0;
      while (j < m) {
        if (haystack[i + j] != needle[j]) {
          break;
        }
        j++;
      }

      if (needle[j] == '\0') {
        return haystack + i;
      }
    }
    i++;
    hash_haystack = ((hash_haystack - (haystack[i - 1] * k) % q) * x + haystack[i + m - 1]) % q;
  }

  return NULL;
}

char * myStrstrBMH(char * const haystack, char * const needle) {
  if (needle == NULL) {
    return haystack;
  }

  size_t m = myStrlen(needle);
  const int LEN_ALPHABET = 256;
  size_t symbols[LEN_ALPHABET] = {};

  for (size_t i = 0; i < LEN_ALPHABET; i++) {
    symbols[i] = m;
  }

  for (size_t i = 0; i < m - 1; i++) {
    if (symbols[(size_t) needle[i]] == m) {
      symbols[(size_t) needle[i]] = m - i - 1;
    }
  }

  size_t i = 0;

  while (haystack[i + m - 1] != '\0') {
    size_t j = m;

    while (j > 0 && haystack[i + j - 1] == needle[j - 1]) {
      j--;
    }

    if (j == 0) {
      return haystack + i;
    }

    i += symbols[(size_t) haystack[i + j - 1]];
  }

  return NULL;
}

long long random(long long q) { // TODO rename q
  srand(time(NULL)); // TODO add explicit cast, abs() or %
  return rand() % (q - 2) + 2;
}

long long myPow(long long x, long long q, size_t m) {
  long long r = 1;
  for (size_t i = 0; i < m; i++) {
    r = (r * x) % q;
  }
  return r;
}

long long strHash(char * const str, long long x, long long q, size_t len) {
  size_t i = 0;
  long long hash = 0;
  while (i < len - 1) {
    hash += str[i] * myPow(x, q, len - i - 1);
    i++;
  }
  hash = (hash + str[i]) % q;
  return hash;
}
