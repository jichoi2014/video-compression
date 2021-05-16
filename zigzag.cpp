#include "buffer.h"
void zig_zag_array(int* Zigzag_array,int zWIDTH,int zHEIGHT)
{
    int d = 1;
    int num = 0;
    int x = 0, y = 0;
    while (true) {
        Zigzag_array[y * zWIDTH + x] = num++;
        if ((x == (zWIDTH - 1)) && (y == (zHEIGHT - 1))) break;
        if (d == 1) {
            x++;
            y--;
            if (x >= zWIDTH) {
                x = zWIDTH - 1;
                y += 2;
                d = 0;
            }
            else if (y < 0) {
                y = 0;
                d = 0;
            }
        }
        else {
            x--;
            y++;
            if (y >= zHEIGHT) {
                x += 2;
                y = zHEIGHT - 1;
                d = 1;
            }
            else if (x < 0) {
                x = 0;
                d = 1;
            }
        }

    }
}

void zig_zag_scan(double* blockarray, int* Zigzag_array)
{
    double Zigzag_buffer_array2[NR] = { 0, };
    
    for (int z=0;z < N;z++)
    {
        for (int c = 0;c < N;c++)
        {
            Zigzag_buffer_array2[Zigzag_array[z * N + c]] = blockarray[z * N + c];
        }
    }
  
    for (int z = 0;z < N;z++)
    {
        for (int c = 0;c < N;c++)
        {
            blockarray[N * z + c] = Zigzag_buffer_array2[N * z + c];
        }
    }
}

void izig_zag_scan(double* blockarray, int* Zigzag_array)
{
    double Zigzag_buffer_array3[64] = { 0, };
    for (int z = 0;z < N;z++)
    {
        for (int c = 0;c < N;c++)
        {
            Zigzag_buffer_array3[N * z + c] = blockarray[N * z + c];
        }
    }

    for (int z = 0;z < N;z++)
    {
        for (int c = 0;c < N;c++)
        {
            blockarray[z * N + c] = Zigzag_buffer_array3[Zigzag_array[z * N + c]];
        }
    }
}

void CBCR_zig_zag_scan(double* CBCRblockarray, int* CBCR_Zigzag_array)
{
    double Zigzag_buffer_array2[16] = { 0, };

    for (int z = 0;z < CBCRBLOCK_H;z++)
    {
        for (int c = 0;c < CBCRBLOCK_W;c++)
        {
            Zigzag_buffer_array2[CBCR_Zigzag_array[z * CBCRBLOCK_W + c]] = CBCRblockarray[z * CBCRBLOCK_W + c];
        }
    }

    for (int z = 0;z < CBCRBLOCK_H;z++)
    {
        for (int c = 0;c < CBCRBLOCK_W;c++)
        {
            CBCRblockarray[CBCRBLOCK_W * z + c] = Zigzag_buffer_array2[CBCRBLOCK_W * z + c];
        }
    }
}

void CBCR_izig_zag_scan(double* CBCRblockarray, int* CBCR_Zigzag_array)
{
    double Zigzag_buffer_array3[16] = { 0, };

    for (int z = 0;z < CBCRBLOCK_H;z++)
    {
        for (int c = 0;c < CBCRBLOCK_W;c++)
        {
            Zigzag_buffer_array3[CBCRBLOCK_W * z + c] = CBCRblockarray[CBCRBLOCK_W * z + c];
        }
    }

    for (int z = 0;z < CBCRBLOCK_H;z++)
    {
        for (int c = 0;c < CBCRBLOCK_W;c++)
        {
            CBCRblockarray[z * CBCRBLOCK_H + c] = Zigzag_buffer_array3[CBCR_Zigzag_array[z * CBCRBLOCK_H + c]];
        }
    }
}

