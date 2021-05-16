#include "buffer.h"

void mpm_flag(int* intra_modenum, int* intra_flag, int* intra_modenum_flag,int mode_num)
{
	if (mode_num == 0)
	{
		intra_modenum_flag[mode_num] = intra_modenum[mode_num];
		intra_flag[mode_num] = 0;
	}
	else if (intra_modenum[mode_num] == intra_modenum[mode_num-1])
	{
		 intra_modenum_flag[mode_num] = intra_modenum[mode_num];
		 intra_flag[mode_num] = 0;
	}
	else 
	{
	   if (intra_modenum[mode_num-1] == 0)
	   {
		   if (intra_modenum[mode_num] == 1)
		   {
			   intra_modenum_flag[mode_num] = 0;
		   }
		   else
		   {
			   intra_modenum_flag[mode_num] = 1;
		   }

	   }
	   if (intra_modenum[mode_num- 1] == 1)
	   {
		   if (intra_modenum[mode_num] == 0)
		   {
			   intra_modenum_flag[mode_num] = 0;
		   }
		   else
		   {
			   intra_modenum_flag[mode_num] =1;
		   }

	   }
	   if (intra_modenum[mode_num - 1] == 2)
	   {
		   if (intra_modenum[mode_num ] == 0)
		   {
			   intra_modenum_flag[mode_num] = 0;
		   }
		   else
		   {
			   intra_modenum_flag[mode_num] = 1;
		   }
	   }
	   
	   intra_flag[mode_num] = 1;

	}
	
	

	 
}

void impm_flag(int* intra_modenum1, int* intra_flag, int* intra_modenum_flag, int mode_num)
{
	if (mode_num==9)
	{
	//	printf("\n ¿©±â°ª %d \n", intra_flag[mode_num]);
	}
	if (mode_num == 0)
	{
		intra_modenum1[mode_num] = 0;
	}
	else if (intra_flag[mode_num] ==0)
	{
		intra_modenum1[mode_num] = intra_modenum1[mode_num-1];
		
	}
	else
	{
		if (intra_modenum1[mode_num - 1] == 0)
		{
			if (intra_modenum_flag[mode_num] == 0)
			{
				intra_modenum1[mode_num] = 1;
			}
			else
			{
				intra_modenum1[mode_num] = 2;
			}

		}
		else if (intra_modenum1[mode_num - 1] == 1)
		{
			if (intra_modenum_flag[mode_num] == 0)
			{
				intra_modenum1[mode_num] = 0;
			}
			else
			{
				intra_modenum1[mode_num] = 2;
			}

		}
		else 
		{
			if (intra_modenum_flag[mode_num] == 0)
			{
				intra_modenum1[mode_num] = 0;
			}
			else
			{
				intra_modenum1[mode_num] = 1;
			}
		}
	}

}
