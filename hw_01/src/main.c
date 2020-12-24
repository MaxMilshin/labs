#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include "bmp.h"


bool arguments_check(int x, int y, int w, int h, int width, int height) {
	return (0 <= x && x < x + w && x + w <= width && 0 <= y && y < y + h && y + h <= height);
}

int main(int argc, char** argv) {
    unsigned char info[54];
    RGBQUAD **rgb = load_bmp(info, argv[2]);
    int width = *(int*)&info[18], height = *(int*)&info[22], n = max(width, height);
    
    int x = atoi(argv[4]), y = atoi(argv[5]), w = atoi(argv[6]), h = atoi(argv[7]);
    if (!arguments_check(x, y, w, h, width, height)) {
        release_memory(&rgb, n);
        printf("illegal arguments\n");
        return 1;
    }
    
    crop(info, &rgb, x, y, w, h);
    rotate(info, &rgb);
    save_bmp(info, &rgb, argv[3]);
    release_memory(&rgb, n);
    return 0;
}
