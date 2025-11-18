#include <stdio.h>
#include "decode.h"
#include "types.h"
#include "common.h"

Status read_and_validate_decode_args(int argc,char *argv[],DecodeInfo *decInfo)
{
    int len=strlen(argv[2]);
    if(strcmp(&argv[2][len-4],".bmp")==0)
    {
        decInfo->src_image_fname=malloc(len+1);
        strcpy(decInfo->src_image_fname,argv[2]);
        printf("bmp file added\n");
    }
    else
    {
        printf("error 1st file is not a bmp file\n");
        return e_failure;
    }
    if(argc==4)
    {
        len=strlen(argv[3]);
        if(strchr(argv[3],'.')!=NULL)
        {
            decInfo->secret_fname=malloc(len+1);
            strcpy(decInfo->secret_fname,argv[3]);
            //strcpy(decInfo->extn_secret_file,".txt");
            printf("secret file added\n");
        }
        else 
        {
            printf("error the output file doesnt have any extention\n");
            return e_failure;
        }
    }
    else if(argc==3)
    {
        decInfo->secret_fname=malloc(15);
        strcpy(decInfo->secret_fname,"result");
        //strcpy(decInfo->extn_secret_file,".txt");
        return e_success;
    }
    else if(argc==5)
    {
        printf("more number of arguments passed\n");
        return e_failure;
    }
    return e_success;
}
Status do_decoding(DecodeInfo *decInfo)
{
    if(open_image_file(decInfo)==e_success)
    {
        printf("image file opened\n");
    }
    else
    {
        printf("file could not open\n");
        return e_failure;
    }
    if(skip_bmp_header(decInfo)==e_success)
    {
        printf("header skipped\n");
    }
    if(decode_magic_string(MAGIC_STRING,decInfo)==e_success)
    {
        printf("magic string decoded\n");
    }
    else
    {
        printf("magic string not found\n");
        return e_failure;
    }
    if(decode_secret_file_extn_size(decInfo)==e_success)
    {
        printf("extention size decoded\n");
    }
    if(decode_secret_file_extn(decInfo)==e_success)
    {
        printf("extention file decoded\n");
    }
    if(open_secret_file(decInfo)==e_success)
    {

    }
    if(decode_secret_file_size(decInfo)==e_success)
    {
        printf("size decoded\n");
    }
    if(decode_secret_file_data(decInfo)==e_success)
    {
        printf("data decoded\n");
    }
    return e_success;


}
Status open_image_file(DecodeInfo *decInfo)
{
      // Src Image file
    decInfo->fptr_src_image = fopen(decInfo->src_image_fname, "r");
    // Do Error handling
    if (decInfo->fptr_src_image == NULL)
    {
    	perror("fopen");
    	fprintf(stderr, "ERROR: Unable to open file %s\n", decInfo->src_image_fname);

    	return e_failure;
    }
    return e_success;
}
Status open_secret_file(DecodeInfo *decInfo)
{
    // Secret file
    decInfo->fptr_secret = fopen(decInfo->secret_fname, "w");
    // Do Error handling
    if (decInfo->fptr_secret == NULL)
    {
    	perror("fopen");
    	fprintf(stderr, "ERROR: Unable to open file %s\n", decInfo->secret_fname);

    	return e_failure;
    }
    return e_success;
}
Status skip_bmp_header(DecodeInfo *decInfo)
{
    fseek(decInfo->fptr_src_image,54,SEEK_SET);
    return e_success;
}
Status decode_magic_string(const char* magic_string,DecodeInfo *decInfo)
{
    char buff[16];
    char res[3];
    fread(buff,1,16,decInfo->fptr_src_image);
    for(int i=0;i<2;i++)
    {
        decode_byte_to_lsb(&res[i],&buff[i*8]);
    }
    res[2]='\0';
    //printf("%s",res);
    if(strcmp(magic_string,res)==0)
    {
        printf("magic string found\n");
        return e_success;
    }
    else
    return e_failure;
    
}
Status decode_secret_file_extn_size(DecodeInfo *decInfo)
{
    char buff[32];
    int size=0;
    fread(buff,1,32,decInfo->fptr_src_image);
    decode_int_to_lsb(&size,buff);
    decInfo->size_secret_file_extn=size;
    return e_success;
}
Status decode_secret_file_extn(DecodeInfo *decInfo)
{
    int size=decInfo->size_secret_file_extn;
    char res[size+1];
    char buff[size*8];
    fread(buff,1,size*8,decInfo->fptr_src_image);
    for(int i=0;i<size;i++)
    {
        decode_byte_to_lsb(&res[i],&buff[i*8]);
    }
    res[size]='\0';
    strcpy(decInfo->extn_secret_file,res);
    char *pos=strstr(decInfo->secret_fname,decInfo->extn_secret_file);
    if(pos!=NULL)
    {
        if(strcmp(pos,res)==0)
        {
            return e_success;
        }
        else
        {
            strcat(decInfo->secret_fname,res);
        }
        
    }
    else
    {
        strcat(decInfo->secret_fname,res);
    }
    return e_success;
}
Status decode_secret_file_size(DecodeInfo *decInfo)
{
    char buff[32];
    int size=0;
    fread(buff,1,32,decInfo->fptr_src_image);
    decode_int_to_lsb(&size,buff);
    decInfo->size_secret_file=size;
    return e_success;
}
Status decode_secret_file_data(DecodeInfo *decInfo)
{
    int size=decInfo->size_secret_file*8;
    char buff[size+1];
    char res[decInfo->size_secret_file+1];
    fread(buff,1,size,decInfo->fptr_src_image);
    for(int i=0;i<size;i++)
    {
        decode_byte_to_lsb(&res[i],&buff[i*8]);
    }
    fwrite(res,1,decInfo->size_secret_file,decInfo->fptr_secret);
    return e_success;

}
Status decode_byte_to_lsb(char *data, char *image_buffer)
{
    *data=0;
    int j=0;
    for(int i=7;i>=0;i--)
    {
        *data = *data | (image_buffer[j] & 1)<<i;
        j++;
    }
}
Status decode_int_to_lsb(int *size, char *buff)
{
    int j=0;
    for(int i=31;i>=0;i--)
    {
        *size = *size | (buff[j] & 1)<<i;
        j++; 
    }
}