#include "buffer.h"
double getCval(int y) {
	if (y == 0)
		return (sqrt(double(1) / double(N)));

	else
		return  (sqrt(double(2) / double(N)));
}

void dct(double* blockArray)
{
	double dct_bk_Array[NR];
	
	for (int x = 0; x < N; x++) //x행
	{
		for (int y = 0; y < N; y++)// y열 출력
		{
			double dInputSum = 0;
			for (int j = 0; j < N; j++)// 8개의 값 받아와서 계산하기
			{
				dInputSum += blockArray[(j + (N * x))] * (double)cos(((2 * double(j) + 1) * double(y) * M_PIl) / (double(2) * double(N)));

			}
			if (y == 0)
				dct_bk_Array[y + (8 * x)] = (sqrt(double(1) / double(N))) * dInputSum;//저장하기
			else
				dct_bk_Array[y + (8 * x)] = (sqrt(double(2) / double(N))) * dInputSum;//저장하기

		}

	}
	for (int x = 0; x < N; x++) {
		for (int y = 0; y < N; y++)
		{
			double dInputSum = 0;
			for (int j = 0; j < N; j++)
			{
				int a = y + (N * j);

				dInputSum += dct_bk_Array[y + (N * j)] * (double)cos(((2 * double(j) + 1) * double(x) * M_PIl) / (double(2) * double(N)));

			}

			if (x == 0)
				blockArray[y + (8 * x)] = (sqrt(double(1) / double(N))) * dInputSum;//저장하기
			else
				blockArray[y + (8 * x)] = (sqrt(double(2) / double(N))) * dInputSum;//저장하기

		}

	}


}
void idct(double* blockArray)
{
	double Idct_bk_Array[NR];
	for (int x = 0; x < N; x++)
	{
		for (int y = 0; y < N; y++)
		{
			double dInputSum = 0;
			for (int k = 0; k < N; k++)
			{

				dInputSum += blockArray[y + (N * k)] * getCval(k) * (double)cos((((2 * double(x)) + 1) * double(k) * M_PIl) / (double(2) * double(N)));


			}

			Idct_bk_Array[y + (8 * x)] = dInputSum;//저장하기

		}

	}

	for (int x = 0; x < N; x++) //x행
	{
		for (int y = 0; y < N; y++)// y열 출력
		{
			double dInputSum = 0;
			for (int j = 0; j < N; j++)// 8개의 값 받아와서 계산하기
			{
				dInputSum += Idct_bk_Array[int(j + (N * x))] * getCval(j) * (double)cos(((2 * double(y) + 1) * double(j) * M_PIl) / (double(2) * double(N)));

			}
			blockArray[y + (8 * x)] = dInputSum;//저장하기

		}

	}


}
void CBCR_DCT(double* CBCRblockArray)
{
	double dct_bk_Array[CBCRBLOCK_H*CBCRBLOCK_W];

	for (int x = 0; x < CBCRBLOCK_W; x++) //x행
	{
		for (int y = 0; y < CBCRBLOCK_H; y++)// y열 출력
		{
			double dInputSum = 0;
			for (int j = 0; j < CBCRBLOCK_W; j++)// 8개의 값 받아와서 계산하기
			{
				dInputSum += CBCRblockArray[(j + (CBCRBLOCK_W * x))] * (double)cos(((2 * double(j) + 1) * double(y) * M_PIl) / (double(2) * double(CBCRBLOCK_W)));

			}
			if (y == 0)
				dct_bk_Array[y + (CBCRBLOCK_W * x)] = (sqrt(double(1) / double(CBCRBLOCK_W))) * dInputSum;//저장하기
			else
				dct_bk_Array[y + (CBCRBLOCK_W * x)] = (sqrt(double(2) / double(CBCRBLOCK_W))) * dInputSum;//저장하기

		}

	}
	for (int x = 0; x < CBCRBLOCK_H; x++) {
		for (int y = 0; y < CBCRBLOCK_W; y++)
		{
			double dInputSum = 0;
			for (int j = 0; j < CBCRBLOCK_H; j++)
			{
		
				dInputSum += dct_bk_Array[y + (CBCRBLOCK_W * j)] * (double)cos(((2 * double(j) + 1) * double(x) * M_PIl) / (double(2) * double(CBCRBLOCK_W)));

			}

			if (x == 0)
				CBCRblockArray[y + (CBCRBLOCK_W * x)] = (sqrt(double(1) / double(CBCRBLOCK_H))) * dInputSum;//저장하기
			else
				CBCRblockArray[y + (CBCRBLOCK_W * x)] = (sqrt(double(2) / double(CBCRBLOCK_H))) * dInputSum;//저장하기

		}

	}


}
void CBCR_IDCT(double* CBCRblockArray)
{
	double Idct_bk_Array[CBCRBLOCK_H * CBCRBLOCK_W];
	for (int x = 0; x < CBCRBLOCK_H; x++)
	{
		for (int y = 0; y < CBCRBLOCK_W; y++)
		{
			double dInputSum = 0;
			for (int k = 0; k < CBCRBLOCK_W; k++)
			{
				if (k == 0)
				{
					dInputSum += CBCRblockArray[y + (CBCRBLOCK_W * k)] * (sqrt(double(1) / double(CBCRBLOCK_H))) * (double)cos((((2 * double(x)) + 1) * double(k) * M_PIl) / (double(2) * double(CBCRBLOCK_H)));
				}
				else
				{
					dInputSum += CBCRblockArray[y + (CBCRBLOCK_W * k)] * (sqrt(double(2) / double(CBCRBLOCK_H))) * (double)cos((((2 * double(x)) + 1) * double(k) * M_PIl) / (double(2) * double(CBCRBLOCK_H)));
				}

			}

			Idct_bk_Array[y + (CBCRBLOCK_W * x)] = dInputSum;//저장하기

		}

	}

	for (int x = 0; x < CBCRBLOCK_H; x++) //x행
	{
		for (int y = 0; y < CBCRBLOCK_W; y++)// y열 출력
		{
			double dInputSum = 0;
			for (int j = 0; j < CBCRBLOCK_W; j++)// 8개의 값 받아와서 계산하기
			{
				if (j == 0)
				{
					dInputSum += Idct_bk_Array[int(j + (CBCRBLOCK_W * x))] * (sqrt(double(1) / double(CBCRBLOCK_H))) * (double)cos(((2 * double(y) + 1) * double(j) * M_PIl) / (double(2) * double(CBCRBLOCK_H)));
				}
				else
				{
					dInputSum += Idct_bk_Array[int(j + (CBCRBLOCK_W * x))] * (sqrt(double(2) / double(CBCRBLOCK_H))) * (double)cos(((2 * double(y) + 1) * double(j) * M_PIl) / (double(2) * double(CBCRBLOCK_H)));
				}

			}
			CBCRblockArray[y + (CBCRBLOCK_W * x)] = dInputSum;//저장하기

		}

	}


}
