#include <stdio.h>

char* my_strcpy(char* dest, const char* src) {
  char* cp_dest = dest;
  while (*src != '\0') {
    *cp_dest = *src;
    cp_dest++;
    src++; 
  }
  *cp_dest = '\0';
  return dest;
}

char* my_strcat(char* dest, const char* src) {
  char* cp_dest = dest;
  while (*cp_dest != '\0')
    cp_dest++;
  while (*src != '\0') {
    *cp_dest = *src;
    cp_dest++;
    src++;
  }
  *cp_dest = '\0';
  return dest;
}

int my_strcmp(const char* s1, const char* s2) {
  while (*s1 != '\0' && *s1 == *s2) {
    s1++;
    s2++;
  }
  return *s1 - *s2;
}

int my_strlen(char* s) {
  char* cp_s = s;
  while (*cp_s != '\0') 
    cp_s++;
  return cp_s - s;
}


