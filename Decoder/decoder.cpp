#include "buffer.h"

void decoder()
{
	FILE* data_collection_FILE = NULL;

	data_collection_FILE = fopen("data_collection.txt", "w");
	if (data_collection_FILE == NULL)
	{
		fputs("File errorDD", stderr);
		exit(1);
	}

	char read_fil_name_YUV[10] = "_CIF.YUV";
	char read_fil_name_RAW[5] = ".RAW";
	for (int dcqptest = 0;dcqptest < 3;dcqptest++)
	{
		char read_dcqpname[10] = "";


		if (dcqptest == 0)
		{
			
			char dcqpname[5] = ",1";
			strcat(read_dcqpname, dcqpname);
		}
		else if (dcqptest == 1)
		{
			
			char dcqpname[30] = ",8";
			strcat(read_dcqpname, dcqpname);
		}
		else
		{
			
			char dcqpname[30] = ",16";
			strcat(read_dcqpname, dcqpname);
		}
		for (int acqptest = 0;acqptest < 2;acqptest++)
		{
			
			char read_acqpname[30] = "";

			if (acqptest == 0)
			{
				
				char acqpname[30] = ",1";
				strcat(read_acqpname, acqpname);
			}
			else
			{
				
				char acqpname[30] = ",16";
				strcat(read_acqpname, acqpname);
			}
			for (int dc_dmpcm_test = 0;dc_dmpcm_test < 2;dc_dmpcm_test++)
			{
				
				char read_dpcm_name[10] = "";

				if (dc_dmpcm_test == 0)
				{
					
					char acqpname[30] = ",0";
					strcat(read_dpcm_name, acqpname);
				}
				else
				{
					
					char acqpname[30] = ",6";
					strcat(read_dpcm_name, acqpname);
				}
				for (int intra_period_test = 0;intra_period_test < 2;intra_period_test++)
				{

					 // 피리어드값!!!!!!!!!!!!!!!!!!
					char read_period_name[10] = "";
					if (intra_period_test == 0)
					{
						
						char dcqpname[30] = ",0";
						strcat(read_period_name, dcqpname);
					}
					else
					{
						
						char dcqpname[30] = ",10";
						strcat(read_period_name, dcqpname);
					}
					for (int intra_prediction_test = 0;intra_prediction_test < 2;intra_prediction_test++)
					{
						//설정에 따라 인트라 모드 실행 나는 설정 안해줌
						char read_pred_name[10] = "";
						if (intra_prediction_test == 0)
						{
							
							char acqpname[30] = ",0";
							strcat(read_pred_name, acqpname);
						}
						else
						{
							
							char acqpname[30] = ",1";
							strcat(read_pred_name, acqpname);
						}
						char read_fil_name[300] = "FOOT";
						char write_fil_name[300] = "FOOT";
						char data_collection[300]="";
						strcat(read_fil_name, read_dcqpname);
						strcat(read_fil_name, read_acqpname);
						strcat(read_fil_name, read_dpcm_name);
						strcat(read_fil_name, read_period_name);
						strcat(read_fil_name, read_pred_name);
						
						strcat(write_fil_name, read_fil_name);
						
						strcat(data_collection, read_fil_name);
						strcat(read_fil_name, read_fil_name_RAW);
						strcat(write_fil_name, read_fil_name_YUV);

						FILE* READ_FILE = NULL;
						FILE* RESTORED_FILE = NULL;
						FILE* TEST_FILE = NULL;

						READ_FILE = fopen(read_fil_name, "rb");
						RESTORED_FILE = fopen(write_fil_name, "wb");
						TEST_FILE = fopen("football_cif(352X288)_90f.YUV", "rb");
						if (TEST_FILE == NULL)
						{
							fputs("File errorDD", stderr);
							exit(1);
						}

						if (READ_FILE == NULL)
						{
							fputs("File errorAA", stderr);
							exit(1);
						}
						if (RESTORED_FILE == NULL)
						{
							fputs("File errorCC", stderr);
							exit(1);
						}

						unsigned int filesize = 0;
						fseek(READ_FILE, 0, SEEK_END);
						filesize = ftell(READ_FILE);
						fseek(READ_FILE, 0, SEEK_SET);
						double blockArray[64] = { 0, };
						int Zigzag_array[64] = { 0, };
						int CBCR_Zigzag_array[16] = { 0, };
						int nFrameSize = WIDTH * HEIGHT;
						int PaddingFrameSize = PWIDTH * PHEIGHT;
						double CBCRblockArray[16] = { 0, };
						int CBCRZigzag_array[16] = { 0, };
						int CBCRnFrameSize = CBCRWIDTH * CBCRHEIGHT;
						int CBCRPaddingFrameSize = CBCRPWIDTH * CBCRPHEIGHT;

						unsigned char* read_data_origin = (unsigned char*)calloc(nFrameSize, sizeof(unsigned char));
						unsigned char* restored_data = (unsigned char*)calloc(nFrameSize, sizeof(unsigned char));
						unsigned char* buffer_padding = (unsigned char*)calloc(PaddingFrameSize, sizeof(unsigned char));

						double* buffer_decod = (double*)calloc(nFrameSize, sizeof(double));

						unsigned char* cb_read_data_origin = (unsigned char*)calloc(CBCRnFrameSize, sizeof(unsigned char));
						unsigned char* cb_restored_data = (unsigned char*)calloc(CBCRnFrameSize, sizeof(unsigned char));
						unsigned char* cb_buffer_padding = (unsigned char*)calloc(CBCRPaddingFrameSize, sizeof(unsigned char));
						double* cb_buffer_decod = (double*)calloc(CBCRnFrameSize, sizeof(double));
						unsigned char* cr_read_data_origin = (unsigned char*)calloc(CBCRnFrameSize, sizeof(unsigned char));
						unsigned char* cr_restored_data = (unsigned char*)calloc(CBCRnFrameSize, sizeof(unsigned char));
						unsigned char* cr_buffer_padding = (unsigned char*)calloc(CBCRPaddingFrameSize, sizeof(unsigned char));
						double* cr_buffer_decod = (double*)calloc(CBCRnFrameSize, sizeof(double));

						unsigned char* TEST_data = (unsigned char*)calloc(nFrameSize, sizeof(unsigned char));
						unsigned char* cr_TEST_data = (unsigned char*)calloc(CBCRnFrameSize, sizeof(unsigned char));
						unsigned char* cb_TEST_data = (unsigned char*)calloc(CBCRnFrameSize, sizeof(unsigned char));

						int pixel_dmpcm = 0;
						int dc_dmpcm = 2;
						int intra_period = 0; // 피리어드값!!!!!!!!!!!!!!!!!!
						int intra_prediction = 0;
						int DCQP = 0;
						int ACQP = 0;
						int mode_num = 0;
						int cbcr_mode_num = 0;
						int icbcr_mode_num = 0;
						int imode_num = 0;
						int Mv_num = 0;
						int iMv_num = 0;
						int entropy_buf_cnt = 0;
						int ientropy_buf_cnt = 0;
						int buf_entropy[8] = { 0, };
						unsigned char buf_read = 0;
						int mv_flag = 0;

						zig_zag_array(Zigzag_array, BLOCK_W, BLOCK_H);
						zig_zag_array(CBCR_Zigzag_array, CBCRBLOCK_W, CBCRBLOCK_H);

						read_stream_header(&DCQP, &ACQP, READ_FILE, &intra_period, &intra_prediction, &pixel_dmpcm, &dc_dmpcm);//stream header 뽑기
						//printf("dc : %d  ac : %d  period  : %d  pred   : %d\n", DCQP, ACQP,intra_period,intra_prediction);
						//printf("dc DPCM : %d", dc_dmpcm);




						fread(&buf_read, sizeof(unsigned char), 1, READ_FILE);//3비트는 MV PRED 5비트는  intra preiod
						for (int i = 0;i < 8;i++)
						{
							int a;
							buf_entropy[i] = buf_read / (128 / pow(2, i));
							a = (128 / pow(2, i));
							buf_read = buf_read % a;
							//printf("%d", buf_entropy[i]);
						}

						double PSNR = 0;
						double sumPSNR = 0;
						int settell = 0;
						for (int z = 0;settell < filesize;z++, settell = ftell(READ_FILE))
						{
							printf("[ %d frame ] Start!!\n", z + 1);
							mode_num = 0;
							cbcr_mode_num = 0;
							icbcr_mode_num = 0;
							imode_num = 0;
							Mv_num = 0;
							iMv_num = 0;
							double MSE = 0;
							double cb_MSE = 0;
							double cr_MSE = 0;

							double Mv_x_flag[BLOCK_W_NUM * BLOCK_H_NUM] = { 0, };
							double Mv_y_flag[BLOCK_W_NUM * BLOCK_H_NUM] = { 0, };
							int init_fpx_loc[BLOCK_W_NUM * BLOCK_H_NUM] = { 0, };
							int intra_modenum_flag[BLOCK_W_NUM * BLOCK_H_NUM] = { 0, };
							int intra_modenum[BLOCK_W_NUM * BLOCK_H_NUM] = { 0, };
							int intra_modenum1[BLOCK_W_NUM * BLOCK_H_NUM] = { 0, };
							int intra_flag[BLOCK_W_NUM * BLOCK_H_NUM] = { 0, };
							int cbcr_init_pix_loc[BLOCK_W_NUM * BLOCK_H_NUM] = { 0, };


							for (int by = 0; by < (HEIGHT / 8);by++)//블럭화+dct (HEIGHT / 8)
							{
								for (int bx = 0; bx < (WIDTH / 8);bx++)// (WIDTH / 8)
								{
									init_fpx_loc[bx + (BLOCK_W_NUM * by)] = (bx * BLOCK_W) + (by * WIDTH * BLOCK_H);//각 블록의 DC값 넣어주기

									int Ac_Flag = 0;

									if (intra_prediction == 1)
									{
										if (z % (intra_period + 1) == 0)//entropy
										{

											RE_intra_entropy(&entropy_buf_cnt, buf_entropy, &buf_read, imode_num, intra_flag, intra_modenum_flag, READ_FILE, bx, by);
											//printf("\nmpmflag : %d mode :  %d DC :  %lf ACFLAG  :  %d \n", intra_flag[imode_num], intra_modenum_flag[imode_num], blockArray[0], Ac_Flag);

										}
									}

									if (z % (intra_period + 1) != 0)
									{
										if (by == 0 && bx == 0)//mv flag넣어주기
										{
											mv_flag = buf_entropy[entropy_buf_cnt];//mv플래그 넣기
											entropy_buf_cnt += 1;
											if (entropy_buf_cnt == 8)
											{
												com_read_data(&entropy_buf_cnt, &buf_read, buf_entropy, READ_FILE);
											}

										}

										RE_inter_entropy(&entropy_buf_cnt, buf_entropy, &buf_read, &Mv_x_flag[iMv_num], &Mv_y_flag[iMv_num], READ_FILE);
									}

									decoder_entropy(&entropy_buf_cnt, buf_entropy, &buf_read, blockArray, &Ac_Flag, BLOCK_W, BLOCK_W, READ_FILE, bx, by);
									/* if (by == 1 && bx == 22)
									  {
										  printf(" mvx: %lf  mvy : %lf   DC :  %lf ACFLAG  :  %d \n",Mv_x_flag[iMv_num], Mv_y_flag[iMv_num],blockArray[0], Ac_Flag);
										  for (int i = 0;i < 8;i++)
										  {
											  for (int j = 0;j < 8;j++)
											  {
												  printf(" %lf ", blockArray[j + i * 8]);
											  }
											  printf("\n");
										  }
										  printf("\n");
									  }*/

									izig_zag_scan(blockArray, Zigzag_array);

									if (dc_dmpcm == 0)
									{
										idcdpcm(init_fpx_loc[bx + (BLOCK_W_NUM * by)], buffer_decod, blockArray);
									}

									for (int nY = 0;nY < N;nY++)
									{
										for (int nX = 0;nX < N;nX++)
										{
											buffer_decod[(bx * N) + nX + (nY * WIDTH) + (by * N * WIDTH)] = (blockArray[nX + (N * nY)]);
										}

									}
									iQuantization(blockArray, DCQP, ACQP);
									idct(blockArray);



									if (intra_prediction == 1)
									{
										if (z % (intra_period + 1) == 0)
										{
											/*if (by == 0 && bx == 0)
											{
												printf("modenum : %d  mpmflag : %d mode :  %d DC :  %lf ACFLAG  :  %d \n", intra_modenum1[imode_num], intra_flag[imode_num], intra_modenum_flag[imode_num], blockArray[0], Ac_Flag);
												for (int i = 0;i < 8;i++)
												{
													for (int j = 0;j < 8;j++)
													{
														printf(" %lf ", blockArray[j + i * 8]);
													}
													printf("\n");
												}
												printf("\n");
											}*/
											impm_flag(intra_modenum1, intra_flag, intra_modenum_flag, imode_num);

											iintra(intra_modenum1[imode_num], init_fpx_loc[bx + (BLOCK_W_NUM * by)], restored_data, blockArray);
											imode_num++;
										}
									}

									if (z % (intra_period + 1) != 0)
									{
										iinter(init_fpx_loc[bx + (BLOCK_W_NUM * by)], buffer_padding, &Mv_x_flag[iMv_num], &Mv_y_flag[iMv_num], blockArray);
										iMv_num++;
									}

									clipping(blockArray);

									for (int nY = 0;nY < N;nY++)
									{
										for (int nX = 0;nX < N;nX++)
										{
											restored_data[(bx * N) + nX + (nY * WIDTH) + (by * N * WIDTH)] = (unsigned char)(blockArray[nX + (N * nY)]);

										}
									}

								}
							}
							padding(restored_data, buffer_padding);
							fwrite(restored_data, sizeof(unsigned char), nFrameSize, RESTORED_FILE);
							iMv_num = 0;

							for (int by = 0; by < (CBCRHEIGHT / CBCRBLOCK_H);by++)//cb 블럭화+dct
							{
								for (int bx = 0; bx < (CBCRWIDTH / CBCRBLOCK_W);bx++)
								{
									cbcr_init_pix_loc[bx + (BLOCK_W_NUM * by)] = (bx * CBCRBLOCK_W) + (by * CBCRWIDTH * CBCRBLOCK_H);
									int Ac_Flag = 0;
									int cbcr_mv_x = 0;
									int cbcr_mv_y = 0;

									RE_cbcr_intra_inter_entropy(&entropy_buf_cnt, buf_entropy, &buf_read, CBCRblockArray, &Ac_Flag, CBCRBLOCK_W, CBCRBLOCK_H, READ_FILE);

									CBCR_izig_zag_scan(CBCRblockArray, CBCR_Zigzag_array);

									if (dc_dmpcm == 0)
									{
										CBCR_idcdpcm(cbcr_init_pix_loc[bx + (BLOCK_W_NUM * by)], cb_buffer_decod, CBCRblockArray);
									}

									for (int nY = 0;nY < CBCRBLOCK_H;nY++)
									{
										for (int nX = 0;nX < CBCRBLOCK_W;nX++)
										{
											cb_buffer_decod[(bx * CBCRBLOCK_W) + (by * CBCRWIDTH * CBCRBLOCK_H) + nX + (nY * CBCRWIDTH)] = (CBCRblockArray[nX + (CBCRBLOCK_W * nY)]);
										}

									}

									CBCR_iQuantization(CBCRblockArray, DCQP, ACQP);
									CBCR_IDCT(CBCRblockArray);

									if (intra_prediction == 1)
									{
										if (z % (intra_period + 1) == 0)
										{
											icbcr_intra(cbcr_init_pix_loc[bx + (BLOCK_W_NUM * by)], cb_restored_data, CBCRblockArray, intra_modenum1[icbcr_mode_num]);
											icbcr_mode_num++;


										}
									}
									if (z % (intra_period + 1) != 0)
									{
										cbcr_mv_x = Mv_x_flag[iMv_num] / 2;
										cbcr_mv_y = Mv_x_flag[iMv_num] / 2;
										iCBCR_inter(cbcr_init_pix_loc[bx + (BLOCK_W_NUM * by)], cb_buffer_padding, cbcr_mv_x, cbcr_mv_y, cb_restored_data, CBCRblockArray);
										iMv_num++;
									}
									cbcr_clipping(CBCRblockArray);
									for (int nY = 0;nY < CBCRBLOCK_H;nY++)
									{
										for (int nX = 0;nX < CBCRBLOCK_W;nX++)
										{
											cb_restored_data[(bx * CBCRBLOCK_W) + (by * CBCRWIDTH * CBCRBLOCK_H) + nX + (nY * CBCRWIDTH)] = (unsigned char)(CBCRblockArray[nX + (CBCRBLOCK_W * nY)]);
										}
									}


								}
							}

							cb_padding(cb_restored_data, cb_buffer_padding);
							fwrite(cb_restored_data, sizeof(unsigned char), CBCRnFrameSize, RESTORED_FILE);

							Mv_num = 0;
							iMv_num = 0;
							cbcr_mode_num = 0;
							icbcr_mode_num = 0;
							for (int by = 0; by < (CBCRHEIGHT / CBCRBLOCK_H);by++)//cr 블럭화+dct
							{
								for (int bx = 0; bx < (CBCRWIDTH / CBCRBLOCK_W);bx++)
								{
									cbcr_init_pix_loc[bx + (BLOCK_W_NUM * by)] = (bx * CBCRBLOCK_W) + (by * CBCRWIDTH * CBCRBLOCK_H);

									int Ac_Flag = 0;
									int cbcr_mv_x = 0;
									int cbcr_mv_y = 0;



									RE_cbcr_intra_inter_entropy(&entropy_buf_cnt, buf_entropy, &buf_read, CBCRblockArray, &Ac_Flag, CBCRBLOCK_W, CBCRBLOCK_H, READ_FILE);

									CBCR_izig_zag_scan(CBCRblockArray, CBCR_Zigzag_array);

									if (dc_dmpcm == 0)
									{
										CBCR_idcdpcm(cbcr_init_pix_loc[bx + (BLOCK_W_NUM * by)], cr_buffer_decod, CBCRblockArray);
									}

									for (int nY = 0;nY < CBCRBLOCK_H;nY++)
									{
										for (int nX = 0;nX < CBCRBLOCK_W;nX++)
										{
											cr_buffer_decod[(bx * CBCRBLOCK_W) + (by * CBCRWIDTH * CBCRBLOCK_H) + nX + (nY * CBCRWIDTH)] = (CBCRblockArray[nX + (CBCRBLOCK_W * nY)]);
										}

									}

									CBCR_iQuantization(CBCRblockArray, DCQP, ACQP);

									CBCR_IDCT(CBCRblockArray);

									if (intra_prediction == 1)
									{
										if (z % (intra_period + 1) == 0)
										{
											icbcr_intra(cbcr_init_pix_loc[bx + (BLOCK_W_NUM * by)], cr_restored_data, CBCRblockArray, intra_modenum1[icbcr_mode_num]);
											icbcr_mode_num++;
										}
									}
									if (z % (intra_period + 1) != 0)
									{
										cbcr_mv_x = Mv_x_flag[iMv_num] / 2;
										cbcr_mv_y = Mv_x_flag[iMv_num] / 2;
										iCBCR_inter(cbcr_init_pix_loc[bx + (BLOCK_W_NUM * by)], cr_buffer_padding, cbcr_mv_x, cbcr_mv_y, cr_restored_data, CBCRblockArray);
										iMv_num++;
									}
									cbcr_clipping(CBCRblockArray);
									for (int nY = 0;nY < CBCRBLOCK_H;nY++)
									{
										for (int nX = 0;nX < CBCRBLOCK_W;nX++)
										{
											cr_restored_data[(bx * CBCRBLOCK_W) + (by * CBCRWIDTH * CBCRBLOCK_H) + nX + (nY * CBCRWIDTH)] = (unsigned char)(CBCRblockArray[nX + (CBCRBLOCK_W * nY)]);
										}
									}

								}
							}
							cb_padding(cr_restored_data, cr_buffer_padding);
							fwrite(cr_restored_data, sizeof(unsigned char), CBCRnFrameSize, RESTORED_FILE);

							fread(TEST_data, sizeof(unsigned char), nFrameSize, TEST_FILE);
							fread(cb_TEST_data, sizeof(unsigned char), CBCRnFrameSize, TEST_FILE);
							fread(cr_TEST_data, sizeof(unsigned char), CBCRnFrameSize, TEST_FILE);

							for (int i = 0;i < HEIGHT;i++)
							{
								for (int j = 0;j < WIDTH;j++)
								{
									MSE += (TEST_data[j + i * WIDTH] - restored_data[j + i * WIDTH]) * (TEST_data[j + i * WIDTH] - restored_data[j + i * WIDTH]);

								}
							}
							MSE = MSE / (WIDTH * HEIGHT);

							for (int i = 0;i < CBCRHEIGHT;i++)
							{
								for (int j = 0;j < CBCRWIDTH;j++)
								{
									cb_MSE += (cb_TEST_data[j + i * CBCRWIDTH] - cb_restored_data[j + i * CBCRWIDTH]) * (cb_TEST_data[j + i * CBCRWIDTH] - cb_restored_data[j + i * CBCRWIDTH]);

								}
							}
							cb_MSE = cb_MSE / (CBCRWIDTH * CBCRHEIGHT);
							for (int i = 0;i < CBCRHEIGHT;i++)
							{
								for (int j = 0;j < CBCRWIDTH;j++)
								{
									cr_MSE += (cr_TEST_data[j + i * CBCRWIDTH] - cr_restored_data[j + i * CBCRWIDTH]) * (cr_TEST_data[j + i * CBCRWIDTH] - cr_restored_data[j + i * CBCRWIDTH]);

								}
							}
							cr_MSE = cr_MSE / (CBCRWIDTH * CBCRHEIGHT);

							MSE = (MSE + cr_MSE + cb_MSE) / 3;
							//printf("mse %lf",MSE);
							sumPSNR += 10 * log10((255 * 255) / MSE);
							
							//printf("psnr %lf", PSNR);

						}
						char spsnr[20] = "";
						PSNR = sumPSNR / 90;
						sprintf(spsnr, "%lf", PSNR);
						strcat(data_collection," psnr :");
						strcat(data_collection, spsnr);
						fputs(data_collection, data_collection_FILE);
						fputs("\n", data_collection_FILE);
					
						printf("psnr %lf", PSNR);
						
						free(read_data_origin);
						free(buffer_decod);
						free(restored_data);
						free(buffer_padding);
						free(cb_read_data_origin);
						free(cb_buffer_decod);
						free(cb_restored_data);
						free(cb_buffer_padding);
						free(cr_read_data_origin);
						free(cr_buffer_decod);
						free(cr_restored_data);
						free(cr_buffer_padding);

						fclose(RESTORED_FILE);
						fclose(READ_FILE);
						fclose(TEST_FILE);
						

					}
				}
			}
		}
	}
	fclose(data_collection_FILE);
}