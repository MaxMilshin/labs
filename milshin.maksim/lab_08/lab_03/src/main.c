#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "mergesort.h"

const char* INT_TYPE = "int";
const char* CHAR_TYPE = "char";
const char* STR_TYPE = "str";

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
	if (strcmp(argv[1], INT_TYPE) == 0) {
		int* a = (int*) malloc(n * sizeof(int));
		assert (a != NULL);
		for (int i = 0; i < n; i++) {
			a[i] = atoi(argv[i + 2]);
		}
		mergesort(a, n, sizeof(a[0]), cmp_int);
		for (int i = 0; i < n - 1; i++) 
			printf("%d ", a[i]);
		printf("%d", a[n - 1]);
		free(a);
	}
	if (strcmp(argv[1], CHAR_TYPE) == 0) {
		char* a = (char*) malloc(n * sizeof(char));
		assert (a != NULL);
		for (int i = 0; i < n; i++) {
			a[i] = *argv[i + 2];
		}
		mergesort(a, n, sizeof(a[0]), cmp_char);
		for (int i = 0; i < n - 1; i++) 
			printf("%c ", a[i]);
		printf("%c", a[n - 1]);
		free(a);

	}
	if (strcmp(argv[1], STR_TYPE) == 0) {
		char** a = (char**) malloc(n * sizeof(char*));
		assert (a != NULL);
		for (int i = 0; i < n; i++) 
			a[i] = &(argv[i + 2][0]);
		mergesort(a, n, sizeof(a[0]), cmp_str);
		for (int i = 0; i < n - 1; i++) 
			printf("%s ", a[i]);
		printf("%s", a[n - 1]);
		free(a);
	}
}
