#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define WIDTH 352
#define HEIGHT 288
#define N				8
#define NR 64
#define M_PIl			3.141592653589793238462643383279502884L /* pi */
#define SPIRALLINE 33
#define PWIDTH (WIDTH+32)
#define PHEIGHT (HEIGHT+32)
#define BLOCK_W 8
#define BLOCK_H 8
#define	SPIRAL_W 33
#define	SPIRAL_H 33
#define BLOCK_W_NUM 44
#define BLOCK_H_NUM 36 

#define FOREMANFRAME 300
#define AKIYOFRAME 300
#define FOOTFRAME 90
#define CBCRBLOCK_W (BLOCK_W/2)
#define CBCRBLOCK_H (BLOCK_H/2)
#define CBCRWIDTH (WIDTH/2)
#define CBCRHEIGHT (HEIGHT/2)
#define CBCRPWIDTH (PWIDTH/2)
#define CBCRPHEIGHT (PHEIGHT/2)


#define TN 0


double getCval(int y);
void dct(double* blockArray);
void idct(double* blockArray);
void Quantization(double* blockArray,int DCQP,int ACQP);
void iQuantization(double* blockArray, int DCQP, int ACQP);
int intra(int nIndex, unsigned char* restored_data, double* blockArray);
void iintra(int modenum, int nIndex, unsigned char* restored_data, double* blockArray);
void clipping(double* blockArray);
void cbcr_clipping(double* blockArray);
void spiral(int* spiral_x, int* spiral_y);
void padding(unsigned char* restored_data, unsigned char* buffer_padding);
void inter(int nIndex, unsigned char* buffer_padding, int* mvx, int* mvy, unsigned char* restored_data, int* spiral_x, int* spiral_y, double* blockArray);
void iinter(int nIndex, unsigned char* buffer_padding, double* mvx, double* mvy, double* blockArray);
void zig_zag_scan(double* blockarray, int* Zigzag_array);
void zig_zag_array(int* Zigzag_array, int zWIDTH, int zHEIGHT);
void izig_zag_scan(double* blockarray, int* Zigzag_array);
void mpm_flag(int* intra_modenum, int* intra_flag, int* intra_modenum_flag, int mode_num);
void impm_flag(int* intra_modenum1, int* intra_flag, int* intra_modenum_flag, int mode_num);
void dcdpcm(int index, double* buffer_encod, double* blockarrey);
void idcdpcm(int index, double* buffer_encod, double* blockarrey);
void icbcr_intra(int cbcr_init_pix_loc, unsigned char* cbcr_restored_data,double* CBCRblockArray,int intra_modenum);
void cbcr_intra(int cbcr_init_pix_loc,unsigned char* cbcr_restored_data, double* CBCRblockArray, int intra_modenum);
void cb_padding(unsigned char* cb_restored_data, unsigned char* cb_buffer_padding);
void CBCR_inter(int cbcr_init_pix_loc, unsigned char* cb_buffer_padding, int mvx, int mvy, unsigned char* cb_restored_data, double* CBCRblockArray);
void iCBCR_inter(int cbcr_init_pix_loc, unsigned char* cb_buffer_padding, double mvx, double mvy, unsigned char* cb_restored_data, double* CBCRblockArray);
void CBCR_IDCT(double* CBCRblockArray);
void CBCR_DCT(double* CBCRblockArray);
void CBCR_Quantization(double* CBCRblockArray, int DCQP, int ACQP);
void CBCR_iQuantization(double* CBCRblockArray, int DCQP, int ACQP);
void CBCR_dcdpcm(int cbcr_init_pix_loc, double* cb_buffer_encod, double* CBCRblockArray);
void CBCR_idcdpcm(int cbcr_init_pix_loc, double* cb_buffer_encod, double* CBCRblockArray);
void CBCR_zig_zag_scan(double* CBCRblockarray, int* CBCR_Zigzag_array);
void CBCR_izig_zag_scan(double* CBCRblockarray, int* CBCR_Zigzag_array);
void Conversion_entropy(int* buf_cnt, double blockArray, unsigned char* buf_write, int* buf_entropy, FILE* Compression_File);
void i_Conversion_entropy(int* ientropy_buf_cnt, double* blockArray, unsigned char* buf_write, int* buf_entropy, FILE* Comp_read_File);
int AC_FLAG(double* blockArray);
void RE_AC_FLAG(int AC_Flag, double* blockArray);
void intra_entropy(int* entropy_buf_cnt, int* buf_entropy, unsigned char* buf_write, int mode_num, int* intra_flag, int* intra_modenum_flag, FILE* Comp_write_File);
void inter_entropy(int* entropy_buf_cnt, int* buf_entropy, unsigned char* buf_write, double mv_x, double mv_y, FILE* Comp_write_File);
void encoder_entropy(int* entropy_buf_cnt, int* buf_entropy, unsigned char* buf_write, double* blockArray, int Ac_Flag, int b_width, int b_heigte, FILE* Comp_write_File);
int CBCR_AC_FLAG(double* blockArray);
void CBCR_RE_AC_FLAG(int AC_Flag, double* blockArray);
void cbcr_intra_inter_entropy(int* entropy_buf_cnt, int* buf_entropy, unsigned char* buf_write, double* blockArray, int Ac_Flag, int b_width, int b_heigte, FILE* Comp_write_File);
void stream_header(int DCQP, int ACQP, FILE* Comp_write_File, int intre_period, int intra_prediction, int pixel_dmpcm,int dc_dmpcm);
void write_entropy(int* buf_cnt, unsigned char* buf_write, int* buf_entropy, FILE* Compression_File);
void com_read_data(int* ientropy_buf_cnt, unsigned char* buf_write, int* buf_entropy, FILE* Comp_read_File);

void read_stream_header(int* DCQP, int* ACQP, FILE* Comp_write_File, int* intre_period, int* intra_prediction);
void RE_cbcr_intra_inter_entropy(int* entropy_buf_cnt, int* buf_entropy, unsigned char* buf_read, double* blockArray, int* Ac_Flag, int b_width, int b_heigte, FILE* Comp_read_File);
void RE_inter_entropy(int* entropy_buf_cnt, int* buf_entropy, unsigned char* buf_read, double* mv_x, double* mv_y, double* blockArray, int* Ac_Flag, int b_width, int b_heigte, FILE* Comp_read_File);
void RE_intra_entropy(int* entropy_buf_cnt, int* buf_entropy, unsigned char* buf_read, int mode_num, int* intra_flag, int* intra_modenum_flag, double* blockArray, int* Ac_Flag, int b_width, int b_heigte, FILE* Comp_read_File);