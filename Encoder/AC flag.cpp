#include "buffer.h"

int AC_FLAG(double* blockArray)
{
	int AC_Flag = 0;
	double FLAG_Array[64] = { 0, };
	for (int i = 0;i < 63;i++)
	{
		if (blockArray[i + 1] == FLAG_Array[i + 1])
		{
			AC_Flag = 1;
		}
		else
		{
			AC_Flag = 0;
			break;
		}

	}

	return AC_Flag;
}
void RE_AC_FLAG(int AC_Flag, double* blockArray)
{
	
	    if (AC_Flag == 1)
		{
			for (int i = 0;i < 63;i++)
				blockArray[i + 1] = 0;
		}

}

int CBCR_AC_FLAG(double* blockArray)
{
	int AC_Flag = 0;
	double FLAG_Array[16] = { 0, };
	for (int i = 0;i < 15;i++)
	{
		if (blockArray[i + 1] == FLAG_Array[i + 1])
		{
			AC_Flag = 1;
		}
		else
		{
			AC_Flag = 0;
			break;
		}

	}

	return AC_Flag;
}
void CBCR_RE_AC_FLAG(int AC_Flag, double* blockArray)
{

	if (AC_Flag == 1)
	{
		for (int i = 0;i < 15;i++)
			blockArray[i + 1] = 0;
	}

}
