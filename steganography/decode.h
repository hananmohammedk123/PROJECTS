#ifndef DECODE_H
#define DECODE_H
#include<string.h>
#include<stdlib.h>
#include"types.h"

typedef struct DecodeInfo
{
     /* Source Image info */
    char *src_image_fname;
    FILE *fptr_src_image;

    /* Secret File Info */
    char *secret_fname;
    FILE *fptr_secret;
    char extn_secret_file[4];
    long size_secret_file;
    int size_secret_file_extn;

}DecodeInfo;

Status read_and_validate_decode_args(int argc,char *argv[],DecodeInfo *decInfo);

/* Perform the encoding */
Status do_decoding(DecodeInfo *decInfo);

/* Get File pointers for i/p and o/p files */
Status open_image_file(DecodeInfo *decInfo);



/* skip bmp image header */
Status skip_bmp_header(DecodeInfo *decInfo);

/* decode Magic String */
Status decode_magic_string(const char* magic_string,DecodeInfo *decInfo);

/* decode secret file extenstion size */
Status decode_secret_file_extn_size(DecodeInfo *deccInfo);

/* decode secret file extenstion */
Status decode_secret_file_extn(DecodeInfo *decInfo);

/*create a secret file based on extention*/
Status open_secret_file(DecodeInfo *decInfo);

/* decode secret file size */
Status decode_secret_file_size(DecodeInfo *decInfo);

/* decode secret file data*/
Status decode_secret_file_data(DecodeInfo *decInfo);

/* decode a byte into LSB of image data array */
Status decode_byte_to_lsb(char *data, char *image_buffer);

/* decode a byte into LSB of image data array */
Status decode_int_to_lsb(int *size, char *buff);

#endif