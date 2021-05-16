#include "buffer.h"

void write_entropy(int* buf_cnt, unsigned char* buf_write,int* buf_entropy,FILE* Comp_write_File)
{
	//printf("\n입력값 :  ");
	for (int i = 0; i < 8;i++)
	{
		*buf_write += buf_entropy[i] * (128 / pow(2, i));
		//printf("%d ", buf_entropy[i]);
	}
	fwrite(buf_write, sizeof(unsigned char), 1, Comp_write_File);

	*buf_write = 0;
	*buf_cnt = 0;
}
void com_read_data(int* ientropy_buf_cnt, unsigned char* buf_write, int* buf_entropy, FILE* Comp_read_File)
{
	
	int a=0;
		fread(buf_write, sizeof(unsigned char), 1, Comp_read_File);
		for (int i = 0; i < 8;i++)
		{
			
			buf_entropy[i] = *buf_write / (128 / pow(2, i));
			a = (128 / pow(2, i));
			*buf_write = *buf_write % a;
		}
		*ientropy_buf_cnt = 0;
		*buf_entropy = 0;
	
}
void Conversion_entropy(int* buf_cnt,double blockArray,unsigned char* buf_write, int* buf_entropy, FILE* Compression_File)
{
	
	//abs
	if (fabs(blockArray) == 0)
	{
		buf_entropy[*buf_cnt] = 0;
		*buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
		buf_entropy[*buf_cnt] = 0;
		*buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
	}
	else if (fabs(blockArray) == 1)
	{
		buf_entropy[*buf_cnt] = 0;
		*buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
		 buf_entropy[*buf_cnt] = 1;
		*buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
		
		buf_entropy[*buf_cnt] = 0;
		*buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
		if (blockArray < 0)
		{
			buf_entropy[*buf_cnt] = 0;
			*buf_cnt += 1;
			if (*buf_cnt == 8)
			{
				write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
			}
		}
		else
		{
			buf_entropy[*buf_cnt] = 1;
			*buf_cnt += 1;
			if (*buf_cnt == 8)
			{
				write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
			}
		}

	}
	else if (fabs(blockArray) >= 2&&fabs(blockArray)<4)
	{
	    int buf_num = fabs(blockArray) - 2;
	    buf_entropy[*buf_cnt] = 0;
	    *buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
	    buf_entropy[*buf_cnt] = 1;
	    *buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
	    
	    buf_entropy[*buf_cnt] = 1;
	    *buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
	    if (blockArray < 0)
	    {
	    	buf_entropy[*buf_cnt] = 0;
	    	*buf_cnt += 1;
			if (*buf_cnt == 8)
			{
				write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
			}
	    }
	    else
	    {
	    	buf_entropy[*buf_cnt] = 1;
	    	*buf_cnt += 1;
			if (*buf_cnt == 8)
			{
				write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
			}
	    }
	    buf_entropy[*buf_cnt] = buf_num%2;
	    *buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
	}
	else if (fabs(blockArray) >= 4 && fabs(blockArray) < 8)
	{
		int buf_num = fabs(blockArray) - 4;
		buf_entropy[*buf_cnt] = 1;
		*buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
		buf_entropy[*buf_cnt] = 0;
		*buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}

		buf_entropy[*buf_cnt] = 0;
		*buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
		if (blockArray < 0)
		{
			buf_entropy[*buf_cnt] = 0;
			*buf_cnt += 1;
			if (*buf_cnt == 8)
			{
				write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
			}
		}
		else
		{
			buf_entropy[*buf_cnt] = 1;
			*buf_cnt += 1;
			if (*buf_cnt == 8)
			{
				write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
			}
		}
		buf_entropy[*buf_cnt] = buf_num / 2;
		*buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
		buf_entropy[*buf_cnt] = buf_num % 2;
		*buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
	}
	else if (fabs(blockArray) >= 8 && fabs(blockArray) < 16)
	{
	    int rest_buf_num = 0;
	    int buf_num = fabs(blockArray) - 8;
	    buf_entropy[*buf_cnt] = 1;
	    *buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
	    buf_entropy[*buf_cnt] = 0;
	    *buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
	    
	    buf_entropy[*buf_cnt] = 1;
	    *buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
	    if (blockArray < 0)
	    {
	    	buf_entropy[*buf_cnt] = 0;
	    	*buf_cnt += 1;
			if (*buf_cnt == 8)
			{
				write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
			}
	    }
	    else
	    {
	    	buf_entropy[*buf_cnt] = 1;
	    	*buf_cnt += 1;
			if (*buf_cnt == 8)
			{
				write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
			}
	    }
	    buf_entropy[*buf_cnt] = buf_num / 4;
	    rest_buf_num = buf_num % 4;
	    *buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
	    buf_entropy[*buf_cnt] = rest_buf_num / 2;
	    
	    *buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
	    buf_entropy[*buf_cnt] = rest_buf_num % 2;
	    *buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
	}
	else if (fabs(blockArray) >= 16 && fabs(blockArray) < 32)
	{
	    int rest_buf_num = 0;
	    int buf_num = fabs(blockArray) - 16;
	    buf_entropy[*buf_cnt] = 1;
	    *buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
	    buf_entropy[*buf_cnt] = 1;
	    *buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
	    
	    buf_entropy[*buf_cnt] = 0;
	    *buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
	    if (blockArray < 0)
	    {
	    	buf_entropy[*buf_cnt] = 0;
	    	*buf_cnt += 1;
			if (*buf_cnt == 8)
			{
				write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
			}
	    }
	    else
	    {
	    	buf_entropy[*buf_cnt] = 1;
	    	*buf_cnt += 1;
			if (*buf_cnt == 8)
			{
				write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
			}
	    }
	    buf_entropy[*buf_cnt] = buf_num / 8;
	    rest_buf_num = buf_num % 8;
	    *buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
	    buf_entropy[*buf_cnt] = rest_buf_num / 4;
	    rest_buf_num = rest_buf_num % 4;
	    *buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
	    buf_entropy[*buf_cnt] = rest_buf_num / 2;
	    *buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
	    
	    buf_entropy[*buf_cnt] = rest_buf_num % 2;
	    *buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
	}
	else if (fabs(blockArray) >= 32 && fabs(blockArray) < 64)
	{
	    int rest_buf_num = 0;
	    int buf_num = fabs(blockArray) - 32;
	    buf_entropy[*buf_cnt] = 1;
	    *buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
	    buf_entropy[*buf_cnt] = 1;
	    *buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
	    
	    buf_entropy[*buf_cnt] = 1;
	    *buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
	    buf_entropy[*buf_cnt] = 0;
	    *buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
	    if (blockArray < 0)
	    {
	    	buf_entropy[*buf_cnt] = 0;
	    	*buf_cnt += 1;
			if (*buf_cnt == 8)
			{
				write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
			}
	    }
	    else
	    {
	    	buf_entropy[*buf_cnt] = 1;
	    	*buf_cnt += 1;
			if (*buf_cnt == 8)
			{
				write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
			}
	    }
	    buf_entropy[*buf_cnt] = buf_num / 16;
	    rest_buf_num = buf_num % 16;
	    *buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
	    buf_entropy[*buf_cnt] = rest_buf_num / 8;
	    rest_buf_num = rest_buf_num % 8;
	    *buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
	    buf_entropy[*buf_cnt] = rest_buf_num / 4;
	    rest_buf_num = rest_buf_num % 4;
	    *buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
	    buf_entropy[*buf_cnt] = rest_buf_num / 2;
	    *buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
	    
	    buf_entropy[*buf_cnt] = rest_buf_num % 2;
	    *buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
	}
	else if (fabs(blockArray) >= 64 && fabs(blockArray) < 128)
	{
	    int rest_buf_num = 0;//range값을 찾기위한 변수
	    int buf_num = fabs(blockArray) - 64;//range값을 찾기위한 변수
	    buf_entropy[*buf_cnt] = 1;//code word
	    *buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
	    buf_entropy[*buf_cnt] = 1;//code word
	    *buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
	    
	    buf_entropy[*buf_cnt] = 1;//code word
	    *buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
	    buf_entropy[*buf_cnt] = 1;//code word
	    *buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
	    buf_entropy[*buf_cnt] = 0;//code word
	    *buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
	    if (blockArray < 0)////sign
	    {
	    	buf_entropy[*buf_cnt] = 0;
	    	*buf_cnt += 1;
			if (*buf_cnt == 8)
			{
				write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
			}
	    }
	    else
	    {
	    	buf_entropy[*buf_cnt] = 1;
	    	*buf_cnt += 1;
			if (*buf_cnt == 8)
			{
				write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
			}
	    }
	    buf_entropy[*buf_cnt] = buf_num / 32;//Range 계산
	    rest_buf_num = buf_num % 32;
	    *buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
	    buf_entropy[*buf_cnt] = rest_buf_num / 16;
	    rest_buf_num = rest_buf_num % 16;
	    *buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
	    buf_entropy[*buf_cnt] = rest_buf_num / 8;
	    rest_buf_num = rest_buf_num % 8;
	    *buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
	    buf_entropy[*buf_cnt] = rest_buf_num / 4;
	    rest_buf_num = rest_buf_num % 4;
	    *buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
	    buf_entropy[*buf_cnt] = rest_buf_num / 2;
	    *buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
	    
	    buf_entropy[*buf_cnt] = rest_buf_num % 2;
	    *buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
	}
	else if (fabs(blockArray) >= 128 && fabs(blockArray) < 256)
	{
	
	    int rest_buf_num = 0;//range값을 찾기위한 변수
	    int buf_num = fabs(blockArray) - 128;//range값을 찾기위한 변수
	    buf_entropy[*buf_cnt] = 1;//code word
	    *buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
	    buf_entropy[*buf_cnt] = 1;//code word
	    *buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
	    
	    buf_entropy[*buf_cnt] = 1;//code word
	    *buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
	    buf_entropy[*buf_cnt] = 1;//code word
	    *buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
	    buf_entropy[*buf_cnt] = 1;//code word
	    *buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
	    buf_entropy[*buf_cnt] = 0;//code word
	    *buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
	    if (blockArray < 0 )////sign
	    {
			
	    	buf_entropy[*buf_cnt] = 0;
	    	*buf_cnt += 1;
			if (*buf_cnt == 8)
			{
				write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
			}
	    }
	    else
	    {
			
	    	buf_entropy[*buf_cnt] = 1;
	    	*buf_cnt += 1;
			if (*buf_cnt == 8)
			{
				write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
			}
	    }
	    buf_entropy[*buf_cnt] = buf_num / 64;//Range 계산
	    rest_buf_num = buf_num % 64;
	    *buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
	    buf_entropy[*buf_cnt] = rest_buf_num / 32;//Range 계산
	    rest_buf_num = rest_buf_num % 32;
	    *buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
		
	    buf_entropy[*buf_cnt] = rest_buf_num / 16;
	    rest_buf_num = rest_buf_num % 16;
	    *buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
	    buf_entropy[*buf_cnt] = rest_buf_num / 8;
	    rest_buf_num = rest_buf_num % 8;
	    *buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
	    buf_entropy[*buf_cnt] = rest_buf_num / 4;
	    rest_buf_num = rest_buf_num % 4;
	    *buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
	    buf_entropy[*buf_cnt] = rest_buf_num / 2;
	    *buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
	    
	    buf_entropy[*buf_cnt] = rest_buf_num % 2;
	    *buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
	}
	else if (fabs(blockArray) >= 256 && fabs(blockArray) < 512)
	{
	    int rest_buf_num = 0;//range값을 찾기위한 변수
	    int buf_num = fabs(blockArray) - 256;//range값을 찾기위한 변수
	    buf_entropy[*buf_cnt] = 1;//code word
	    *buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
	    buf_entropy[*buf_cnt] = 1;//code word
	    *buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
	    
	    buf_entropy[*buf_cnt] = 1;//code word
	    *buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
	    buf_entropy[*buf_cnt] = 1;//code word
	    *buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
	    buf_entropy[*buf_cnt] = 1;//code word
	    *buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
	    buf_entropy[*buf_cnt] = 1;//code word
	    *buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
	    buf_entropy[*buf_cnt] = 0;//code word
	    *buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
	    if (blockArray < 0)////sign
	    {
	    	buf_entropy[*buf_cnt] = 0;
	    	*buf_cnt += 1;
			if (*buf_cnt == 8)
			{
				write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
			}
	    }
	    else
	    {
	    	buf_entropy[*buf_cnt] = 1;
	    	*buf_cnt += 1;
			if (*buf_cnt == 8)
			{
				write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
			}
	    }
	    buf_entropy[*buf_cnt] = buf_num / 128;//Range 계산
	    rest_buf_num = buf_num % 128;
	    *buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
	    buf_entropy[*buf_cnt] = rest_buf_num / 64;//Range 계산
	    rest_buf_num = rest_buf_num % 64;
	    *buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
	    buf_entropy[*buf_cnt] = rest_buf_num / 32;//Range 계산
	    rest_buf_num = rest_buf_num % 32;
	    *buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
	    buf_entropy[*buf_cnt] = rest_buf_num / 16;
	    rest_buf_num = rest_buf_num % 16;
	    *buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
	    buf_entropy[*buf_cnt] = rest_buf_num / 8;
	    rest_buf_num = rest_buf_num % 8;
	    *buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
	    buf_entropy[*buf_cnt] = rest_buf_num / 4;
	    rest_buf_num = rest_buf_num % 4;
	    *buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
	    buf_entropy[*buf_cnt] = rest_buf_num / 2;
	    *buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
	    
	    buf_entropy[*buf_cnt] = rest_buf_num % 2;
	    *buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
	}
	else if (fabs(blockArray) >= 512 && fabs(blockArray) < 1024)
	{
	    int rest_buf_num = 0;//range값을 찾기위한 변수
	    int buf_num = fabs(blockArray) - 512;//range값을 찾기위한 변수
	    buf_entropy[*buf_cnt] = 1;//code word
	    *buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
	    buf_entropy[*buf_cnt] = 1;//code word
	    *buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
	    
	    buf_entropy[*buf_cnt] = 1;//code word
	    *buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
	    buf_entropy[*buf_cnt] = 1;//code word
	    *buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
	    buf_entropy[*buf_cnt] = 1;//code word
	    *buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
	    buf_entropy[*buf_cnt] = 1;//code word
	    *buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
		buf_entropy[*buf_cnt] = 1;//code word
		*buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
	    buf_entropy[*buf_cnt] = 0;//code word
	    *buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
	    if (blockArray < 0)////sign
	    {
	    	buf_entropy[*buf_cnt] = 0;
	    	*buf_cnt += 1;
			if (*buf_cnt == 8)
			{
				write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
			}
	    }
	    else
	    {
	    	buf_entropy[*buf_cnt] = 1;
	    	*buf_cnt += 1;
			if (*buf_cnt == 8)
			{
				write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
			}
	    }
	    buf_entropy[*buf_cnt] = buf_num / 256;//Range 계산
	    rest_buf_num = buf_num % 256;
	    *buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
		buf_entropy[*buf_cnt] = rest_buf_num / 128;//Range 계산
		rest_buf_num = rest_buf_num % 128;
		*buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
	    buf_entropy[*buf_cnt] = rest_buf_num / 64;//Range 계산
	    rest_buf_num = rest_buf_num % 64;
	    *buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
	    buf_entropy[*buf_cnt] = rest_buf_num / 32;//Range 계산
	    rest_buf_num = rest_buf_num % 32;
	    *buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
	    buf_entropy[*buf_cnt] = rest_buf_num / 16;
	    rest_buf_num = rest_buf_num % 16;
	    *buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
	    buf_entropy[*buf_cnt] = rest_buf_num / 8;
	    rest_buf_num = rest_buf_num % 8;
	    *buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
	    buf_entropy[*buf_cnt] = rest_buf_num / 4;
	    rest_buf_num = rest_buf_num % 4;
	    *buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
	    buf_entropy[*buf_cnt] = rest_buf_num / 2;
	    *buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
	    
	    buf_entropy[*buf_cnt] = rest_buf_num % 2;
	    *buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
	}
	else
	{
	    int rest_buf_num = 0;//range값을 찾기위한 변수
	    int buf_num = fabs(blockArray) - 1024;//range값을 찾기위한 변수
	    buf_entropy[*buf_cnt] = 1;//code word
	    *buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
	    buf_entropy[*buf_cnt] = 1;//code word
	    *buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
	    
	    buf_entropy[*buf_cnt] = 1;//code word
	    *buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
	    buf_entropy[*buf_cnt] = 1;//code word
	    *buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
	    buf_entropy[*buf_cnt] = 1;//code word
	    *buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
	    buf_entropy[*buf_cnt] = 1;//code word
	    *buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
	    buf_entropy[*buf_cnt] = 1;//code word
	    *buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
	    buf_entropy[*buf_cnt] = 1;//code word
	    *buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
	    buf_entropy[*buf_cnt] = 0;//code word
	    *buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
	    if (blockArray < 0)////sign
	    {
	    	buf_entropy[*buf_cnt] = 0;
	    	*buf_cnt += 1;
			if (*buf_cnt == 8)
			{
				write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
			}
	    }
	    else
	    {
	    	buf_entropy[*buf_cnt] = 1;
	    	*buf_cnt += 1;
			if (*buf_cnt == 8)
			{
				write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
			}
	    }
	    buf_entropy[*buf_cnt] = buf_num / 512;//Range 계산
	    rest_buf_num = buf_num % 512;
	    *buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
	    buf_entropy[*buf_cnt] = rest_buf_num / 256;//Range 계산
	    rest_buf_num = rest_buf_num % 256;
	    *buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
	    buf_entropy[*buf_cnt] = rest_buf_num / 128;//Range 계산
	    rest_buf_num = rest_buf_num % 128;
	    *buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
	    buf_entropy[*buf_cnt] = rest_buf_num / 64;//Range 계산
	    rest_buf_num = rest_buf_num % 64;
	    *buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
	    buf_entropy[*buf_cnt] = rest_buf_num / 32;//Range 계산
	    rest_buf_num = rest_buf_num % 32;
	    *buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
	    buf_entropy[*buf_cnt] = rest_buf_num / 16;
	    rest_buf_num = rest_buf_num % 16;
	    *buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
	    buf_entropy[*buf_cnt] = rest_buf_num / 8;
	    rest_buf_num = rest_buf_num % 8;
	    *buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
	    buf_entropy[*buf_cnt] = rest_buf_num / 4;
	    rest_buf_num = rest_buf_num % 4;
	    *buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
	    buf_entropy[*buf_cnt] = rest_buf_num / 2;
	    *buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
	    
	    buf_entropy[*buf_cnt] = rest_buf_num % 2;
	    *buf_cnt += 1;
		if (*buf_cnt == 8)
		{
			write_entropy(buf_cnt, buf_write, buf_entropy, Compression_File);
		}
	}
   
}
void i_Conversion_entropy(int* ientropy_buf_cnt, double* blockArray, unsigned char* buf_write, int* buf_entropy, FILE* Comp_read_File)
{
	*blockArray = 0;
	int sign = 0;
	
	if (buf_entropy[*ientropy_buf_cnt] == 0)
	{
		
		*ientropy_buf_cnt += 1;
		if (*ientropy_buf_cnt ==8)
		{
			com_read_data(ientropy_buf_cnt, buf_write, buf_entropy, Comp_read_File);
		}
		if (buf_entropy[*ientropy_buf_cnt] == 0)//category 0
		{
			*blockArray = 0;
			*ientropy_buf_cnt += 1;//마지막이 맞는거 같은디
			if (*ientropy_buf_cnt == 8)
			{
				com_read_data(ientropy_buf_cnt, buf_write, buf_entropy, Comp_read_File);
			}

		}
		else//category 1~2
		{
			
			*ientropy_buf_cnt += 1;//마지막이 맞는거 같은디
			if (*ientropy_buf_cnt == 8)
			{
				com_read_data(ientropy_buf_cnt, buf_write, buf_entropy, Comp_read_File);
			}
			if (buf_entropy[*ientropy_buf_cnt] == 0)//category 1
			{

				*blockArray = 1;
				*ientropy_buf_cnt += 1;
				if (*ientropy_buf_cnt == 8)
				{
					com_read_data(ientropy_buf_cnt, buf_write, buf_entropy, Comp_read_File);
				}
				if (buf_entropy[*ientropy_buf_cnt] == 0)
				{
					sign = -1;
					*ientropy_buf_cnt += 1;
					if (*ientropy_buf_cnt == 8)
					{
						com_read_data(ientropy_buf_cnt, buf_write, buf_entropy, Comp_read_File);
					}
				}
				else
				{
					sign = 1;
					*ientropy_buf_cnt += 1;
					if (*ientropy_buf_cnt == 8)
					{
						com_read_data(ientropy_buf_cnt, buf_write, buf_entropy, Comp_read_File);
					}
				}

				*blockArray = (*blockArray * sign);

			}
			else//category 2
			{

				*blockArray = 2;
				*ientropy_buf_cnt += 1;
				if (*ientropy_buf_cnt == 8)
				{
					com_read_data(ientropy_buf_cnt, buf_write, buf_entropy, Comp_read_File);
				}
				if (buf_entropy[*ientropy_buf_cnt] == 0)
				{
					sign = -1;
					*ientropy_buf_cnt += 1;
					if (*ientropy_buf_cnt == 8)
					{
						com_read_data(ientropy_buf_cnt, buf_write, buf_entropy, Comp_read_File);
					}
				}
				else
				{
					sign = 1;
					*ientropy_buf_cnt += 1;
					if (*ientropy_buf_cnt == 8)
					{
						com_read_data(ientropy_buf_cnt, buf_write, buf_entropy, Comp_read_File);
					}
				}

				*blockArray = (*blockArray + buf_entropy[*ientropy_buf_cnt]) * sign;//2~3 정하기
				
				*ientropy_buf_cnt += 1;
				if (*ientropy_buf_cnt == 8)
				{
					com_read_data(ientropy_buf_cnt, buf_write, buf_entropy, Comp_read_File);
				}


			}
		}

	}
	else//3번 category 이상
	{
		*ientropy_buf_cnt += 1;
		if (*ientropy_buf_cnt == 8)
		{
			com_read_data(ientropy_buf_cnt, buf_write, buf_entropy, Comp_read_File);
		}
		if (buf_entropy[*ientropy_buf_cnt] == 0)//3~4 category
		{
			*ientropy_buf_cnt += 1;
			if (*ientropy_buf_cnt == 8)
			{
				com_read_data(ientropy_buf_cnt, buf_write, buf_entropy, Comp_read_File);
			}
			if (buf_entropy[*ientropy_buf_cnt] == 0)//3
			{
				*blockArray = 4;
				*ientropy_buf_cnt += 1;
				if (*ientropy_buf_cnt == 8)
				{
					com_read_data(ientropy_buf_cnt, buf_write, buf_entropy, Comp_read_File);
				}
				if (buf_entropy[*ientropy_buf_cnt] == 0)
				{
					sign = -1;
					*ientropy_buf_cnt += 1;
					if (*ientropy_buf_cnt == 8)
					{
						com_read_data(ientropy_buf_cnt, buf_write, buf_entropy, Comp_read_File);
					}
				}
				else
				{
					sign = 1;
					*ientropy_buf_cnt += 1;
					if (*ientropy_buf_cnt == 8)
					{
						com_read_data(ientropy_buf_cnt, buf_write, buf_entropy, Comp_read_File);
					}
				}
				for (int i = 1;i > 0;i--)
				{
					*blockArray = (*blockArray + buf_entropy[*ientropy_buf_cnt]* pow(2, i)) ;//2~3 정하기
					*ientropy_buf_cnt += 1;
					if (*ientropy_buf_cnt == 8)
					{
						com_read_data(ientropy_buf_cnt, buf_write, buf_entropy, Comp_read_File);
					}
				}

				*blockArray = *blockArray * sign;//부호 곱해주기
			}
			else//4 101x000
			{
			
				*blockArray = 8;
				*ientropy_buf_cnt += 1;
				if (*ientropy_buf_cnt == 8)
				{
					com_read_data(ientropy_buf_cnt, buf_write, buf_entropy, Comp_read_File);
				}
				
				if (buf_entropy[*ientropy_buf_cnt] == 0)
				{
					sign = -1;
					*ientropy_buf_cnt += 1;
					if (*ientropy_buf_cnt == 8)
					{
						com_read_data(ientropy_buf_cnt, buf_write, buf_entropy, Comp_read_File);
					}
				}
				else
				{
					sign = 1;
					*ientropy_buf_cnt += 1;
					if (*ientropy_buf_cnt == 8)
					{
						com_read_data(ientropy_buf_cnt, buf_write, buf_entropy, Comp_read_File);
					}
				}
				
				for (int j = 2;j >=0 ;j--)
				{
					*blockArray = (*blockArray + buf_entropy[*ientropy_buf_cnt] * pow(2, j));//2~3 정하기
					*ientropy_buf_cnt += 1;
					if (*ientropy_buf_cnt == 8)
					{
						com_read_data(ientropy_buf_cnt, buf_write, buf_entropy, Comp_read_File);
					}
				}
				
				*blockArray = *blockArray * sign;
			}

		}
	    else//5번 이상
	    {
		    
		     *ientropy_buf_cnt += 1;
			 if (*ientropy_buf_cnt == 8)
			 {
				 com_read_data(ientropy_buf_cnt, buf_write, buf_entropy, Comp_read_File);
			 }
			 if (buf_entropy[*ientropy_buf_cnt] == 0)//5번
			 {
				 *blockArray = 16;
				 *ientropy_buf_cnt += 1;
				 if (*ientropy_buf_cnt == 8)
				 {
					 com_read_data(ientropy_buf_cnt, buf_write, buf_entropy, Comp_read_File);
				 }
				 if (buf_entropy[*ientropy_buf_cnt] == 0)
				 {
					 sign = -1;
					 *ientropy_buf_cnt += 1;
					 if (*ientropy_buf_cnt == 8)
					 {
						 com_read_data(ientropy_buf_cnt, buf_write, buf_entropy, Comp_read_File);
					 }
				 }
				 else
				 {
					 sign = 1;
					 *ientropy_buf_cnt += 1;
					 if (*ientropy_buf_cnt == 8)
					 {
						 com_read_data(ientropy_buf_cnt, buf_write, buf_entropy, Comp_read_File);
					 }
				 }
				 
				 for (int j = 3;j >= 0;j--)
				 {
					 *blockArray = (*blockArray + buf_entropy[*ientropy_buf_cnt] * pow(2, j));//2~3 정하기
					 *ientropy_buf_cnt += 1;
					 
					 if (*ientropy_buf_cnt == 8)
					 {
						 com_read_data(ientropy_buf_cnt, buf_write, buf_entropy, Comp_read_File);
					 }
					 
				 }

				 *blockArray = *blockArray * sign;
			 }
			 else
			 {
				 *ientropy_buf_cnt += 1;
				 if (*ientropy_buf_cnt == 8)
				 {
					 com_read_data(ientropy_buf_cnt, buf_write, buf_entropy, Comp_read_File);
				 }
				 if (buf_entropy[*ientropy_buf_cnt] == 0)//6
				 {
					 *blockArray = 32;
					 *ientropy_buf_cnt += 1;
					 if (*ientropy_buf_cnt == 8)
					 {
						 com_read_data(ientropy_buf_cnt, buf_write, buf_entropy, Comp_read_File);
					 }
					 if (buf_entropy[*ientropy_buf_cnt] == 0)
					 {
						 sign = -1;
						 *ientropy_buf_cnt += 1;
						 if (*ientropy_buf_cnt == 8)
						 {
							 com_read_data(ientropy_buf_cnt, buf_write, buf_entropy, Comp_read_File);
						 }
					 }
					 else
					 {
						 sign = 1;
						 *ientropy_buf_cnt += 1;
						 if (*ientropy_buf_cnt == 8)
						 {
							 com_read_data(ientropy_buf_cnt, buf_write, buf_entropy, Comp_read_File);
						 }
					 }

					 for (int j = 4;j >= 0;j--)
					 {
						 *blockArray = (*blockArray + buf_entropy[*ientropy_buf_cnt] * pow(2, j));//2~3 정하기
						 *ientropy_buf_cnt += 1;
						 if (*ientropy_buf_cnt == 8)
						 {
							 com_read_data(ientropy_buf_cnt, buf_write, buf_entropy, Comp_read_File);
						 }
					 }

					 *blockArray = *blockArray * sign;
				 }
				 else
				 {
					 *ientropy_buf_cnt += 1;
					 if (*ientropy_buf_cnt == 8)
					 {
						 com_read_data(ientropy_buf_cnt, buf_write, buf_entropy, Comp_read_File);
					 }
					 if (buf_entropy[*ientropy_buf_cnt] == 0)//7
					 {
						 *blockArray = 64;
						 *ientropy_buf_cnt += 1;
						 if (*ientropy_buf_cnt == 8)
						 {
							 com_read_data(ientropy_buf_cnt, buf_write, buf_entropy, Comp_read_File);
						 }
						 if (buf_entropy[*ientropy_buf_cnt] == 0)
						 {
							 sign = -1;
							 *ientropy_buf_cnt += 1;
							 if (*ientropy_buf_cnt == 8)
							 {
								 com_read_data(ientropy_buf_cnt, buf_write, buf_entropy, Comp_read_File);
							 }
						 }
						 else
						 {
							 sign = 1;
							 *ientropy_buf_cnt += 1;
							 if (*ientropy_buf_cnt == 8)
							 {
								 com_read_data(ientropy_buf_cnt, buf_write, buf_entropy, Comp_read_File);
							 }
						 }

						 for (int j = 5;j >= 0;j--)
						 {
							 *blockArray = (*blockArray + buf_entropy[*ientropy_buf_cnt] * pow(2, j));//2~3 정하기
							 *ientropy_buf_cnt += 1;
							 if (*ientropy_buf_cnt == 8)
							 {
								 com_read_data(ientropy_buf_cnt, buf_write, buf_entropy, Comp_read_File);
							 }
						 }

						 *blockArray = *blockArray * sign;
					 }
					 else
					 {
						 *ientropy_buf_cnt += 1;
						 if (*ientropy_buf_cnt == 8)
						 {
							 com_read_data(ientropy_buf_cnt, buf_write, buf_entropy, Comp_read_File);
						 }
						 if (buf_entropy[*ientropy_buf_cnt] == 0)//8
						 {
							 *blockArray = 128;
							 *ientropy_buf_cnt += 1;
							 if (*ientropy_buf_cnt == 8)
							 {
								 com_read_data(ientropy_buf_cnt, buf_write, buf_entropy, Comp_read_File);
							 }
							 if (buf_entropy[*ientropy_buf_cnt] == 0)
							 {
								 sign = -1;
								 *ientropy_buf_cnt += 1;
								 if (*ientropy_buf_cnt == 8)
								 {
									 com_read_data(ientropy_buf_cnt, buf_write, buf_entropy, Comp_read_File);
								 }
							 }
							 else
							 {
								 sign = 1;
								 *ientropy_buf_cnt += 1;
								 if (*ientropy_buf_cnt == 8)
								 {
									 com_read_data(ientropy_buf_cnt, buf_write, buf_entropy, Comp_read_File);
								 }
							 }

							 for (int j = 6;j >= 0;j--)
							 {
								 *blockArray = (*blockArray + buf_entropy[*ientropy_buf_cnt] * pow(2, j));//2~3 정하기
								 *ientropy_buf_cnt += 1;
								 if (*ientropy_buf_cnt == 8)
								 {
									 com_read_data(ientropy_buf_cnt, buf_write, buf_entropy, Comp_read_File);
								 }
							 }

							 *blockArray = *blockArray * sign;
						 }
						 else
						 {
							 *ientropy_buf_cnt += 1;
							 if (*ientropy_buf_cnt == 8)
							 {
								 com_read_data(ientropy_buf_cnt, buf_write, buf_entropy, Comp_read_File);
							 }
							 if (buf_entropy[*ientropy_buf_cnt] == 0)//9
							 {
								 *blockArray = 256;
								 *ientropy_buf_cnt += 1;
								 if (*ientropy_buf_cnt == 8)
								 {
									 com_read_data(ientropy_buf_cnt, buf_write, buf_entropy, Comp_read_File);
								 }
								 if (buf_entropy[*ientropy_buf_cnt] == 0)
								 {
									 sign = -1;
									 *ientropy_buf_cnt += 1;
									 if (*ientropy_buf_cnt == 8)
									 {
										 com_read_data(ientropy_buf_cnt, buf_write, buf_entropy, Comp_read_File);
									 }
								 }
								 else
								 {
									 sign = 1;
									 *ientropy_buf_cnt += 1;
									 if (*ientropy_buf_cnt == 8)
									 {
										 com_read_data(ientropy_buf_cnt, buf_write, buf_entropy, Comp_read_File);
									 }
								 }

								 for (int j = 7;j >= 0;j--)
								 {
									 *blockArray = (*blockArray + buf_entropy[*ientropy_buf_cnt] * pow(2, j));//2~3 정하기
									 *ientropy_buf_cnt += 1;
									 if (*ientropy_buf_cnt == 8)
									 {
										 com_read_data(ientropy_buf_cnt, buf_write, buf_entropy, Comp_read_File);
									 }
								 }

								 *blockArray = *blockArray * sign;
							 }
							 else
							 {
								
								 *ientropy_buf_cnt += 1;
								 if (*ientropy_buf_cnt == 8)
								 {
									 com_read_data(ientropy_buf_cnt, buf_write, buf_entropy, Comp_read_File);
								 }
								 if (buf_entropy[*ientropy_buf_cnt] == 0)//10
								 {
									 *blockArray = 512;
									 *ientropy_buf_cnt += 1;
									 if (*ientropy_buf_cnt == 8)
									 {
										 com_read_data(ientropy_buf_cnt, buf_write, buf_entropy, Comp_read_File);
									 }
									 if (buf_entropy[*ientropy_buf_cnt] == 0)
									 {
										 sign = -1;
										 *ientropy_buf_cnt += 1;
										 if (*ientropy_buf_cnt == 8)
										 {
											 com_read_data(ientropy_buf_cnt, buf_write, buf_entropy, Comp_read_File);
										 }
									 }
									 else
									 {
										 sign = 1;
										 *ientropy_buf_cnt += 1;
										 if (*ientropy_buf_cnt == 8)
										 {
											 com_read_data(ientropy_buf_cnt, buf_write, buf_entropy, Comp_read_File);
										 }
									 }

									 for (int j = 8;j >= 0;j--)
									 {
										 *blockArray = (*blockArray + buf_entropy[*ientropy_buf_cnt] * pow(2, j));//2~3 정하기
										 *ientropy_buf_cnt += 1;
										 if (*ientropy_buf_cnt == 8)
										 {
											 com_read_data(ientropy_buf_cnt, buf_write, buf_entropy, Comp_read_File);
										 }
									 }

									 *blockArray = *blockArray * sign;
								 }
								 else//11
								 {
									 
									 
									 *ientropy_buf_cnt += 1;
									 if (*ientropy_buf_cnt == 8)
									 {
										 com_read_data(ientropy_buf_cnt, buf_write, buf_entropy, Comp_read_File);
									 }
									 if(buf_entropy[*ientropy_buf_cnt] == 0)
									 {
										 *blockArray = 1024;
										 *ientropy_buf_cnt += 1;
									       if (buf_entropy[*ientropy_buf_cnt] == 0)
									       {
									  	     sign = -1;
									  	     *ientropy_buf_cnt += 1;
											 if (*ientropy_buf_cnt == 8)
											 {
												 com_read_data(ientropy_buf_cnt, buf_write, buf_entropy, Comp_read_File);
											 }
									       }
									       else
									       {
									  	     sign = 1;
									  	     *ientropy_buf_cnt += 1;
											 if (*ientropy_buf_cnt == 8)
											 {
												 com_read_data(ientropy_buf_cnt, buf_write, buf_entropy, Comp_read_File);
											 }
									       }
									      
									       for (int j = 9;j >= 0;j--)
									       {
									       
									  	     *blockArray = (*blockArray + buf_entropy[*ientropy_buf_cnt] * pow(2, j));//2~3 정하기
									  	     *ientropy_buf_cnt += 1;
											 if (*ientropy_buf_cnt == 8)
											 {
												 com_read_data(ientropy_buf_cnt, buf_write, buf_entropy, Comp_read_File);
											 }
									       }
									       
									       *blockArray = *blockArray * sign;
									 }
								 }
							 }
						 }
					 }
				 }

			 }

	    }

	}
	
}

void intra_entropy(int* entropy_buf_cnt, int* buf_entropy, unsigned char* buf_write,int mode_num,int* intra_flag, int* intra_modenum_flag,FILE* Comp_write_File)
{
	
		buf_entropy[*entropy_buf_cnt] = intra_flag[mode_num - 1];//intra 플래그 넣기
		*entropy_buf_cnt += 1;
		if (*entropy_buf_cnt == 8)
		{
			write_entropy(entropy_buf_cnt, buf_write, buf_entropy, Comp_write_File);
		}
		if (intra_flag[mode_num - 1] == 1)
		{
			buf_entropy[*entropy_buf_cnt] = intra_modenum_flag[mode_num - 1];//intra 플래그 모드 넣기
			*entropy_buf_cnt += 1;
			if (*entropy_buf_cnt == 8)
			{
				write_entropy(entropy_buf_cnt, buf_write, buf_entropy, Comp_write_File);
			}
		}
	
}
void inter_entropy(int* entropy_buf_cnt, int* buf_entropy, unsigned char* buf_write,double mv_x, double mv_y,FILE* Comp_write_File)
{
	Conversion_entropy(entropy_buf_cnt, mv_x, buf_write, buf_entropy, Comp_write_File);//mvx 넣어주기
	
	Conversion_entropy(entropy_buf_cnt, mv_y, buf_write, buf_entropy, Comp_write_File);//mvx넣어주기

}
void encoder_entropy(int* entropy_buf_cnt, int* buf_entropy, unsigned char* buf_write,double* blockArray, int Ac_Flag, int b_width, int b_heigte, FILE* Comp_write_File)
{
	Conversion_entropy(entropy_buf_cnt, blockArray[0], buf_write, buf_entropy, Comp_write_File);//dc넣기

	buf_entropy[*entropy_buf_cnt] = Ac_Flag;//ac플래그 넣기
	
	*entropy_buf_cnt += 1;

	if (*entropy_buf_cnt == 8)
	{
		write_entropy(entropy_buf_cnt, buf_write, buf_entropy, Comp_write_File);
	}

	if (Ac_Flag == 0)//Ac_Flag 0일경우
	{
		for (int i = 1;i < b_width * b_heigte;i++)
		{

			Conversion_entropy(entropy_buf_cnt, blockArray[i], buf_write, buf_entropy, Comp_write_File);//ac 넣기

		}
	}

}
void cbcr_intra_inter_entropy(int* entropy_buf_cnt, int* buf_entropy, unsigned char* buf_write, double* blockArray, int Ac_Flag, int b_width, int b_heigte, FILE* Comp_write_File)
{
	Conversion_entropy(entropy_buf_cnt, blockArray[0], buf_write, buf_entropy, Comp_write_File);//dc넣기
	
	buf_entropy[*entropy_buf_cnt] = Ac_Flag;//ac플래그 넣기
	*entropy_buf_cnt += 1;
	if (*entropy_buf_cnt == 8)
	{
		write_entropy(entropy_buf_cnt, buf_write, buf_entropy, Comp_write_File);
	}
	if (Ac_Flag == 0)//Ac_Flag일경우
	{
		for (int i = 1;i < b_width * b_heigte;i++)
		{
			Conversion_entropy(entropy_buf_cnt, blockArray[i], buf_write, buf_entropy, Comp_write_File);//ac 넣기
		}
	}
}

void RE_intra_entropy(int* entropy_buf_cnt, int* buf_entropy, unsigned char* buf_read, int mode_num, int* intra_flag, int* intra_modenum_flag, double* blockArray, int* Ac_Flag, int b_width, int b_heigte, FILE* Comp_read_File)
{

	intra_flag[mode_num] = buf_entropy[*entropy_buf_cnt];//intra 플래그 받아오기
	*entropy_buf_cnt += 1;
	if (*entropy_buf_cnt == 8)
	{
		fread(&buf_read, sizeof(unsigned char), 1, Comp_read_File);
		for (int i = 0; i < 8;i++)//필요
		{
			int a;
			buf_entropy[i] = *buf_read / (128 / pow(2, i));
			a = (128 / pow(2, i));
			*buf_read = *buf_read % a;

		}
		*buf_read = 0;
		*entropy_buf_cnt = 0;
	}
	printf("%d", intra_flag[mode_num]);
	if (intra_flag[mode_num] == 1)
	{
		
		intra_modenum_flag[mode_num - 1] = buf_entropy[*entropy_buf_cnt];//intra 플래그 모드 넣기
		*entropy_buf_cnt += 1;
		if (*entropy_buf_cnt == 8)
		{
			fread(&buf_read, sizeof(unsigned char), 1, Comp_read_File);
			for (int i = 0; i < 8;i++)//필요
			{
				int a;
				buf_entropy[i] = *buf_read / (128 / pow(2, i));
				a = (128 / pow(2, i));
				*buf_read = *buf_read % a;

			}
			*buf_read = 0;
			*entropy_buf_cnt = 0;
		}
	}

	i_Conversion_entropy(entropy_buf_cnt, &blockArray[0], buf_read, buf_entropy, Comp_read_File);//dc넣기

	*Ac_Flag = buf_entropy[*entropy_buf_cnt];//ac플래그 넣기
	*entropy_buf_cnt += 1;
	if (*entropy_buf_cnt == 8)
	{
		fread(&buf_read, sizeof(unsigned char), 1, Comp_read_File);
		for (int i = 0; i < 8;i++)//필요
		{
			int a;
			buf_entropy[i] = *buf_read / (128 / pow(2, i));
			a = (128 / pow(2, i));
			*buf_read = *buf_read % a;

		}
		*buf_read = 0;
		*entropy_buf_cnt = 0;
	}
	if (Ac_Flag == 0)//Ac_Flag일경우
	{
		for (int i = 1;i < b_width * b_heigte;i++)
		{
			Conversion_entropy(entropy_buf_cnt, blockArray[i], buf_read, buf_entropy, Comp_read_File);//ac 넣기
		}
	}
	else
	{
		for (int i = 1;i < b_width * b_heigte;i++)
		{
			blockArray[i] = 0;
		}
	}

}
void RE_inter_entropy(int* entropy_buf_cnt, int* buf_entropy, unsigned char* buf_read, double* mv_x, double* mv_y, double* blockArray, int* Ac_Flag, int b_width, int b_heigte, FILE* Comp_read_File)
{
	i_Conversion_entropy(entropy_buf_cnt, mv_x, buf_read, buf_entropy, Comp_read_File);//mv x

	i_Conversion_entropy(entropy_buf_cnt, mv_y, buf_read, buf_entropy, Comp_read_File);//mv y
	i_Conversion_entropy(entropy_buf_cnt, &blockArray[0], buf_read, buf_entropy, Comp_read_File);//dc
	*Ac_Flag = buf_entropy[*entropy_buf_cnt];//ac플래그 넣기
	*entropy_buf_cnt += 1;
	if (*entropy_buf_cnt == 8)
	{
		fread(&buf_read, sizeof(unsigned char), 1, Comp_read_File);
		for (int i = 0; i < 8;i++)//필요
		{
			int a;
			buf_entropy[i] = *buf_read / (128 / pow(2, i));
			a = (128 / pow(2, i));
			*buf_read = *buf_read % a;

		}
		*buf_read = 0;
		*entropy_buf_cnt = 0;
	}
	if (Ac_Flag == 0)//Ac_Flag일경우
	{
		for (int i = 1;i < b_width * b_heigte;i++)
		{
			Conversion_entropy(entropy_buf_cnt, blockArray[i], buf_read, buf_entropy, Comp_read_File);//ac 넣기
		}
	}
	else
	{
		for (int i = 1;i < b_width * b_heigte;i++)
		{
			blockArray[i] = 0;
		}
	}

}

void RE_cbcr_intra_inter_entropy(int* entropy_buf_cnt, int* buf_entropy, unsigned char* buf_read, double* blockArray, int* Ac_Flag, int b_width, int b_heigte, FILE* Comp_read_File)
{
	i_Conversion_entropy(entropy_buf_cnt, &blockArray[0], buf_read, buf_entropy, Comp_read_File);//dc

	*Ac_Flag = buf_entropy[*entropy_buf_cnt];//ac플래그 넣기
	*entropy_buf_cnt += 1;
	if (*entropy_buf_cnt == 8)
	{
		fread(&buf_read, sizeof(unsigned char), 1, Comp_read_File);
		for (int i = 0; i < 8;i++)//필요
		{
			int a;
			buf_entropy[i] = *buf_read / (128 / pow(2, i));
			a = (128 / pow(2, i));
			*buf_read = *buf_read % a;

		}
		*buf_read = 0;
		*entropy_buf_cnt = 0;
	}
	if (Ac_Flag == 0)//Ac_Flag일경우
	{
		for (int i = 1;i < b_width * b_heigte;i++)
		{
			Conversion_entropy(entropy_buf_cnt, blockArray[i], buf_read, buf_entropy, Comp_read_File);//ac 넣기
		}
	}
	else
	{
		for (int i = 1;i < b_width * b_heigte;i++)
		{
			blockArray[i] = 0;
		}
	}
}
int ddmain()
{
	/*
	FILE* Compression_File = NULL;
	Compression_File = fopen("TEST1.YUV", "wb");

	if (Compression_File == NULL)
	{
		fputs("File error", stderr);
		exit(1);
	}

	int entropy_buf_cnt = 0;
	int ientropy_buf_cnt = 0;
	int buf_entropy[8];
	unsigned char buf_write = 0;
	double blockArray[64] = { 0, };
	
	unsigned char buf_write2 = 0;
	
	blockArray[0] = -20;
	blockArray[1] = 100;
	blockArray[2] =500;
	blockArray[3] = -1742;
	// category 4 까지 완료


	
	dc_entropy(&entropy_buf_cnt, blockArray[0], &buf_write, buf_entropy, Compression_File);
	dc_entropy(&entropy_buf_cnt, blockArray[1], &buf_write, buf_entropy, Compression_File);
	dc_entropy(&entropy_buf_cnt, blockArray[2], &buf_write, buf_entropy, Compression_File);
	dc_entropy(&entropy_buf_cnt, blockArray[3], &buf_write, buf_entropy, Compression_File);
	dc_entropy(&entropy_buf_cnt, blockArray[3], &buf_write, buf_entropy, Compression_File);
	dc_entropy(&entropy_buf_cnt, blockArray[3], &buf_write, buf_entropy, Compression_File);
	dc_entropy(&entropy_buf_cnt, blockArray[3], &buf_write, buf_entropy, Compression_File);
	
	fclose(Compression_File);
	
	blockArray[0] = 0;
	blockArray[1] = 0;
	blockArray[2] = 0;
	blockArray[3] = 0;

	FILE* Comp_read_File = NULL;
	Comp_read_File = fopen("TEST1.YUV", "rb");//명칭 다르게 실행 왜냐하면 파일 자체 읽는 위치가 바뀌기 떄문에//읽거나 쓰는 위치 공유
	if (Comp_read_File == NULL)
	{
		fputs("File error", stderr);
		exit(1);
	}
	fread(&buf_write, sizeof(unsigned char), 1, Comp_read_File);// 이거실행하고 실행
	
	for (int i = 0; i < 8;i++)//필요
	{
		int a;
		buf_entropy[i] = buf_write / (128 / pow(2, i));
		a = (128 / pow(2, i));
		buf_write = buf_write %a;
		//printf("%d ", buf_entropy[i]);
	}
	//printf("\n");


	idc_entropy(&ientropy_buf_cnt, &blockArray[0], &buf_write, buf_entropy, Comp_read_File);	
	idc_entropy(&ientropy_buf_cnt, &blockArray[1], &buf_write, buf_entropy, Comp_read_File);
	idc_entropy(&ientropy_buf_cnt, &blockArray[2], &buf_write, buf_entropy, Comp_read_File);
	idc_entropy(&ientropy_buf_cnt, &blockArray[3], &buf_write, buf_entropy, Comp_read_File);
	printf("  %lf ", blockArray[0]);
	printf("%lf ", blockArray[1]);
	printf("%lf ", blockArray[2]);
	printf("%lf ", blockArray[3]);
	

	fclose(Comp_read_File);

	return 0;
	*/
	return 0;
}