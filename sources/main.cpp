// main.cpp -- файл для тестирования собственных функций строк

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "str.h"

int main() { // TODO split to unit test (use google test if you will have enough times)
  char str[] = "dfsdfsdfsdfs";
  char str2[] = "eqweqweqweqweqwew";
  char str3[] = "erewrererewrewrerwer";
  char str4[] = "vxcvxcvxccvbxvcbvvzxv";
  char str5[] = "kjlkjlkjlkjlkjljlkjjlj";
  char str6[150] = "";
  char str7[] = "fdgsdfhgdfhgfsg";
  char str8[] = "hgfs";
  myPuts(str);
  puts(str);
  printf("%p %p\n", myStrchr(str, 's'), strchr(str, 's'));
  printf("%zu %zu\n", myStrlen(str), strlen(str));
  myPuts(myStrcpy(str2, str));
  myPuts(strcpy(str3, str));
  myPuts(myStrncpy(str4, str, 5));
  myPuts(strncpy(str5, str, 5));
  myPuts(myStrcat(str6, str4));
  myPuts(strcat(str6, str));
  myPuts(myStrncat(str6, str4, 10));
  myPuts(strncat(str6, str4, 10));
  myPuts(myFgets(str, 5, stdin));
  myPuts(fgets(str, 5, stdin));
  char * ds1 = myStrdup(str);
  char * ds2 = strdup(str);
  myPuts(ds1);
  myPuts(ds2);
  free(ds1);
  free(ds2);
  char * line1 = NULL;
  char * line2 = NULL;
  size_t s1 = 0, s2 = 0;
  size_t n1 = myGetline(&line1, &s1, stdin);
  size_t n2 = getline(&line2, &s2, stdin); // TODO use ssize_t
  myPuts(line1);
  myPuts(line2);
  printf("%zu %zu\n", n1, n2);
  free(line1);
  free(line2);
  printf("%p %p %p %p\n", strstr(str7, str8), myStrstr(str7, str8), myStrstrRK(str7, str8), myStrstrBMH(str7, str8));
  return 0;
}
