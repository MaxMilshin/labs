#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

void mergesort(void* arr, int count, size_t elem_sz, int (*cmp)(const void *, const void *)) {
	if (count <= 1)
		return;
	int left_count = count / 2, right_count = count - count / 2;
	char* char_arr = (char *) arr;
	char* right_arr = char_arr + left_count * elem_sz;
	mergesort(arr, left_count, elem_sz, cmp);
    mergesort(right_arr, count - left_count, elem_sz, cmp);
	char* brr = (char *) malloc(count * elem_sz);
	assert (brr != NULL);
	int i = 0, j = 0;
	while (i < left_count && j < right_count) {
		if (cmp(&char_arr[i * elem_sz], &right_arr[j * elem_sz]) < 0) {
			memcpy(&brr[(i + j) * elem_sz], &char_arr[i * elem_sz], elem_sz);
			i++;
		} 
		else {
			memcpy(&brr[(i + j) * elem_sz], &right_arr[j * elem_sz], elem_sz);
			j++;
		}
	}
	while (i < left_count) {
		memcpy(&brr[(i + j) * elem_sz], &char_arr[i * elem_sz], elem_sz);
		i++;
	}
	while (j < right_count) {
		memcpy(&brr[(i + j) * elem_sz], &right_arr[j * elem_sz], elem_sz);
		j++;
	}
	memcpy(char_arr, brr, count * elem_sz);
	free(brr);
	return;
}
