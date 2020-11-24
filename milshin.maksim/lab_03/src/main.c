#include <stdio.h>
#include <stdlib.h>
#include "mergesort.h"

int to_int(char* str) {
	int sign = 1;
	if (*str == '-') {
		str++;
		sign = -1;
	}
	int ans = 0;
	while (*str != '\0') {
		ans = ans * 10 + *str - '0';
		str++;
	}
	return ans * sign;
}

int cmp_int(const void* x, const void* y) {
	int numb1 = *((int *) x);
	int numb2 = *((int *) y);
	if (numb1 > numb2)
		return 1;
	if (numb1 < numb2)
		return -1;
	return 0;
}

int cmp_char(const void* x, const void* y) {
	return *((char *) x) - *((char *) y);
}

int cmp_str(const void* x, const void* y) {
  char* s1 = *((char **) x);
  char* s2 = *((char **) y);
  while (*s1 != '\0' && *s1 == *s2) {
    s1++;
    s2++;
  }
  return *s1 - *s2;
}

int main(int argc, char** argv){
	int n = argc - 2;
	if (argv[1][0] == 'i') {
		int a[n];
		for (int i = 0; i < n; i++) {
			a[i] = to_int(argv[i + 2]);
		}
		mergesort(a, n, sizeof(a[0]), cmp_int);
		for (int i = 0; i < n; i++) 
			printf("%d ", a[i]);
	}
	if (argv[1][0] == 'c') {
		char a[n];
		for (int i = 0; i < n; i++) {
			a[i] = *argv[i + 2];
		}
		mergesort(a, n, sizeof(a[0]), cmp_char);
		for (int i = 0; i < n; i++) 
			printf("%c ", a[i]);

	}
	if (argv[1][0] == 's') {
		char * a[n];
		for (int i = 0; i < n; i++) 
			a[i] = &(argv[i + 2][0]);
		mergesort(a, n, sizeof(a[0]), cmp_str);
		for (int i = 0; i < n; i++) 
			printf("%s ", a[i]);
	}
}
