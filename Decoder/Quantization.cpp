#include "buffer.h"

void Quantization(double* blockArray,int DCQP, int ACQP)
{
	int qblockArray[NR] = { 0, };
	for (int i = 0; i < 64; i++)
	{
		if (i == 0)
		{
			blockArray[i] = (int(blockArray[i]) / DCQP);
		}
		else blockArray[i] = (int(blockArray[i]) / ACQP);
	}
	

}

void iQuantization(double* blockArray, int DCQP, int ACQP)
{
	for (int i = 0; i < 64; i++)
	{
		if (i == 0)
		{
			blockArray[i] = ((blockArray[i]) * DCQP);
		}
		else blockArray[i] = ((blockArray[i]) * ACQP);
	}
}
void CBCR_Quantization(double* CBCRblockArray, int DCQP, int ACQP)
{
	
	for (int i = 0; i < 16; i++)
	{
		if (i == 0)
		{
			CBCRblockArray[i] = (int(CBCRblockArray[i]) / DCQP);
		}
		else CBCRblockArray[i] = (int(CBCRblockArray[i]) / ACQP);
	}
}
void CBCR_iQuantization(double* CBCRblockArray, int DCQP, int ACQP)
{
	for (int i = 0; i < 16; i++)
	{
		if (i == 0)
		{
			CBCRblockArray[i] = ((CBCRblockArray[i]) * DCQP);
		}
		else CBCRblockArray[i] = ((CBCRblockArray[i]) * ACQP);
	}
}