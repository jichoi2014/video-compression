#include "buffer.h"

void spiral(int* spiral_x, int* spiral_y)
{
	int num = 0;
	for (int i = 0; i < SPIRALLINE; i++)
	{
		
		if (i == 0)
		{
			spiral_x[i] = 0;
			spiral_y[i] = 0;
			num++;
			
			
		}
		
		else if (i % 2 != 0)
		{
			for (int j = 0; j < i; j++)
			{
				spiral_x[num ] = 1;
				spiral_y[num] = 0;
				num++;
			}
			for (int j = 0; j < i; j++)
			{
				spiral_x[num] = 0;
				spiral_y[num] = 1;
				num++;
			}
		}
	
		else if (i % 2 == 0)
			{
				for (int j = 0; j < i; j++)
				{
					spiral_x[num] = -1;
					spiral_y[num] = 0;
					num++; 
					
					
				}
				for (int j = 0; j < i; j++)
				{
					spiral_x[num] = 0;
					spiral_y[num] = -1;
					num++;
				}
				if (i == 32)
				{
					for (int j = 0; j < i; j++)
					{
						spiral_x[num] = 1;
						spiral_y[num] = 0;
						num++;
					}
     			}
			}
			

		
	}


}
void padding(unsigned char* restored_data, unsigned char* buffer_padding)
{
	int num=0;
	int num2 = 0;
	int num3 = 0;
	for (int pixelnum = 0; pixelnum < PWIDTH*PHEIGHT; pixelnum++)
	{
		
		if (pixelnum < (PWIDTH * 16))//상위 16칸
		{
			if (pixelnum % PWIDTH < 16)//좌측 맨 위
			{
				buffer_padding[pixelnum] = restored_data[0];
			
			}
			
			else if (pixelnum % PWIDTH > 15 && pixelnum % PWIDTH < (PWIDTH - 16))//모서리를 제외한 나머지
			{
				buffer_padding[pixelnum] = restored_data[pixelnum % PWIDTH -16];
				
			}
			else
			{
				buffer_padding[pixelnum] = restored_data[WIDTH-1];//우측 맨 위
				
			}

		}
		else if (pixelnum >= (PWIDTH * 16) && pixelnum < (PWIDTH * (PHEIGHT - 16)))//중간
		{

			if (pixelnum % PWIDTH < 16)//좌측
			{
				buffer_padding[pixelnum] = restored_data[num*WIDTH];
				if (pixelnum % PWIDTH == 15)
				{
					num++;
				}
				
				

			}

			else if (pixelnum % PWIDTH > 15 && pixelnum % PWIDTH < (PWIDTH - 16))//우측좌측 제외한 나머지
			{
				buffer_padding[pixelnum] = restored_data[num2];
				num2++;
			}
			else
			{
				buffer_padding[pixelnum] = restored_data[num3 * WIDTH+351];//우측
				if (pixelnum % PWIDTH == 383)
				{
					num3++;
				}
			}
		
		}
		
		else
		{
				if (pixelnum % PWIDTH < 16)//좌측 맨 위
				{
					buffer_padding[pixelnum] = restored_data[WIDTH*(HEIGHT-1)];
				}
				else if (pixelnum % PWIDTH > 15 && pixelnum % PWIDTH < (PWIDTH - 16))//모서리를 제외한 나머지
				{
					buffer_padding[pixelnum] = restored_data[(pixelnum % PWIDTH - 16)+ WIDTH * (HEIGHT - 1)];
				}
				else
				{
					buffer_padding[pixelnum] = restored_data[WIDTH * HEIGHT - 1];//우측 맨 위
				}

			
		}
	}
	
		

	
}
void inter(int nIndex, unsigned char* buffer_padding,int* mvx ,int* mvy, unsigned char* restored_data,int* spiral_x, int* spiral_y, double* blockArray)
{
	int startnIdex = nIndex;
	int inIndex = 0;
	inIndex = (((int)(startnIdex / WIDTH))*PWIDTH+16+ (startnIdex % WIDTH)+ PWIDTH*16);//첫위치 구하기 = 몇번째 행인가를 확인한후 패딩에 폭많금 곱해주고 16을 더해준다
	
	double StorageArray[NR] = { 0, };
	double bufferArray[NR] = { 0, };
	int mv_x = 0;
	int mv_y = 0;
	int buffermv_x = 0;
	int buffermv_y = 0;
	double Storagesad = 0;
	double buffersad = 0;
	
	for (int search = 0;search < SPIRAL_W* SPIRAL_H;search++)
	{
		buffersad = 0;
		buffermv_x = spiral_x[search];
		buffermv_y = spiral_y[search];// 값으로 받아오기
		
		
		for (int y=0;y<8;y++)
		{//여기서 받아오기

			for (int x=0;x < 8;x++)
			{
				
				bufferArray[x + 8 * y] = blockArray[x + (8 * y)] - double(buffer_padding[inIndex + PWIDTH * y + buffermv_x + (buffermv_y * PWIDTH) + x]);
				buffersad += fabs(bufferArray[x + 8 * y]);
				
			}
		}

		if (search == 0)
		{
			
			mv_x = buffermv_x;
			mv_y = buffermv_y;
			Storagesad = buffersad;

		}
		else if (search > 0)
		{
			if (buffersad < Storagesad)
			{
				
				mv_x = buffermv_x;
				mv_y = buffermv_y;
				Storagesad = buffersad;

			}
		}
	}

	for (int i = 0;i < N;i++)
	{
		for (int j = 0;j < N; j++)
		{

			blockArray[j + i * N] = blockArray[j + i * N] - double(buffer_padding[inIndex + PWIDTH * i + mv_x + (mv_y * PWIDTH) + j]);
			//blockArray[j + i * N] = double(buffer_padding[inIndex + PWIDTH * i + mv_x + (mv_y * PWIDTH) + j]);
		}

	}
	
	
	
	*mvx = mv_x;//받아오기
	*mvy = mv_y;//받아오기
		
	
		
}

void iinter(int nIndex, unsigned char* buffer_padding, double* mvx, double* mvy, double* blockArray)
{
	int startnIdex = nIndex;

	int inIndex = (((int)(startnIdex / WIDTH)) * PWIDTH + 16 + (startnIdex % WIDTH) + PWIDTH * 16);//첫위치 구하기 = 몇번째 행인가를 확인한후 패딩에 폭많금 곱해주고 16을 더해준다

	int buffermv_x = 0;
	int buffermv_y = 0;



	
		buffermv_x = *mvx;
		buffermv_y = *mvy;
		for (int i = 0;i < N;i++)
			{
				for (int j = 0;j < N; j++)
				{
					
					blockArray[i + j*N] = blockArray[i + j * N] + double(buffer_padding[inIndex + PWIDTH * j + buffermv_x + (buffermv_y * PWIDTH) + i]);
				}
				
			}

}
void cb_padding(unsigned char* cb_restored_data, unsigned char* cb_buffer_padding)
{
	int num = 0;
	int num2 = 0;
	int num3 = 0;
	for (int pixelnum = 0; pixelnum < CBCRPWIDTH * CBCRPHEIGHT; pixelnum++)
	{

		if (pixelnum < (CBCRPWIDTH * 8))//상위 8칸
		{
			if (pixelnum % CBCRPWIDTH < 8)//좌측 맨 위
			{
				cb_buffer_padding[pixelnum] = cb_restored_data[0];

			}

			else if (pixelnum % CBCRPWIDTH >= 8 && pixelnum % CBCRPWIDTH < (CBCRPWIDTH - 8))//모서리를 제외한 나머지
			{
				cb_buffer_padding[pixelnum] = cb_restored_data[pixelnum % CBCRPWIDTH - 8];

			}
			else
			{
				cb_buffer_padding[pixelnum] = cb_restored_data[CBCRWIDTH - 1];//우측 맨 위

			}

		}
		else if (pixelnum >= (CBCRPWIDTH * 8) && pixelnum < (CBCRPWIDTH * (CBCRPHEIGHT - 8)))//중간
		{

			if (pixelnum % PWIDTH < 8)//좌측
			{
				cb_buffer_padding[pixelnum] = cb_restored_data[num * CBCRWIDTH];
				if (pixelnum % PWIDTH == 7)
				{
					num++;
				}
			}

			else if (pixelnum % CBCRPWIDTH >=8 && pixelnum % CBCRPWIDTH < (CBCRPWIDTH - 8))//우측좌측 제외한 나머지
			{
				cb_buffer_padding[pixelnum] = cb_restored_data[num2];
				num2++;
			}
			else
			{
				cb_buffer_padding[pixelnum] = cb_restored_data[num3 * CBCRWIDTH + (CBCRWIDTH - 1)];//우측
				if (pixelnum % CBCRPWIDTH == 191)
				{
					num3++;
				}
			}

		}

		else
		{
			if (pixelnum % CBCRPWIDTH < 8)//좌측 맨 위
			{
				cb_buffer_padding[pixelnum] = cb_restored_data[CBCRWIDTH * (CBCRHEIGHT - 1)];
			}
			else if (pixelnum % CBCRPWIDTH >= 8 && pixelnum % CBCRPWIDTH < (CBCRPWIDTH - 8))//모서리를 제외한 나머지
			{
				cb_buffer_padding[pixelnum] = cb_restored_data[(pixelnum % CBCRPWIDTH - 8) + CBCRWIDTH * (CBCRHEIGHT - 1)];
			}
			else
			{
				cb_buffer_padding[pixelnum] = cb_restored_data[CBCRWIDTH * CBCRHEIGHT - 1];//우측 맨 위
			}


		}
	}




}
void CBCR_inter(int cbcr_init_pix_loc, unsigned char* cb_buffer_padding, int mvx, int mvy, unsigned char* cb_restored_data, double* CBCRblockArray)
{
	int Position = 0;
	Position = (((int)(cbcr_init_pix_loc / CBCRWIDTH)) * CBCRPWIDTH + 8 + (cbcr_init_pix_loc % CBCRWIDTH) + CBCRPWIDTH * 8);//첫위치 구하기 = 몇번째 행인가를 확인한후 패딩에 폭많금 곱해주고 16을 더해준다

		for (int y = 0;y < CBCRBLOCK_H;y++)
		{

			for (int x = 0;x < CBCRBLOCK_W;x++)
			{

				CBCRblockArray[x + CBCRBLOCK_H * y] = CBCRblockArray[x + CBCRBLOCK_H * y] - double(cb_buffer_padding[Position + CBCRPWIDTH * y + mvx + (mvy * CBCRPWIDTH) + x]);
				

			}
		}

}
void iCBCR_inter(int cbcr_init_pix_loc, unsigned char* cb_buffer_padding, double mvx, double mvy, unsigned char* cb_restored_data, double* CBCRblockArray)
{
	int Position = 0;
	Position = (((int)(cbcr_init_pix_loc / CBCRWIDTH)) * CBCRPWIDTH + 8 + (cbcr_init_pix_loc % CBCRWIDTH) + CBCRPWIDTH * 8);//첫위치 구하기 = 몇번째 행인가를 확인한후 패딩에 폭많금 곱해주고 16을 더해준다
	int a = mvx;
	int b = mvy;
	for (int y = 0;y < CBCRBLOCK_H;y++)
	{

		for (int x = 0;x < CBCRBLOCK_W;x++)
		{

			CBCRblockArray[x + CBCRBLOCK_H * y] = CBCRblockArray[x + CBCRBLOCK_H * y] + double(cb_buffer_padding[Position + CBCRPWIDTH * y + a + (b * CBCRPWIDTH) + x]);


		}
	}
}