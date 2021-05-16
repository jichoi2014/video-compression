#include "buffer.h"

int intra(int nIndex, unsigned char* restored_data,double* blockArray)
{
	
	double storageArray0[64] = { 0, };
	double storageArray1[64] = { 0, };
	double storageArray2[64] = { 0, };
	int modenum = 0;
	double sad0 = 0;
	double sad1 = 0;
	double sad2 = 0;
	double mean = 0;
	if (nIndex == 0)//0.0
	{
		
		//평균값
		
		mean = 128;
		for (int x = 0; x < 8; x++)
		{
			for (int y = 0; y < 8; y++)
			{
				blockArray[y + (8 * x)] = blockArray[y + (8 * x)] - mean;
				
			}
		}
		
		modenum = 0;

	}

	else if( nIndex < 351)//첫번째 행
	{


		for (int x = 0; x < 8; x++)//horizontal
		{
			for (int y = 0; y < 8; y++)
			{
				storageArray1[y + (8 * x)] = blockArray[y + (8 * x)] - restored_data[nIndex - 1 + (WIDTH * x)];
				sad1 += fabs(storageArray1[y + (8 * x)]);

			}
		}


		//평균값
	
		for (int z = 0; z < 8; z++)
		{
			mean += restored_data[nIndex - 1 + (WIDTH * z)];
		}
		mean = mean / 8;
		for (int x = 0; x < 8; x++)
		{
			for (int y = 0; y < 8; y++)
			{
				storageArray2[y + (8 * x)] = blockArray[y + (8 * x)] - mean;
				sad2 += fabs(storageArray2[y + (8 * x)]);

			}
		}


		if (sad1 <= sad2)
		{
			for (int i = 0; i < 64; i++)
			{
				blockArray[i] = storageArray1[i];
				
			}
			modenum = 1;
		}
		else 
		{
			for (int i = 0; i < 64; i++)
			{
				blockArray[i] = storageArray2[i];
				
			}
			modenum = 2;
		}

	}


	else if (nIndex  % (WIDTH*8) == 0 )//맨 왼쪽 열
	{
		
		for (int x = 0; x < 8; x++)//vertical
		{
			for (int y = 0; y < 8; y++)
			{
				storageArray0[x + (8 * y)] = blockArray[x + (8 * y)] - restored_data[nIndex - (WIDTH) + x];
				sad0 += fabs(storageArray0[x + (8 * y)]);
			}

		}

		for (int z = 0; z < 8; z++)//dc
		{
			mean += restored_data[nIndex - (WIDTH) + z];
		}
		
		mean = mean / 8;
		for (int x = 0; x < 8; x++)
		{
			for (int y = 0; y < 8; y++)
			{
				storageArray2[y + (8 * x)] = blockArray[y + (8 * x)] - mean;
				sad2 += fabs(storageArray2[y + (8 * x)]);
			}
		}

		if (sad0 <= sad2)
		{

			for (int i = 0; i < 64; i++)
			{
				blockArray[i] = storageArray0[i];
				
			}
			modenum = 0;
		}
		else
		{

			for (int i = 0; i < 64; i++)
			{
				blockArray[i] = storageArray2[i];
			
			}

			modenum = 2;
		}

	}
	else//나머지
	{
	
		for (int x = 0; x < 8; x++)//vertical
		{
			for (int y = 0; y < 8; y++)
			{
				storageArray0[x + (8 * y)] = blockArray[x + (8 * y)] - restored_data[nIndex - (WIDTH) + x];
				sad0 += fabs(storageArray0[x + (8 * y)]);
				
			}

		}
		
		for (int x = 0; x < 8; x++)//horizontal
		{
			for (int y = 0; y < 8; y++)
			{
				storageArray1[y + (8 * x)] = blockArray[y + (8 * x)] - restored_data[nIndex - 1 + (WIDTH * x)];
				sad1 += fabs(storageArray1[y + (8 * x)]);
			}
		}
		
		
		//평균값
		for (int z = 0; z < 9; z++)//dc
		{
			mean += restored_data[nIndex - (WIDTH+1) + z];
		}
		for (int z = 0; z < 8; z++)
		{
			mean += restored_data[nIndex - 1 + (WIDTH * z)];
		}
		mean = mean / 17;
		for (int x = 0; x < 8; x++)
		{
			for (int y = 0; y < 8; y++)
			{
				storageArray2[y + (8 * x)] = blockArray[y + (8 * x)] - mean;
				sad2 += fabs(storageArray2[y + (8 * x)]);
			}
		}
		
		if (sad0 <= sad1&&sad0 <= sad2)
		{
			 
			
				for (int i = 0; i < 64; i++)
				{
					blockArray[i] = storageArray0[i];
					
				}
				modenum = 0;

		}
		else if (sad1 <= sad2)
		{
		
				for (int i = 0; i < 64; i++)
				{
					blockArray[i] = storageArray1[i];
					
				}
				
				modenum = 1;
		}
		else
		{
			
				for (int i = 0; i < 64; i++)
				{
					blockArray[i] = storageArray2[i];
					
				}
				
				modenum = 2;
		}
		
	}
	return modenum;
}

void iintra(int modenum, int nIndex, unsigned char* restored_data,double* blockArray)//
{
	double mean = 0;
	if (nIndex == 0)//0.0
	{
		
	
			
			mean = 128;
			for (int x = 0; x < 8; x++)
			{
				for (int y = 0; y < 8; y++)
				{
					blockArray[y + (8 * x)] += mean;

				}
			}
		
	}



	else if (nIndex < WIDTH)//첫번째 행
	{

		if (modenum == 1)
		{
			for (int x = 0; x < 8; x++)//horizontal
			{
				for (int y = 0; y < 8; y++)
				{
					blockArray[y + (8 * x)] += restored_data[nIndex - 1 + (WIDTH * x)];
					
				}
			}

		}

		//평균값
		if (modenum == 2)
		{
		
			for (int z = 0; z < 8; z++)
			{
				mean += restored_data[nIndex - 1 + (WIDTH * z)];
			}
			mean = mean / 8;
			for (int x = 0; x < 8; x++)
			{
				for (int y = 0; y < 8; y++)
				{
					blockArray[y + (8 * x)] += mean;

				}
			}

		}


	}


	else if (nIndex  % (WIDTH*8) == 0 )//맨 왼쪽 열
	{

		if (modenum == 0)
		{
			//printf("실행");
			for (int x = 0; x < 8; x++)//vertical
			{
				for (int y = 0; y < 8; y++)
				{
					blockArray[x + (8 * y)] = blockArray[x + (8 * y)] + restored_data[nIndex - (WIDTH) + x];

				}

			}
		}

		if (modenum == 2)
		{
			for (int z = 0; z < 8; z++)//dc
			{
				mean += restored_data[nIndex - (WIDTH)+ z];
			}
			mean = mean / 8;
			for (int x = 0; x < 8; x++)
			{
				for (int y = 0; y < 8; y++)
				{
					blockArray[y + (8 * x)] += mean;

				}
			}
		}


	}

	else//나머지
	{ 
	

		if (modenum == 0)
		{
			for (int x = 0; x < 8; x++)//vertical
			{
				for (int y = 0; y < 8; y++)
				{
					blockArray[x + (8 * y)] += restored_data[nIndex - (WIDTH) + x];

				}

			}

		}
		if (modenum == 1)
		{
			for (int x = 0; x < 8; x++)//horizontal
			{
				for (int y = 0; y < 8; y++)
				{
					blockArray[y + (8 * x)] += restored_data[nIndex - 1 + (WIDTH * x)];

				}
			}

		}
		//평균값
		if (modenum == 2)
		{
			for (int z = 0; z < 9; z++)//dc
			{
				mean += restored_data[nIndex - (WIDTH+1) + z];

			}
			for (int z = 0; z < 8; z++)
			{
				mean += restored_data[nIndex - 1 + (WIDTH * z)];
			}
			mean = mean / 17;
			for (int x = 0; x < 8; x++)
			{
				for (int y = 0; y < 8; y++)
				{
					blockArray[y + (8 * x)] += mean;

				}
			}

		}
	

	}




}
void icbcr_intra(int cbcr_init_pix_loc, unsigned char* cbcr_restored_data, double* CBCRblockArray, int intra_modenum)
{
	double mean = 128;
	if (cbcr_init_pix_loc == 0)//0.0
	{
		//평균값
		mean = 128;
		for (int y = 0; y < CBCRBLOCK_H; y++)
		{
			for (int x = 0; x < CBCRBLOCK_W; x++)
			{
				CBCRblockArray[x + (CBCRBLOCK_W * y)] = CBCRblockArray[x + (CBCRBLOCK_W * y)] + mean;

			}
		}


	}

	else if (cbcr_init_pix_loc < CBCRWIDTH)//첫번째 행
	{

		if (intra_modenum == 1)
		{
			for (int y = 0; y < CBCRBLOCK_H; y++)//horizontal
			{
				for (int x = 0; x < CBCRBLOCK_W; x++)
				{
					CBCRblockArray[x + (CBCRBLOCK_W * y)] = CBCRblockArray[x + (CBCRBLOCK_W * y)] + cbcr_restored_data[cbcr_init_pix_loc - 1 + (CBCRWIDTH * y)];


				}
			}
		}


		//평균값
		else
		{
			for (int z = 0; z < CBCRBLOCK_H; z++)
			{
				mean += cbcr_restored_data[cbcr_init_pix_loc - 1 + (CBCRWIDTH * z)];
			}
			mean = mean / CBCRBLOCK_H;
			for (int x = 0; x < CBCRBLOCK_H; x++)
			{
				for (int y = 0; y < CBCRBLOCK_W; y++)
				{
					CBCRblockArray[y + (CBCRBLOCK_W * x)] = CBCRblockArray[y + (CBCRBLOCK_W * x)] + mean;
				}
			}
		}

	}


	else if (cbcr_init_pix_loc % CBCRWIDTH == 0)//맨 왼쪽 열
	{
		if (intra_modenum == 0)
		{
			for (int x = 0; x < CBCRBLOCK_H; x++)//vertical
			{
				for (int y = 0; y < CBCRBLOCK_W; y++)
				{
					CBCRblockArray[y + (CBCRBLOCK_W * x)] = CBCRblockArray[y + (CBCRBLOCK_W * x)] + cbcr_restored_data[cbcr_init_pix_loc - (CBCRWIDTH)+x];
				}

			}
		}
		else
		{
			for (int z = 0; z < CBCRBLOCK_W; z++)//dc
			{
				mean += cbcr_restored_data[cbcr_init_pix_loc - (WIDTH)+z];
			}
			mean = mean / CBCRBLOCK_W;
			for (int x = 0; x < CBCRBLOCK_H; x++)
			{
				for (int y = 0; y < CBCRBLOCK_W; y++)
				{
					CBCRblockArray[y + (CBCRBLOCK_W * x)] = CBCRblockArray[y + (CBCRBLOCK_W * x)] + mean;
				}
			}
		}

	}
	else//나머지
	{
		if (intra_modenum == 0)
		{
			for (int x = 0; x < CBCRBLOCK_H; x++)//vertical
			{
				for (int y = 0; y < CBCRBLOCK_W; y++)
				{
					CBCRblockArray[y + (CBCRBLOCK_W * x)] = CBCRblockArray[y + (CBCRBLOCK_W * x)] + cbcr_restored_data[cbcr_init_pix_loc - (CBCRWIDTH)+x];
				}

			}
		}
		else if (intra_modenum == 1)
		{
			for (int x = 0; x < CBCRBLOCK_H; x++)//horizontal
			{
				for (int y = 0; y < CBCRBLOCK_W; y++)
				{
					CBCRblockArray[y + (CBCRBLOCK_W * x)] = CBCRblockArray[y + (CBCRBLOCK_W * x)] + cbcr_restored_data[cbcr_init_pix_loc - 1 + (CBCRWIDTH * x)];

				}
			}
		}

		else
		{
			for (int z = 0; z < (CBCRBLOCK_W + 1); z++)//dc
			{
				mean += cbcr_restored_data[cbcr_init_pix_loc - (CBCRWIDTH + 1) + z];
			}
			for (int z = 0; z < CBCRBLOCK_H; z++)
			{
				mean += cbcr_restored_data[cbcr_init_pix_loc - 1 + (CBCRWIDTH * z)];
			}
			mean = mean /9;//CBCRBLOCK_H + CBCRBLOCK_W + 1
			for (int x = 0; x < CBCRBLOCK_H; x++)
			{
				for (int y = 0; y < CBCRBLOCK_W; y++)
				{
					CBCRblockArray[y + (CBCRBLOCK_W * x)] = CBCRblockArray[y + (CBCRBLOCK_W * x)] + mean;

				}
			}
		}


	}

}
void cbcr_intra(int cbcr_init_pix_loc, unsigned char* cbcr_restored_data, double* CBCRblockArray, int intra_modenum)
{
	double mean = 128;
	if (cbcr_init_pix_loc == 0)//0.0
	{
		//평균값
		mean = 128;
		for (int y = 0; y < CBCRBLOCK_H; y++)
		{
			for (int x = 0; x < CBCRBLOCK_W; x++)
			{
				CBCRblockArray[x + (CBCRBLOCK_W * y)] = CBCRblockArray[x + (CBCRBLOCK_W * y)] - mean;

			}
		}


	}

	else if (cbcr_init_pix_loc < CBCRWIDTH)//첫번째 행
	{

		if (intra_modenum == 1)
		{
			for (int y = 0; y < CBCRBLOCK_H; y++)//horizontal
			{
				for (int x = 0; x < CBCRBLOCK_W; x++)
				{
					CBCRblockArray[x + (CBCRBLOCK_W * y)] = CBCRblockArray[x + (CBCRBLOCK_W * y)] - cbcr_restored_data[cbcr_init_pix_loc - 1 + (CBCRWIDTH * y)];
	

				}
			}
		}


		//평균값
		else
		{
			for (int z = 0; z < CBCRBLOCK_H; z++)
			{
				mean += cbcr_restored_data[cbcr_init_pix_loc - 1 + (CBCRWIDTH * z)];
			}
			mean = mean / CBCRBLOCK_H;
			for (int x = 0; x < CBCRBLOCK_H; x++)
			{
				for (int y = 0; y < CBCRBLOCK_W; y++)
				{
					CBCRblockArray[y + (CBCRBLOCK_W * x)] = CBCRblockArray[y + (CBCRBLOCK_W * x)] - mean;
				}
			}
		}

	}


	else if (cbcr_init_pix_loc % CBCRWIDTH == 0)//맨 왼쪽 열
	{
		if (intra_modenum == 0)
		{
			for (int x = 0; x < CBCRBLOCK_H; x++)//vertical
			{
				for (int y = 0; y < CBCRBLOCK_W; y++)
				{
					CBCRblockArray[y + (CBCRBLOCK_W * x)] = CBCRblockArray[y + (CBCRBLOCK_W * x)] - cbcr_restored_data[cbcr_init_pix_loc - (CBCRWIDTH)+x];
				}

			}
		}
		else
		{
			for (int z = 0; z < CBCRBLOCK_W; z++)//dc
			{
				mean += cbcr_restored_data[cbcr_init_pix_loc - (WIDTH)+z];
			}
			mean = mean / CBCRBLOCK_W;
			for (int x = 0; x < CBCRBLOCK_H; x++)
			{
				for (int y = 0; y < CBCRBLOCK_W; y++)
				{
					CBCRblockArray[y + (CBCRBLOCK_W * x)] = CBCRblockArray[y + (CBCRBLOCK_W * x)] - mean;					
				}
			}
		}

	}
	else//나머지
	{
		if (intra_modenum == 0)
		{
			for (int x = 0; x < CBCRBLOCK_H; x++)//vertical
			{
				for (int y = 0; y < CBCRBLOCK_W; y++)
				{
					CBCRblockArray[y + (CBCRBLOCK_W * x)] = CBCRblockArray[y + (CBCRBLOCK_W * x)] - cbcr_restored_data[cbcr_init_pix_loc - (CBCRWIDTH)+x];
				}

			}
		}
		else if (intra_modenum == 1)
		{
			for (int x = 0; x < CBCRBLOCK_H; x++)//horizontal
			{
				for (int y = 0; y < CBCRBLOCK_W; y++)
				{
					CBCRblockArray[y + (CBCRBLOCK_W * x)] = CBCRblockArray[y + (CBCRBLOCK_W * x)] - cbcr_restored_data[cbcr_init_pix_loc - 1 + (CBCRWIDTH * x)];

				}
			}
		}

		else
		{
			for (int z = 0; z < (CBCRBLOCK_W + 1); z++)//dc
			{
				mean += cbcr_restored_data[cbcr_init_pix_loc - (CBCRWIDTH + 1) + z];
			}
			for (int z = 0; z < CBCRBLOCK_H; z++)
			{
				mean += cbcr_restored_data[cbcr_init_pix_loc - 1 + (CBCRWIDTH * z)];
			}
			mean = mean / (9);//CBCRBLOCK_H+CBCRBLOCK_W+1
			for (int x = 0; x < CBCRBLOCK_H; x++)
			{
				for (int y = 0; y < CBCRBLOCK_W; y++)
				{
					CBCRblockArray[y + (CBCRBLOCK_W * x)] = CBCRblockArray[y + (CBCRBLOCK_W * x)] - mean;

				}
			}
		}
		

	}

}