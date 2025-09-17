// str.cpp -- собственные функции для строк

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "str.h"

int myPuts(const char * string) {
  if (string == NULL) {
    return EOF;
  }

  size_t index = 0;
  while (string[index] != '\0') {
    putchar(string[index++]);
  }
  putchar('\n');
  return 0;
}

char * myStrchr(const char * string, const int symbol) {
  size_t index = 0;
  while (string[index] != '\0') {
    if (symbol == string[index]) {
      return (char *) (string + index);
    }
    index++;
  }
  return NULL;
}

int myAtoi(char * string) {
  size_t index = 0;
  int num = 0;
  int sign = 0;

  if (string[index] < '0' || string[index] > '9') {
    sign = (string[index++] == '-' ? -1 : 1);
  }

  while (string[index] != '\0' && string[index] >= '0' && string[index] <= '9') {
    num = 10 * num + string[index++] - '0';
  }

  return num * sign;
}

size_t myStrlen(const char * string) {
  size_t index = 0;
  while (string[index++] != '\0');
  return index - 1;
}

int myStrCmpStart(const char * str1, const char * str2) {
  size_t index1 = 0, index2 = 0;
  while (!isalpha(str1[index1++]));
  while (!isalpha(str2[index2++]));
  while (str1[index1] != '\0' && str2[index2] != '\0' && isalpha(str1[index1]) && isalpha(str2[index2])) {
    if (str1[index1] != str2[index2]) {
      return str1[index1] - str2[index2];
    }
    index1++;
    index2++;
  }
  return 0;
}

int myStrCmpEnd(const char * str1, const char * str2) {
  size_t index1 = 0, index2 = 0;
  while (str1[index1++] != '\0');
  while (str2[index2++] != '\0');
  while (!isalpha(str1[index1--]));
  while (!isalpha(str2[index2--]));
  while (index1 != 0 && index2 != 0) {
    if (str1[index1] != str2[index2]) {
      return str1[index1] - str2[index2];
    }
    index1++;
    index2++;
  }
  return str1[0] - str2[0];
}

char * myStrcpy(char * dest, const char * src) {
  size_t index = 0;
  while ((dest[index] = src[index]) != '\0') {
    index++;
  }
  return dest;
}

char * myStrncpy(char * dest, const char * src, size_t n) {
  size_t index = 0;

  while (index < n && (dest[index] = src[index]) != '\0') {
    index++;
  }

  while (index < n) dest[index++] = '\0';

  return dest;
}

char * myStrcat(char * dest, const char * src) {
  size_t dest_index = 0, src_index = 0;

  while (dest[dest_index] != '\0') {
    dest_index++;
  }

  while ((dest[dest_index++] = src[src_index++]) != '\0');

  return dest;
}

char * myStrncat(char * dest, const char * src, size_t n) {
  size_t dest_index = 0, src_index = 0;

  while (dest[dest_index] != '\0') {
    dest_index++;
  }

  while (src_index < n && (dest[dest_index] = src[src_index]) != '\0') {
    dest_index++;
    src_index++;
  }

  if (src_index == n) {
    dest[dest_index] = '\0';
  }

  return dest;
}

char * myFgets(char * string, int size, FILE * stream) {
  int index = 0;
  char symbol = '\0';

  while (index < size - 1 && (symbol = (char) getc(stream)) != EOF) {
    string[index] = symbol;
    if (string[index++] == '\n') {
      break;
    }
  }
  string[index] = '\0';

  return string;
}

char * myStrdup(const char * string) {
  char * dstring = (char *) malloc((myStrlen(string) + 1) * sizeof(char));

  if (dstring != NULL) {
    myStrcpy(dstring, string);
  }

  return dstring;
}

size_t myGetline(char ** lineptr, size_t * n, FILE * stream) {
  if (*lineptr == NULL) {
    *lineptr = (char *) malloc(*n * sizeof(char));
  }

  size_t index = 0;
  char symbol = 0;

  while (index < *n && (symbol = (char) getc(stream)) != '\n' && symbol != EOF) {
    (*lineptr)[index] = symbol;
    index++;
  }

  if (index == *n) {
    while ((symbol = (char) getc(stream)) != '\n' && symbol != EOF) {
      *n += 1;
      *lineptr = (char *) realloc(*lineptr, *n * sizeof(char));
      (*lineptr)[index++] = symbol;
    }
  }

  if (index < *n - 1) {
    (*lineptr)[index++] = '\n';
    (*lineptr)[index] = '\0';
  }
  else {
    *n += 2;
    *lineptr = (char *) realloc(*lineptr, *n * sizeof(char));
    (*lineptr)[index++] = '\n';
    (*lineptr)[index] = '\0';
  }

  return *n - 1;
}

char * myStrstr(const char * haystack, char * const needle) {
  if (needle == NULL) {
    return (char *) haystack;
  }

  size_t index = 0;

  while (haystack[index] != '\0') {
    size_t subindex = 0;

    while (haystack[index + subindex] != '\0' && needle[subindex] != '\0' && haystack[index + subindex] == needle[subindex]) {
      subindex++;
    }

    if (needle[subindex] == '\0') {
      return (char *) (haystack + index);
    }

    index++;
  }

  return NULL;
}

char * myStrstrRK(const char * haystack, char * const needle) {
  if (needle == NULL) {
    return (char *) haystack;
  }

  long long prime = 1 << 31;
  prime--;

  size_t len_substring = myStrlen(needle);
  long long randomnum = random(256);
  long long coeff = myPow(randomnum, prime, len_substring - 1);
  long long hash_haystack = strHash(haystack, randomnum, prime, len_substring);
  long long hash_needle = strHash(needle, randomnum, prime, len_substring);

  size_t index = 0;
  while (haystack[index + len_substring] != '\0') {
    if (hash_haystack == hash_needle) {

      size_t subindex = 0;
      while (subindex < len_substring) {
        if (haystack[index + subindex] != needle[subindex]) {
          break;
        }
        subindex++;
      }

      if (needle[subindex] == '\0') {
        return (char *) (haystack + index);
      }
    }
    index++;
    hash_haystack = ((hash_haystack - (haystack[index - 1] * coeff) % prime) * randomnum + haystack[index + len_substring - 1]) % prime;
  }

  return NULL;
}

char * myStrstrBMH(const char * haystack, char * const needle) {
  if (needle == NULL) {
    return (char *) haystack;
  }

  size_t len_substring = myStrlen(needle);
  const int LEN_ALPHABET = 256;
  size_t symbols[LEN_ALPHABET] = {};

  for (size_t index = 0; index < LEN_ALPHABET; index++) {
    symbols[index] = len_substring;
  }

  for (size_t index = 0; index < len_substring - 1; index++) {
    if (symbols[(size_t) needle[index]] == len_substring) {
      symbols[(size_t) needle[index]] = len_substring - index - 1;
    }
  }

  size_t index = 0;

  while (haystack[index + len_substring - 1] != '\0') {
    size_t subindex = len_substring;

    while (subindex > 0 && haystack[index + subindex - 1] == needle[subindex - 1]) {
      subindex--;
    }

    if (subindex == 0) {
      return (char *) (haystack + index);
    }

    index += symbols[(size_t) haystack[index + subindex - 1]];
  }

  return NULL;
}

long long random(long long prime) {
  srand(0);
  return rand() % (prime - 2) + 2;
}

long long myPow(long long randomnum, long long prime, size_t len_substring) {
  long long result = 1;
  for (size_t index = 0; index < len_substring; index++) {
    result = (result * randomnum) % prime;
  }
  return result;
}

long long strHash(const char * str, long long randomnum, long long prime, size_t len) {
  size_t index = 0;
  long long hash = 0;
  while (index < len - 1) {
    hash += str[index] * myPow(randomnum, prime, len - index - 1);
    index++;
  }
  hash = (hash + str[index]) % prime;
  return hash;
}

char * myStrtok(char * __restrict str, const char * __restrict delim) {
  static char * string = nullptr;
  static size_t index = 0;

  if (str) {
    string = str;
    index = 0;
  }

  char * pointer = string + index;
  while (string[index] != '\0' && (myStrchr(delim, string[index]) == NULL)) {
    index++;
  }

  if (myStrchr(delim, string[index])) {
    while (myStrchr(delim, string[index])) {
      string[index++] = '\0';
    }
  }
  return pointer;
}
