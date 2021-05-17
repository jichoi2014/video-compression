//#include <windows.h>
#include "buffer.h"

int main()
{
	//system("mode con cols=50 lines=80");
	
	
		int DCQP=1;
		
		int ACQP=1;//1,16
			
		int dc_dmpcm = 0;
				
		int intra_period = 0; // 피리어드값!!!!!!!!!!!!!!!!!!
					
		int intra_prediction = 1;//설정에 따라 인트라 모드 실행 나는 설정 안해줌

		double sum_dc_data = 0;
	
					

						FILE* pOriginalFile = NULL;
						FILE* pidctFile = NULL;
						FILE* Comp_write_File = NULL;

						pOriginalFile = fopen("football_cif(352X288)_90f.YUV", "rb");
						pidctFile = fopen("TESTfootball_cif(352X288)_90f.YUV", "wb");
						Comp_write_File = fopen("tastfoot11.RAW", "wb");//명칭 다르게 실행 왜냐하면 파일 자체 읽는 위치가 바뀌기 문에//읽거나 쓰는 위치 공유
						if (Comp_write_File == NULL)
						{
							fputs("File error ", stderr);
							exit(1);
						}
						if (pOriginalFile == NULL)
						{
							fputs("File error", stderr);
							exit(1);
						}
						if (pidctFile == NULL)
						{
							fputs("File error", stderr);
							exit(1);
						}
						unsigned int filesize = 0;
						fseek(pOriginalFile, 0, SEEK_END);
						filesize = ftell(pOriginalFile);
						fseek(pOriginalFile, 0, SEEK_SET);

						double blockArray[64] = { 0, };
						int Zigzag_array[64] = { 0, };
						int CBCR_Zigzag_array[16] = { 0, };
						int nFrameSize = WIDTH * HEIGHT;
						int PaddingFrameSize = PWIDTH * PHEIGHT;
						double CBCRblockArray[16] = { 0, };
						int CBCRZigzag_array[16] = { 0, };
						int CBCRnFrameSize = CBCRWIDTH * CBCRHEIGHT;
						int CBCRPaddingFrameSize = CBCRPWIDTH * CBCRPHEIGHT;
						int originalframesize = nFrameSize + CBCRnFrameSize * 2;

						unsigned char* read_data_origin = (unsigned char*)calloc(nFrameSize, sizeof(unsigned char));
						unsigned char* restored_data = (unsigned char*)calloc(nFrameSize, sizeof(unsigned char));
						unsigned char* buffer_padding = (unsigned char*)calloc(PaddingFrameSize, sizeof(unsigned char));
						double* buffer_encod = (double*)calloc(nFrameSize, sizeof(double));

						unsigned char* cb_read_data_origin = (unsigned char*)calloc(CBCRnFrameSize, sizeof(unsigned char));
						unsigned char* cb_restored_data = (unsigned char*)calloc(CBCRnFrameSize, sizeof(unsigned char));
						unsigned char* cb_buffer_padding = (unsigned char*)calloc(CBCRPaddingFrameSize, sizeof(unsigned char));
						double* cb_buffer_encod = (double*)calloc(CBCRnFrameSize, sizeof(double));
						unsigned char* cr_read_data_origin = (unsigned char*)calloc(CBCRnFrameSize, sizeof(unsigned char));
						unsigned char* cr_restored_data = (unsigned char*)calloc(CBCRnFrameSize, sizeof(unsigned char));
						unsigned char* cr_buffer_padding = (unsigned char*)calloc(CBCRPaddingFrameSize, sizeof(unsigned char));
						double* cr_buffer_encod = (double*)calloc(CBCRnFrameSize, sizeof(double));

						int spiral_x[SPIRALLINE * SPIRALLINE] = { 0, };
						int spiral_y[SPIRALLINE * SPIRALLINE] = { 0, };
						int bufferspiral_x[SPIRALLINE * SPIRALLINE] = { 0, };
						int bufferspiral_y[SPIRALLINE * SPIRALLINE] = { 0, };

						int mode_num = 0;
						int cbcr_mode_num = 0;
						int icbcr_mode_num = 0;
						int imode_num = 0;
						int Mv_num = 0;
						int iMv_num = 0;
						int entropy_buf_cnt = 0;
						int ientropy_buf_cnt = 0;
						int buf_entropy[8] = { 0, };

						unsigned char buf_write = 0;
						int mv_flag = 0;
						int a = 0;
						int b = 0;
						int pixel_dmpcm = 6;
						spiral(bufferspiral_x, bufferspiral_y);
						for (int i = 0;i < SPIRAL_W * SPIRAL_H;i++)
						{

							a += bufferspiral_x[i];
							spiral_x[i] = a;// 값으로 받아오기
							b += bufferspiral_y[i];
							spiral_y[i] = b;

						}
						zig_zag_array(Zigzag_array, BLOCK_W, BLOCK_H);

						zig_zag_array(CBCR_Zigzag_array, CBCRBLOCK_W, CBCRBLOCK_H);



						stream_header(DCQP, ACQP, Comp_write_File, intra_period, intra_prediction, pixel_dmpcm, dc_dmpcm);
						int settell = 0;
						int ac = filesize / (nFrameSize * 1.5);
						//printf("%d", ac);
						for (int z = 0;z < 1;z++ )//settell < filesize;z++, settell = ftell(pOriginalFile)
						{

							mode_num = 0;
							cbcr_mode_num = 0;
							icbcr_mode_num = 0;
							imode_num = 0;
							Mv_num = 0;
							iMv_num = 0;

							double Mv_x_flag[BLOCK_W_NUM * BLOCK_H_NUM] = { 0, };
							double Mv_y_flag[BLOCK_W_NUM * BLOCK_H_NUM] = { 0, };
							int init_fpx_loc[BLOCK_W_NUM * BLOCK_H_NUM] = { 0, };
							int intra_modenum_flag[BLOCK_W_NUM * BLOCK_H_NUM] = { 0, };
							int intra_modenum[BLOCK_W_NUM * BLOCK_H_NUM] = { 0, };
							int intra_modenum1[BLOCK_W_NUM * BLOCK_H_NUM] = { 0, };
							int intra_flag[BLOCK_W_NUM * BLOCK_H_NUM] = { 0, };
							int cbcr_init_pix_loc[BLOCK_W_NUM * BLOCK_H_NUM] = { 0, };

							printf("[ %d frame ] Start!!\n", z + 1);

							fread(read_data_origin, sizeof(unsigned char), nFrameSize, pOriginalFile);//한프레임 받아오기


							for (int by = 0; by < (HEIGHT / 8);by++)//블럭화+dct
							{
								for (int bx = 0; bx < (WIDTH / 8);bx++)
								{
									init_fpx_loc[bx + (BLOCK_W_NUM * by)] = (bx * BLOCK_W) + (by * WIDTH * BLOCK_H);//각 블록의 DC값 넣어주기

									for (int nY = 0;nY < N;nY++)
									{
										for (int nX = 0;nX < N;nX++)
										{
											blockArray[nX + (N * nY)] = double(read_data_origin[(bx * N) + nX + (nY * WIDTH) + (by * N * WIDTH)]);
										}
									}

									int Ac_Flag = 0;
									int mvx = 0;
									int mvy = 0;

									if (by == 30 && bx == 30)
									{
										for (int i = 0;i < 8;i++)
										{
											for (int j = 0;j < 8;j++)
											{
												printf(" %lf ", blockArray[j + i * 8]);
											}
											printf("\n");
										}
										printf("\n");
									}
									
									if (intra_prediction == 1)
									{
										if (z % (intra_period + 1) == 0)
										{
											intra_modenum[mode_num] = intra(init_fpx_loc[bx + (BLOCK_W_NUM * by)], restored_data, blockArray);

											mpm_flag(intra_modenum, intra_flag, intra_modenum_flag, mode_num);
											mode_num++;
										}
									}
									

									if (by == 30 && bx == 30)
									{
										for (int i = 0;i < 8;i++)
										{
											for (int j = 0;j < 8;j++)
											{
												printf(" %lf ", blockArray[j + i * 8]);
											}
											printf("\n");
										}
										printf("\n");
									}


									if (z % (intra_period + 1) != 0)
									{
										inter(init_fpx_loc[bx + (BLOCK_W_NUM * by)], buffer_padding, &mvx, &mvy, restored_data, spiral_x, spiral_y, blockArray);
										Mv_x_flag[Mv_num] = mvx;
										Mv_y_flag[Mv_num] = mvy;
										Mv_num++;

									}

									dct(blockArray);

									if (by == 30 && bx == 30)
									{
										for (int i = 0;i < 8;i++)
										{
											for (int j = 0;j < 8;j++)
											{
												printf(" %lf ", blockArray[j + i * 8]);
											}
											printf("\n");
										}
										printf("\n");
									}
									
									Quantization(blockArray, DCQP, ACQP);

									for (int nY = 0;nY < N;nY++)
									{
										for (int nX = 0;nX < N;nX++)
										{
											buffer_encod[(bx * N) + nX + (nY * WIDTH) + (by * N * WIDTH)] = (blockArray[nX + (N * nY)]);
										}

									}
									if (dc_dmpcm == 0)
									{
										dcdpcm(init_fpx_loc[bx + (BLOCK_W_NUM * by)], buffer_encod, blockArray);
									}
									if (by == 30 && bx == 30)
									{
										for (int i = 0;i < 8;i++)
										{
											for (int j = 0;j < 8;j++)
											{
												printf(" %lf ", blockArray[j + i * 8]);
											}
											printf("\n");
										}
										printf("\n");
									}

									sum_dc_data += blockArray[0];

									Ac_Flag = AC_FLAG(blockArray);

									zig_zag_scan(blockArray, Zigzag_array);

									if (intra_prediction == 1)
									{
										if (z % (intra_period + 1) == 0)//entropy
										{

											intra_entropy(&entropy_buf_cnt, buf_entropy, &buf_write, mode_num, intra_flag, intra_modenum_flag, Comp_write_File);

										}
									}


									if (z % (intra_period + 1) != 0)
									{
										if (by == 0 && bx == 0)//mv flag넣어주기
										{
											buf_entropy[entropy_buf_cnt] = mv_flag;//mv플래그 넣기
											entropy_buf_cnt += 1;
											if (entropy_buf_cnt == 8)
											{

												for (int i = 0; i < 8;i++)
												{
													buf_write += buf_entropy[i] * (128 / pow(2, i));

												}

												fwrite(&buf_write, sizeof(unsigned char), 1, Comp_write_File);
												buf_write = 0;
												entropy_buf_cnt = 0;
											}
										}

										inter_entropy(&entropy_buf_cnt, buf_entropy, &buf_write, Mv_x_flag[Mv_num - 1], Mv_y_flag[Mv_num - 1], Comp_write_File);
									}

									encoder_entropy(&entropy_buf_cnt, buf_entropy, &buf_write, blockArray, Ac_Flag, BLOCK_W, BLOCK_H, Comp_write_File);

									/*if (by == 1 && bx == 23)
									{
										printf(" mvx: %lf  mvy : %lf   DC :  %lf ACFLAG  :  %d \n", Mv_x_flag[iMv_num], Mv_y_flag[iMv_num], blockArray[0], Ac_Flag);
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
										idcdpcm(init_fpx_loc[bx + (BLOCK_W_NUM * by)], buffer_encod, blockArray);
									}
									iQuantization(blockArray, DCQP, ACQP);
									idct(blockArray);
									/*if (by == 0 && bx == 1)
									{
										printf("modenum : %d  mpmflag : %d mode :  %d DC :  %lf ACFLAG  :  %d \n", intra_modenum[imode_num], intra_flag[imode_num], intra_modenum_flag[imode_num], blockArray[0], Ac_Flag);
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
									if (intra_prediction == 1)
									{
										if (z % (intra_period + 1) == 0)
										{
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

									if (by == 30 && bx == 30)
									{
										for (int i = 0;i < 8;i++)
										{
											for (int j = 0;j < 8;j++)
											{
												printf(" %lf ", blockArray[j + i * 8]);
											}
											printf("\n");
										}
										printf("\n");
									}

									for (int nY = 0;nY < N;nY++)
									{
										for (int nX = 0;nX < N;nX++)
										{
											restored_data[(bx * N) + nX + (nY * WIDTH) + (by * N * WIDTH)] = (unsigned char)(blockArray[nX + (N * nY)]);

										}

									}

								}

							}
							/*for (int i = 0;i < 288;i++)
							{
								for (int j = 0;j < 352;j++)
								{
									printf(" %d ", restored_data[j + i * 352]);
								}
								printf("\n");
							}*/
							//printf("\n");
							padding(restored_data, buffer_padding);
							fwrite(restored_data, sizeof(unsigned char), nFrameSize, pidctFile);


							fread(cb_read_data_origin, sizeof(unsigned char), CBCRnFrameSize, pOriginalFile);//cbcr한프레임 받아오기
							Mv_num = 0;
							iMv_num = 0;

							for (int by = 0; by < (CBCRHEIGHT / CBCRBLOCK_H);by++)//cb 블럭화+dct
							{
								for (int bx = 0; bx < (CBCRWIDTH / CBCRBLOCK_W);bx++)
								{
									cbcr_init_pix_loc[bx + (BLOCK_W_NUM * by)] = (bx * CBCRBLOCK_W) + (by * CBCRWIDTH * CBCRBLOCK_H);

									for (int nY = 0;nY < CBCRBLOCK_H;nY++)
									{
										for (int nX = 0;nX < CBCRBLOCK_W;nX++)
										{
											CBCRblockArray[nX + (CBCRBLOCK_W * nY)] = cb_read_data_origin[(bx * CBCRBLOCK_W) + (by * CBCRWIDTH * CBCRBLOCK_H) + nX + (nY * CBCRWIDTH)];
										}
									}
									int cbcr_mv_x = 0;
									int cbcr_mv_y = 0;
									if (intra_prediction == 1)
									{
										if (z % (intra_period + 1) == 0)
										{
											cbcr_intra(cbcr_init_pix_loc[bx + (BLOCK_W_NUM * by)], cb_restored_data, CBCRblockArray, intra_modenum[cbcr_mode_num]);
											cbcr_mode_num++;
										}
									}
									if (z % (intra_period + 1) != 0)
									{
										cbcr_mv_x = Mv_x_flag[Mv_num] / 2;
										cbcr_mv_y = Mv_x_flag[Mv_num] / 2;
										CBCR_inter(cbcr_init_pix_loc[bx + (BLOCK_W_NUM * by)], cb_buffer_padding, cbcr_mv_x, cbcr_mv_y, cb_restored_data, CBCRblockArray);
										Mv_num++;

									}

									CBCR_DCT(CBCRblockArray);

									CBCR_Quantization(CBCRblockArray, DCQP, ACQP);
									for (int nY = 0;nY < CBCRBLOCK_H;nY++)
									{
										for (int nX = 0;nX < CBCRBLOCK_W;nX++)
										{
											cb_buffer_encod[(bx * CBCRBLOCK_W) + (by * CBCRWIDTH * CBCRBLOCK_H) + nX + (nY * CBCRWIDTH)] = (CBCRblockArray[nX + (CBCRBLOCK_W * nY)]);
										}

									}
									if (dc_dmpcm == 0)
									{
										CBCR_dcdpcm(cbcr_init_pix_loc[bx + (BLOCK_W_NUM * by)], cb_buffer_encod, CBCRblockArray);
									}
									sum_dc_data += CBCRblockArray[0];
									CBCR_zig_zag_scan(CBCRblockArray, CBCR_Zigzag_array);

									int cbcr_Ac_Flag = CBCR_AC_FLAG(CBCRblockArray);
									cbcr_intra_inter_entropy(&entropy_buf_cnt, buf_entropy, &buf_write, CBCRblockArray, cbcr_Ac_Flag, CBCRBLOCK_W, CBCRBLOCK_H, Comp_write_File);



									CBCR_izig_zag_scan(CBCRblockArray, CBCR_Zigzag_array);
									if (dc_dmpcm == 0)
									{
										CBCR_idcdpcm(cbcr_init_pix_loc[bx + (BLOCK_W_NUM * by)], cb_buffer_encod, CBCRblockArray);
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

									cbcr_clipping(blockArray);


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
							fwrite(cb_restored_data, sizeof(unsigned char), CBCRnFrameSize, pidctFile);


							fread(cr_read_data_origin, sizeof(unsigned char), CBCRnFrameSize, pOriginalFile);
							Mv_num = 0;
							iMv_num = 0;
							cbcr_mode_num = 0;
							icbcr_mode_num = 0;
							for (int by = 0; by < (CBCRHEIGHT / CBCRBLOCK_H);by++)//cr 블럭화+dct
							{
								for (int bx = 0; bx < (CBCRWIDTH / CBCRBLOCK_W);bx++)
								{
									cbcr_init_pix_loc[bx + (BLOCK_W_NUM * by)] = (bx * CBCRBLOCK_W) + (by * CBCRWIDTH * CBCRBLOCK_H);

									for (int nY = 0;nY < CBCRBLOCK_H;nY++)
									{
										for (int nX = 0;nX < CBCRBLOCK_W;nX++)
										{
											CBCRblockArray[nX + (CBCRBLOCK_W * nY)] = cr_read_data_origin[(bx * CBCRBLOCK_W) + (by * CBCRWIDTH * CBCRBLOCK_H) + nX + (nY * CBCRWIDTH)];
										}
									}
									int cbcr_mv_x = 0;
									int cbcr_mv_y = 0;
									if (intra_prediction == 1)
									{
										if (z % (intra_period + 1) == 0)
										{
											cbcr_intra(cbcr_init_pix_loc[bx + (BLOCK_W_NUM * by)], cr_restored_data, CBCRblockArray, intra_modenum[cbcr_mode_num]);
											cbcr_mode_num++;

										}
									}
									if (z % (intra_period + 1) != 0)
									{
										cbcr_mv_x = Mv_x_flag[Mv_num] / 2;
										cbcr_mv_y = Mv_x_flag[Mv_num] / 2;
										CBCR_inter(cbcr_init_pix_loc[bx + (BLOCK_W_NUM * by)], cr_buffer_padding, cbcr_mv_x, cbcr_mv_y, cr_restored_data, CBCRblockArray);
										Mv_num++;
									}

									CBCR_DCT(CBCRblockArray);

									CBCR_Quantization(CBCRblockArray, DCQP, ACQP);
									for (int nY = 0;nY < CBCRBLOCK_H;nY++)
									{
										for (int nX = 0;nX < CBCRBLOCK_W;nX++)
										{
											cr_buffer_encod[(bx * CBCRBLOCK_W) + (by * CBCRWIDTH * CBCRBLOCK_H) + nX + (nY * CBCRWIDTH)] = (CBCRblockArray[nX + (CBCRBLOCK_W * nY)]);
										}

									}
									if (dc_dmpcm == 0)
									{
										CBCR_dcdpcm(cbcr_init_pix_loc[bx + (BLOCK_W_NUM * by)], cr_buffer_encod, CBCRblockArray);
									}
									sum_dc_data += CBCRblockArray[0];
									CBCR_zig_zag_scan(CBCRblockArray, CBCR_Zigzag_array);

									int cbcr_Ac_Flag = CBCR_AC_FLAG(CBCRblockArray);
									cbcr_intra_inter_entropy(&entropy_buf_cnt, buf_entropy, &buf_write, CBCRblockArray, cbcr_Ac_Flag, CBCRBLOCK_W, CBCRBLOCK_H, Comp_write_File);

									CBCR_izig_zag_scan(CBCRblockArray, CBCR_Zigzag_array);
									if (dc_dmpcm == 0)
									{
										CBCR_idcdpcm(cbcr_init_pix_loc[bx + (BLOCK_W_NUM * by)], cr_buffer_encod, CBCRblockArray);
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
									cbcr_clipping(blockArray);cbcr_clipping(blockArray);
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
							fwrite(cr_read_data_origin, sizeof(unsigned char), CBCRnFrameSize, pidctFile);

							printf("%d frame / dpcm : %lf", z,sum_dc_data);
							sum_dc_data = 0;
						}
						if (entropy_buf_cnt != 0)
						{
							for (int j = entropy_buf_cnt;j < 8;j++)
							{
								buf_entropy[j] = 0;
							}

							for (int i = 0; i < 8;i++)
							{
								buf_write += buf_entropy[i] * (128 / pow(2, i));
							}

							fwrite(&buf_write, sizeof(unsigned char), 1, Comp_write_File);
							buf_write = 0;
							entropy_buf_cnt = 0;

						}

						free(read_data_origin);
						free(buffer_encod);
						free(restored_data);
						free(buffer_padding);
						free(cb_read_data_origin);
						free(cb_buffer_encod);
						free(cb_restored_data);
						free(cb_buffer_padding);
						free(cr_read_data_origin);
						free(cr_buffer_encod);
						free(cr_restored_data);
						free(cr_buffer_padding);

						fclose(pOriginalFile);
						fclose(pidctFile);
						fclose(Comp_write_File);
						//memset(write_fil_name, NULL, 300);
						
					
				
			
		
	
	return 0;
}
