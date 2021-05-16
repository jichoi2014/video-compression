#include "buffer.h"

void stream_header(int DCQP, int ACQP, FILE* Comp_write_File, int intre_period,int intra_prediction)
{
	unsigned char buf_stream[8] = { 0 , };
	int buf_stream_cnt = 0;
	int buf_num = 0;
	unsigned char stream_write = 0;
	unsigned char QP_DC = DCQP;
	unsigned char QP_AC = ACQP;
	char icsp = NULL;
	int img_width = WIDTH;
	int img_height = HEIGHT;
	fwrite(&stream_write, sizeof(unsigned char), 1, Comp_write_File);//0�ֱ�
	printf("����� : %d\n", stream_write);

	icsp = 'I';
	fwrite(&icsp, sizeof(char), 1, Comp_write_File);
	printf("I : %d\n", icsp);
	icsp = 'C';
	fwrite(&icsp, sizeof(char), 1, Comp_write_File);
	printf("C : %d\n", icsp);
	icsp = 'S';
	fwrite(&icsp, sizeof(char), 1, Comp_write_File);
	printf("S : %d\n", icsp);
	icsp = 'P';
	fwrite(&icsp, sizeof(char), 1, Comp_write_File);
	printf("P : %d\n", icsp);
	
	for (int i = 15;i >= 0;i--)
	{
		int a = pow(2, i);
		buf_stream[buf_stream_cnt] = img_width / a;//WIDTH
		img_width =img_width % a;
		buf_stream_cnt++;
		
		if (buf_stream_cnt == 8)
		{
			for (int i = 0; i < 8;i++)
			{
				stream_write += buf_stream[i] * (128 / pow(2, i));
				
			}
			fwrite(&stream_write, sizeof(unsigned char), 1, Comp_write_File);
			
			printf("WIDTH : %d\n", stream_write);
			stream_write = 0;
			buf_stream_cnt = 0;
		}
	}
	for (int i = 15;i >= 0;i--)
	{
		int a = pow(2, i);
		buf_stream[buf_stream_cnt] = img_height / a;//height
		img_height = img_height % a;
		buf_stream_cnt++;
		if (buf_stream_cnt == 8)
		{
			for (int i = 0; i < 8;i++)
			{
				stream_write += buf_stream[i] * (128 / pow(2, i));
			}
			fwrite(&stream_write, sizeof(unsigned char), 1, Comp_write_File);
			printf("HEIGHT : %d\n", stream_write);
			stream_write = 0;
			buf_stream_cnt = 0;
		}
	}

	fwrite(&QP_DC, sizeof(unsigned char), 1, Comp_write_File);
	printf("DC QP : %d\n", QP_DC);
	fwrite(&QP_AC, sizeof(unsigned char), 1, Comp_write_File);
	printf("AC AP : %d\n", QP_AC);
	
	buf_stream[buf_stream_cnt] = 0;
	buf_stream_cnt++;
	buf_stream[buf_stream_cnt] = 1;
	buf_stream_cnt++;
	buf_stream[buf_stream_cnt] = 1;
	buf_stream_cnt++;
	buf_stream[buf_stream_cnt] = 0;//Pixle DPCM mode 6 ����
	buf_stream_cnt++;
	buf_stream[buf_stream_cnt] = 0;
	buf_stream_cnt++;
	buf_stream[buf_stream_cnt] = 0;
	buf_stream_cnt++;
	buf_stream[buf_stream_cnt] = 0;
	buf_stream_cnt++;
	buf_stream[buf_stream_cnt] = 0;//DC DPCM mode 0 ����
	buf_stream_cnt++;
	
	for (int i = 0; i < 8;i++)
	{
		stream_write += buf_stream[i] * (128 / pow(2, i));
	}
	fwrite(&stream_write, sizeof(unsigned char), 1, Comp_write_File);
	printf("DC,AC DPCM : %d\n", stream_write);
	stream_write = 0;
	buf_stream_cnt = 0;
	
	buf_stream[buf_stream_cnt] = 0;
	buf_stream_cnt++;
	buf_stream[buf_stream_cnt] = 0;
	buf_stream_cnt++;
	buf_stream[buf_stream_cnt] = 0;//mv  perd 0
	buf_stream_cnt++;
	for (int i = 5;i >= 0;i--)
	{
		int a = pow(2, i);
		buf_stream[buf_stream_cnt] = intre_period / a;//period
		intre_period = intre_period % a;
		buf_stream_cnt++;
		if (buf_stream_cnt == 8)
		{
			for (int i = 0; i < 8;i++)
			{
				stream_write += buf_stream[i] * (128 / pow(2, i));
			}
			fwrite(&stream_write, sizeof(unsigned char), 1, Comp_write_File);
			printf("period : %d\n", stream_write);
			stream_write = 0;
			buf_stream_cnt = 0;
		}
    }
	buf_stream[buf_stream_cnt] = 1;//intra prediction
	buf_stream_cnt++;
	for (int i = 0; i < 6;i++)
	{
		buf_stream[buf_stream_cnt] = 0;
		buf_stream_cnt++;
	}
	if (buf_stream_cnt == 8)
	{
		for (int i = 0; i < 8;i++)
		{
			stream_write += buf_stream[i] * (128 / pow(2, i));
		}
		fwrite(&stream_write, sizeof(unsigned char), 1, Comp_write_File);
		printf("intra prediction + ARRAY:%d\n", stream_write);
		stream_write = 0;
		buf_stream_cnt = 0;
	}
}

void read_stream_header(int* DCQP, int* ACQP, FILE* Comp_read_File, int* intre_period, int* intra_prediction, int* pixel_dmpcm, int* dc_dmpcm)
{
	unsigned char buf_stream[8] = { 0 , };
	int buf_stream_cnt = 0;
	int buf_num = 0;
	unsigned char stream_read = 0;
	int mv_pred = 0;
	unsigned char QP_DC = *DCQP;
	unsigned char QP_AC = *ACQP;
	char icsp = NULL;
	int img_width = 0;
	int img_height = 0;
	fread(&stream_read, sizeof(unsigned char), 1, Comp_read_File);//0�ֱ�

	printf("����� : %d   ", stream_read);

	fread(&icsp, sizeof(char), 1, Comp_read_File);//i
	printf("%c", icsp);
	fread(&icsp, sizeof(char), 1, Comp_read_File);//c
	printf("%c", icsp);
	fread(&icsp, sizeof(char), 1, Comp_read_File);//s
	printf("%c", icsp);
	fread(&icsp, sizeof(char), 1, Comp_read_File);//p
	printf("%c", icsp);


	fread(&stream_read, sizeof(unsigned char), 1, Comp_read_File);//width
	img_width += stream_read * (pow(2, 8));
	fread(&stream_read, sizeof(unsigned char), 1, Comp_read_File);//width
	img_width += stream_read;
	printf("   width  %d ", img_width);

	fread(&stream_read, sizeof(unsigned char), 1, Comp_read_File);//heigth
	img_height += stream_read * (pow(2, 8));
	fread(&stream_read, sizeof(unsigned char), 1, Comp_read_File);//heigth
	img_height += stream_read;
	printf("  height  %d ", img_height);


	fread(DCQP, sizeof(unsigned char), 1, Comp_read_File);//DC
	printf(" DCQP %d ", *DCQP);
	fread(ACQP, sizeof(unsigned char), 1, Comp_read_File);//QP
	printf(" ACQP %d ", *ACQP);

	fread(&stream_read, sizeof(unsigned char), 1, Comp_read_File);//PIXEL DPCM 6, DC DPCM 0 
	for (int i = 0;i < 8;i++)
	{
		int a;
		buf_stream[buf_stream_cnt] = stream_read / (128 / pow(2, i));
		a = (128 / pow(2, i));
		stream_read = stream_read % a;
		buf_stream_cnt++;
	}
	buf_stream_cnt = 0;
	for (int i = 3;i >= 0;i--)//pixel_dmpcm
	{
		*pixel_dmpcm += buf_stream[buf_stream_cnt] * pow(2, i);
		buf_stream_cnt++;
	}
	int dcbuf = 0;
	for (int i = 3;i >= 0;i--)//dc_dmpcm
	{
		dcbuf += buf_stream[buf_stream_cnt] * pow(2, i);
		buf_stream_cnt++;
	}
	*dc_dmpcm = dcbuf;

	buf_stream_cnt = 0;
	printf(" pixel DPCM : %d  dc DPCM : %d ", *pixel_dmpcm, *dc_dmpcm);

	fread(&stream_read, sizeof(unsigned char), 1, Comp_read_File);//3��Ʈ�� MV PRED 5��Ʈ��  intra preiod
	for (int i = 0;i < 8;i++)
	{
		int a;
		buf_stream[buf_stream_cnt] = stream_read / (128 / pow(2, i));
		a = (128 / pow(2, i));
		stream_read = stream_read % a;
		buf_stream_cnt++;
	}
	buf_stream_cnt = 0;
	for (int i = 2;i >= 0;i--)//MV PRED
	{
		mv_pred += buf_stream[buf_stream_cnt] * pow(2, i);
		buf_stream_cnt++;

	}
	printf("  mv_pred  %d ", mv_pred);

	for (int i = 5;i >= 0;i--)//intra preiod
	{

		*intre_period += buf_stream[buf_stream_cnt] * pow(2, i);//intra prediction
		buf_stream_cnt++;

		if (buf_stream_cnt == 8)
		{
			fread(&stream_read, sizeof(unsigned char), 1, Comp_read_File);
			for (int i = 0;i < 8;i++)
			{
				int a;
				buf_stream[i] = stream_read / (128 / pow(2, i));
				a = (128 / pow(2, i));
				stream_read = stream_read % a;

			}
			buf_stream_cnt = 0;
		}

	}
	printf(" intre_period : %d ", *intre_period);
	*intra_prediction = buf_stream[buf_stream_cnt];
	printf(" intra_predictio : %d ", *intra_prediction);



}