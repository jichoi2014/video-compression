#include "buffer.h"
void clipping(double* blockArray)
{
	for (int i = 0; i < 64; i++)//clipping

	{
		if (blockArray[i] > 255)
		{
			blockArray[i] = 255;
		}
		if (blockArray[i] < 0)
		{
			blockArray[i] = 0;
		}
	}
}

void cbcr_clipping(double* blockArray)
{
	for (int i = 0; i < 16; i++)//clipping

	{
		if (blockArray[i] > 255)
		{
			blockArray[i] = 255;
		}
		if (blockArray[i] < 0)
		{
			blockArray[i] = 0;
		}
	}
}