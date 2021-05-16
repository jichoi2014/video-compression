#include "buffer.h"
void dcdpcm(int index, double* buffer_encod,double* blockarrey)
{   
	double dif[3] = {0,};
	double bufdif[3] = { 0, };
	double temp = 0;
	
	if (index != 0)
	{
	 
		if (index < WIDTH)
		{
			blockarrey[0] = blockarrey[0] - buffer_encod[index - N];
		}
		else if (index % WIDTH==0)
		{
			blockarrey[0] = blockarrey[0] - buffer_encod[index - (WIDTH*N)];
		}
		else
		{
		        dif[0] = blockarrey[0] - buffer_encod[index - (WIDTH * N)];
		  	
			    dif[1] = (blockarrey[0] - buffer_encod[index - N]);
			
		        dif[2] = blockarrey[0] - buffer_encod[index - N - (WIDTH * N)];


				for (int i = 0;i < 3;i++)
				{
					bufdif[i] = dif[i];
				 
				}
				for (int i = 0;i < 2;i++)
				{
					for (int j = 0;j < 2 - i;j++)
					{
						if (dif[j] > dif[j + 1])
						{
							temp = dif[j];
							dif[j] = dif[j + 1];
							dif[j + 1] = temp;
						}
					}
				}


		        if (dif[1]== bufdif[0])
		        {

					blockarrey[0] = blockarrey[0] - buffer_encod[index - (WIDTH * N)];

		        }
		        else if (dif[1] == bufdif[1])
		        {
					blockarrey[0] = blockarrey[0] - buffer_encod[index - N];

		        }
		        else
		        {
					blockarrey[0] = blockarrey[0] - buffer_encod[index - N - (WIDTH * N)];
		        }

		}
		

	}
	
}

void idcdpcm(int index, double* buffer_encod, double* blockarrey)
{
	
	double dif[3] = { 0, };
	double bufdif[3] = { 0, };
	double temp = 0;
	if (index == 0)
	{
	}
	else
	{

		if (index < WIDTH)
		{
			blockarrey[0] = blockarrey[0] + buffer_encod[index - N];
		}
		else if (index % WIDTH == 0)
		{
			blockarrey[0] = blockarrey[0] + buffer_encod[index - (WIDTH * N)];
		}
		else
		{
			dif[0] = blockarrey[0] + buffer_encod[index - (WIDTH * N)];

			dif[1] = blockarrey[0] + buffer_encod[index - N];

			dif[2] = blockarrey[0] + buffer_encod[index - N - (WIDTH * N)];


			for (int i = 0;i < 3;i++)
			{
				bufdif[i] = dif[i];

			}
			for (int i = 0;i < 2;i++)
			{
				for (int j = 0;j < 2 - i;j++)
				{
					if (dif[j] > dif[j + 1])
					{
						temp = dif[j];
						dif[j] = dif[j + 1];
						dif[j + 1] = temp;
					}
				}
			}


			if (dif[1] == bufdif[0])
			{

				blockarrey[0] = blockarrey[0] + buffer_encod[index - (WIDTH * N)];

			}
			else if (dif[1] == bufdif[1])
			{
				blockarrey[0] = blockarrey[0] + buffer_encod[index - N];

			}
			else
			{
				blockarrey[0] = blockarrey[0] + buffer_encod[index - N - (WIDTH * N)];
			}

		}

	}


}

void CBCR_dcdpcm(int cbcr_init_pix_loc, double* cb_buffer_encod, double* CBCRblockArray)
{
	double dif[3] = { 0, };
	double bufdif[3] = { 0, };
	double temp = 0;
	//0 UPPER //0=LEFT//2LEFT UPPER
	if (cbcr_init_pix_loc != 0)
	{

		if (cbcr_init_pix_loc < CBCRWIDTH)
		{
			CBCRblockArray[0] = CBCRblockArray[0] - cb_buffer_encod[cbcr_init_pix_loc - CBCRBLOCK_W];
		}
		else if (cbcr_init_pix_loc % CBCRWIDTH == 0)
		{
			CBCRblockArray[0] = CBCRblockArray[0] - cb_buffer_encod[cbcr_init_pix_loc - (CBCRWIDTH * CBCRBLOCK_H)];
		}
		else
		{
			dif[0] = CBCRblockArray[0] - cb_buffer_encod[cbcr_init_pix_loc - (CBCRWIDTH * CBCRBLOCK_H)];

			dif[1] = CBCRblockArray[0] - cb_buffer_encod[cbcr_init_pix_loc - CBCRBLOCK_W];

			dif[2] = CBCRblockArray[0] - cb_buffer_encod[cbcr_init_pix_loc - CBCRBLOCK_W - (CBCRWIDTH * CBCRBLOCK_H)];


			for (int i = 0;i < 3;i++)
			{
				bufdif[i] = dif[i];

			}
			for (int i = 0;i < 2;i++)
			{
				for (int j = 0;j < 2 - i;j++)
				{
					if (dif[j] > dif[j + 1])
					{
						temp = dif[j];
						dif[j] = dif[j + 1];
						dif[j + 1] = temp;
					}
				}
			}


			if (dif[1] == bufdif[0])
			{

				CBCRblockArray[0] = CBCRblockArray[0] - cb_buffer_encod[cbcr_init_pix_loc - (CBCRWIDTH * CBCRBLOCK_H)];

			}
			else if (dif[1] == bufdif[1])
			{
				CBCRblockArray[0] = CBCRblockArray[0] - cb_buffer_encod[cbcr_init_pix_loc - CBCRBLOCK_W];

			}
			else
			{
				CBCRblockArray[0] = CBCRblockArray[0] - cb_buffer_encod[cbcr_init_pix_loc - CBCRBLOCK_W - (CBCRWIDTH * CBCRBLOCK_H)];
			}

		}


	}

}
void CBCR_idcdpcm(int cbcr_init_pix_loc, double* cb_buffer_encod, double* CBCRblockArray)
{
	double dif[3] = { 0, };
	double bufdif[3] = { 0, };
	double temp = 0;
	//0 UPPER //0=LEFT//2LEFT UPPER
	if (cbcr_init_pix_loc != 0)
	{

		if (cbcr_init_pix_loc < CBCRWIDTH)
		{
			CBCRblockArray[0] = CBCRblockArray[0] + cb_buffer_encod[cbcr_init_pix_loc - CBCRBLOCK_W];
		}
		else if (cbcr_init_pix_loc % CBCRWIDTH == 0)
		{
			CBCRblockArray[0] = CBCRblockArray[0] + cb_buffer_encod[cbcr_init_pix_loc - (CBCRWIDTH * CBCRBLOCK_H)];
		}
		else
		{
			dif[0] = CBCRblockArray[0] + cb_buffer_encod[cbcr_init_pix_loc - (CBCRWIDTH * CBCRBLOCK_H)];

			dif[1] = CBCRblockArray[0] + cb_buffer_encod[cbcr_init_pix_loc - CBCRBLOCK_W];

			dif[2] = CBCRblockArray[0] + cb_buffer_encod[cbcr_init_pix_loc - CBCRBLOCK_W - (CBCRWIDTH * CBCRBLOCK_H)];


			for (int i = 0;i < 3;i++)
			{
				bufdif[i] = dif[i];

			}
			for (int i = 0;i < 2;i++)
			{
				for (int j = 0;j < 2 - i;j++)
				{
					if (dif[j] > dif[j + 1])
					{
						temp = dif[j];
						dif[j] = dif[j + 1];
						dif[j + 1] = temp;
					}
				}
			}


			if (dif[1] == bufdif[0])
			{

				CBCRblockArray[0] = CBCRblockArray[0] + cb_buffer_encod[cbcr_init_pix_loc - (CBCRWIDTH * CBCRBLOCK_H)];

			}
			else if (dif[1] == bufdif[1])
			{
				CBCRblockArray[0] = CBCRblockArray[0] + cb_buffer_encod[cbcr_init_pix_loc - CBCRBLOCK_W];

			}
			else
			{
				CBCRblockArray[0] = CBCRblockArray[0] + cb_buffer_encod[cbcr_init_pix_loc - CBCRBLOCK_W - (CBCRWIDTH * CBCRBLOCK_H)];
			}

		}


	}

}
