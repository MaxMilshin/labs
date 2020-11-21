#include <stdio.h>
#include <stdbool.h>
#include <assert.h> 
#include "str.h"

bool are_they_equal(char *s1, char *s2) {
  while (*s1 != '\0' && *s1 == *s1) {
    s1++;
    s2++;
  }
  return (*s1 == *s2);
}

void print_message(char *function_name) {
  printf("Test for function %s is succesfully passed!\n", function_name);  
}


void test_strcpy() {
  char s1[10];
  char* s2 = "Hello";
  char* expected_ans = "Hello";
  char* actual_ans = my_strcpy(s1, s2);
  assert(are_they_equal(expected_ans, actual_ans));
  print_message("my_strcpy"); 
} 

void test_strcat() {
  char s1[10] = {'H', 'e', 'l', 'l', 'o', '\0'};
  char* s2 = "Max";
  char* expected_ans = "HelloMax";
  char* actual_ans = my_strcat(s1, s2);
  assert(are_they_equal(expected_ans, actual_ans));
  print_message("my_strcat");
}

void test_strcmp() {
  char* s1 = "car";
  char* s2 = "cake";
  int expected_ans = 7;
  int actual_ans = my_strcmp(s1, s2);
  assert(expected_ans == actual_ans);
  print_message("my_strcmp");
}

void test_strlen() {
  char* s = "abacaba";
  int expected_ans = 7;
  int actual_ans = my_strlen(s);
  assert(expected_ans == actual_ans);
  print_message("my_strlen");
}

