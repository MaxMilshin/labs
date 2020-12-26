#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include "bmp.h"

int max(int a, int b) {
    if (a > b)
        return a;
    return b;
}

RGBQUAD ** load_bmp(unsigned char* info, char* file_name) {   
    FILE * f = fopen(file_name, "rb");
    assert(f);
    
    fread(info, sizeof(unsigned char), 54, f);
    
    int width = *(int*)&info[18];
    int height = *(int*)&info[22];
    int n = max(width, height);

    RGBQUAD **rgb = malloc(n * sizeof(RGBQUAD*));
    for (int i = 0; i < n; i++) 
        rgb[i] = malloc(n * sizeof(RGBQUAD));

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            rgb[height - i - 1][j].rgbBlue = getc(f);
            rgb[height - i - 1][j].rgbGreen = getc(f);
            rgb[height - i - 1][j].rgbRed = getc(f);
        }
        int rest = (4 - (3 * width) % 4) % 4;
        for (int i = 0; i < rest; i++)
          getc(f);
    }

    fclose(f);

    return rgb;
}
 
void crop(unsigned char* info, RGBQUAD ***rgb, int x, int y, int w, int h) {
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) 
            (*rgb)[i][j] = (*rgb)[i + y][j + x];
    }
    *(int*)&info[18] = w;
    *(int*)&info[22] = h; 
}

void rotate(unsigned char* info, RGBQUAD ***rgb) {
    int width = *(int*)&info[18];
    int height = *(int*)&info[22];
    int n = max(width, height);
    for (int i = 0; i < (n + 1) / 2; i++)
        for (int j = 0; j < n - 2 * i - 1; j++) {
            int x1 = i, y1 = j + i;
            int x2 = x1, y2 = n - 1 - i;
            if (j != 0) 
                x2 = y1;
            int x3 = n - x1 - 1, y3 = n - y1 - 1;
            int x4 = n - x2 - 1, y4 = n - y2 - 1;
            RGBQUAD tmp = (*rgb)[x4][y4];
            (*rgb)[x4][y4] = (*rgb)[x3][y3];
            (*rgb)[x3][y3] = (*rgb)[x2][y2];
            (*rgb)[x2][y2] = (*rgb)[x1][y1];
            (*rgb)[x1][y1] = tmp;
        }

    for (int i = 0; i < width; i++)
        for (int j = 0; j < height; j++)
            (*rgb)[i][j] = (*rgb)[i][j + n - height]; 

    // обновляем ширину и высоту изображения    
    *(int*)&info[18] = height;
    *(int*)&info[22] = width;        
}

void save_bmp(unsigned char* info, RGBQUAD ***rgb, char* file_name) {
    FILE* f = fopen(file_name, "wb");
    assert(f);

    int width = *(int*)&info[18];
    int height = *(int*)&info[22];
    
    // обновляем размер файла и изображения
    *(int*)&info[2] = height * (width * 3 + (4 - (width * 3) % 4) % 4) + 54;
    *(int*)&info[34] = *(int*)&info[2] - 54;
    
    fwrite(info, sizeof(unsigned char), 54, f);
    
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            fwrite(&((*rgb)[height - i - 1][j].rgbBlue), 1, 1, f);
            fwrite(&((*rgb)[height - i - 1][j].rgbGreen), 1, 1, f);
            fwrite(&((*rgb)[height - i - 1][j].rgbRed), 1, 1, f);
        }

        // выравнивание нулями
        int rest = (4 - (3 * width) % 4) % 4;
        for (int i = 0; i < rest; i++)
            putc(0, f);
    }

    fclose(f);
}

void release_memory(RGBQUAD ***rgb, int n) {
    for (int i = 0; i < n; i++)
        free((*rgb)[i]);
    free(*rgb);
}
