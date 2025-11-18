#include <stdio.h>
#include "encode.h"
#include "types.h"
#include "common.h"

/* Function Definitions */

/* Get image size
 * Input: Image file ptr
 * Output: width * height * bytes per pixel (3 in our case)
 * Description: In BMP Image, width is stored in offset 18,
 * and height after that. size is 4 bytes
 */

uint get_image_size_for_bmp(FILE *fptr_image)
{
    uint width, height;
    // Seek to 18th byte
    fseek(fptr_image, 18, SEEK_SET);

    // Read the width (an int)
    fread(&width, sizeof(int), 1, fptr_image);

    // Read the height (an int)
    fread(&height, sizeof(int), 1, fptr_image);

    // Return image capacity
    return width * height * 3;
}

/* 
 * Get File pointers for i/p and o/p files
 * Inputs: Src Image file, Secret file and
 * Stego Image file
 * Output: FILE pointer for above files
 * Return Value: e_success or e_failure, on file errors
 */
Status open_files(EncodeInfo *encInfo)
{
    // Src Image file
    encInfo->fptr_src_image = fopen(encInfo->src_image_fname, "r");
    // Do Error handling
    if (encInfo->fptr_src_image == NULL)
    {
    	perror("fopen");
    	fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->src_image_fname);

    	return e_failure;
    }

    // Secret file
    encInfo->fptr_secret = fopen(encInfo->secret_fname, "r");
    // Do Error handling
    if (encInfo->fptr_secret == NULL)
    {
    	perror("fopen");
    	fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->secret_fname);

    	return e_failure;
    }

    // Stego Image file
    encInfo->fptr_stego_image = fopen(encInfo->stego_image_fname, "w");
    // Do Error handling
    if (encInfo->fptr_stego_image == NULL)
    {
    	perror("fopen");
    	fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->stego_image_fname);

    	return e_failure;
    }

    // No failure return e_success
    return e_success;
}
OperationType check_operation_type (char *argv[])
{
    if(strcmp(argv[1],"-e")==0)
    {
        return e_encode;
    }
    else if(strcmp(argv[1],"-d")==0)
    {
        return e_decode;
    }
    else
    {
        return e_unsupported;
    }
}
Status read_and_validate_encode_args(int argc,char *argv[], EncodeInfo *encInfo)
{
    if(argc==3)
    {
        printf("pass at least 4 args\n");
        return e_failure;
    }
    int len=strlen(argv[2]);
    if(strcmp(&argv[2][len-4],".bmp")==0)
    {
        encInfo->src_image_fname=malloc(len+1);
        strcpy(encInfo->src_image_fname,argv[2]);
        printf("bmp file added\n");
    }
    else
    {
        printf("error 1st file is not a bmp file\n");
        return e_failure;
    }
    len=strlen(argv[3]);
    char *pos1=strchr(argv[3],'.');
    if(pos1!=NULL)
    {
        encInfo->secret_fname=malloc(len+1);
        strcpy(encInfo->secret_fname,argv[3]);
        strcpy(encInfo->extn_secret_file,pos1);
        printf("secret file added\n");
    }
    else
    {
        printf("error no valid secret file\n");
        return e_failure;
    }
    if(argc==4)
    {
        encInfo->stego_image_fname=malloc(10);
        strcpy(encInfo->stego_image_fname,"stego.bmp");
        return e_success;
    }
    else if(argc==5)
    {
        len=strlen(argv[4]);
        if(strcmp(&argv[4][len-4],".bmp")==0)
        {
            encInfo->stego_image_fname=malloc(len+1);
            strcpy(encInfo->stego_image_fname,argv[4]);
            return e_success;
        }
        else
        {
            printf("error, 5th argument file is not a bmp file\n");
            return e_failure;
        }
    }
    return e_success;
}
Status do_encoding(EncodeInfo *encInfo)
{
    if(open_files(encInfo)==e_success)
    {
        printf("file opened\n");
    }
    else
    {
        printf("file not found\n");
        return e_failure;
    }
    if(check_capacity(encInfo)==e_success)
    {
        printf("do encoding....\n");   
    }
    else
    {
        printf("no space\n");
        return e_failure;
    }
    if(copy_bmp_header(encInfo->fptr_src_image,encInfo->fptr_stego_image)==e_success)
    {
        printf("header copied\n");
    }
    else
    {
        printf("header file could not copy\n");
        return e_failure;
    }
    if(encode_magic_string(MAGIC_STRING,encInfo)==e_success)
    {
        printf("magic string encoded\n");
    }
    if(encode_secret_file_extn_size(strlen(encInfo->extn_secret_file),encInfo)==e_success)
    {
        printf("extention size encoded\n");
    }
    if(encode_secret_file_extn(encInfo->extn_secret_file,encInfo)==e_success)
    {
        printf("extention encoded\n");
    }
    if(encode_secret_file_size(encInfo->size_secret_file,encInfo)==e_success)
    {
        printf("data size encoded\n");
    }
    if(encode_secret_file_data(encInfo)==e_success)
    {
        printf("secret data encoded\n");
    }
    if(copy_remaining_img_data(encInfo->fptr_src_image,encInfo->fptr_stego_image)==e_success)
    {
        printf("remaining data copied\n");
    }
    return e_success;
}


Status check_capacity(EncodeInfo *encInfo)
{
    encInfo->image_capacity = get_image_size_for_bmp(encInfo->fptr_src_image);
    encInfo->size_secret_file= get_file_size(encInfo->fptr_secret);
    if(((encInfo->image_capacity))>(((encInfo->size_secret_file)*8)+(sizeof(encInfo->extn_secret_file)*8)+(2*8*sizeof(int))+(strlen(MAGIC_STRING)*8)))
    {
        return e_success;
    }
    else
    return e_failure;
}
uint get_file_size(FILE *fptr_secret)
{
    long size;

    fseek(fptr_secret, 0, SEEK_END);   // Move pointer to end of file
    size = ftell(fptr_secret);         // Get current position = file size
    rewind(fptr_secret);               // Move pointer back to beginning

    return size;                // Return size in bytes
}
Status copy_bmp_header(FILE *fptr_src_image, FILE *fptr_dest_image)
{
    char buff[54];
    fseek(fptr_src_image, 0, SEEK_SET);
    fread(buff,1,54,fptr_src_image);
    fwrite(buff,1,54,fptr_dest_image);
    return e_success;
}
Status encode_magic_string(const char *magic_string, EncodeInfo *encInfo)
{
    int len=strlen(magic_string);
    char image[(len*8)+1];
    fread(image,1,len*8,encInfo->fptr_src_image);
    image[(len*8)]='\0';
    for(int i=0 ;i<len;i++)
    {
        char data=magic_string[i];
        encode_byte_to_lsb(data,&image[i*8]);
        
    }
    
    fwrite(image,1,len*8,encInfo->fptr_stego_image);
    return e_success;
}
Status encode_secret_file_extn_size(int size, EncodeInfo *encInfo)
{
    char buff[32];
    fread(buff,1,32,encInfo->fptr_src_image);
    if(encode_int_to_lsb(size,buff)==e_success)
    {
        fwrite(buff,1,32,encInfo->fptr_stego_image);
        return e_success;
    }
    
}
Status encode_secret_file_extn(const char *file, EncodeInfo *encInfo)
{
    int len=strlen(file);
    char buff[(len*8)+1];
    buff[len*8]='\0';
    fread(buff,1,len*8,encInfo->fptr_src_image);
    for(int i=0; i<len; i++)
    {
        encode_byte_to_lsb(file[i],&buff[i*8]);
    }
    fwrite(buff,1,len*8,encInfo->fptr_stego_image);
    return e_success;
}
Status encode_secret_file_size(int file_size, EncodeInfo *encInfo)
{
    char buff[32];
    fread(buff,1,32,encInfo->fptr_src_image);
    if(encode_int_to_lsb(file_size,buff)==e_success)
    {
        fwrite(buff,1,32,encInfo->fptr_stego_image);
        return e_success;
    }
}
Status encode_secret_file_data(EncodeInfo *encInfo)
{
    int size=encInfo->size_secret_file;
    char buff[size+1];
    fread(buff,1,size,encInfo->fptr_secret);
    buff[size]='\0';
    encode_data_to_image(buff,size,encInfo->fptr_src_image,encInfo->fptr_stego_image);
    return e_success;
}
Status encode_data_to_image(char *data, int size, FILE *fptr_src_image, FILE *fptr_stego_image)
{
    char buff2[size*8];
    fread(buff2,1,size*8,fptr_src_image);
    for(int i=0;i<size;i++)
    {
        encode_byte_to_lsb(data[i],&buff2[i*8]);
    }
    fwrite(buff2,1,size*8,fptr_stego_image);
    
}
Status copy_remaining_img_data(FILE *fptr_src, FILE *fptr_dest)
{
    int ch;
    while((ch = fgetc(fptr_src)) != EOF)
    {
        fputc(ch,fptr_dest);
    }
    return e_success;
}
Status encode_byte_to_lsb(char data, char *image_buffer)
{
    char new;
    int j=0;
    for(int i=7;i>=0;i--)
    {
        new=(data>>i)&1;
        if(new==0)
        {
            image_buffer[j] = image_buffer[j] & ~1;
            j++;
        }
        else if(new==1)
        {
            image_buffer[j] = image_buffer[j] | 1;
            j++;
        }
    }    
}
Status encode_int_to_lsb(int size,char *buff)
{
    int new;
    int j=0;
    for(int i=31;i>=0;i--)
    {
        new=(size>>i)&1;
        if(new==0)
        {
            buff[j] = buff[j] & ~1;
            j++;
        }
        else if(new==1)
        {
             buff[j] = buff[j] | 1;
             j++;
        }
    }   
    return e_success;
}