#pragma once

int max(int a, int b);

typedef struct
{
    int   rgbBlue;
    int   rgbGreen;
    int   rgbRed;
    int   rgbReserved;
} RGBQUAD;

RGBQUAD ** load_bmp(unsigned char* info, char* file_name);

void crop(unsigned char* info, RGBQUAD ***rgb, int x, int y, int w, int h);

void rotate(unsigned char* info, RGBQUAD ***rgb);

void save_bmp(unsigned char* info, RGBQUAD ***rgb, char* file_name);
