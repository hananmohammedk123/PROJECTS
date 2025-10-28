#include"mp3_header.h"
int convert(int);
void mp3_view(char song[])
{
    FILE *fp =fopen(song,"rb");
    if (fp==NULL)
    {
        printf("file dont exist\n");
        return;
    }
    char *name[6]={"TITLE","ARTIST","ALBUM","YEAR","CONTENT","COMMENT"};
    char id3[4];
    /* check whether the first 3 bytes is ID3 or not 
         to understand whether it is mp3 or not */

    fread(id3,(sizeof(id3)-1),1,fp);
    /* Reading first 3 bytes byte by byte to get "ID3"*/

    id3[3]='\0';
    if(strcmp(id3,"ID3")==0)
    {
        printf("\n=============================================================\n");
        printf("                      MP3 TAG READER\n");
    }
    else
    {
        printf("Not an mp3 file\n");
        return;
    }
    fseek(fp,7,SEEK_CUR);
    /* Skipping next 7 bytes as it is not used for viewing
       purpose it consists of Version (2 bytes) FLAGS(1 byte)
       Size(4 bytes) */
    printf("=============================================================\n");
    for(int i=0;i<6;i++) //we are only viewing 6 Tags so i<6.
    {
        char TAG[5];
        fread(TAG,(sizeof(TAG)-1),1,fp);
        TAG[4]='\0';

        int size;
        fread(&size,sizeof(size),1,fp);
        size=convert(size);
        /* We are reading byte by byte so while reading 
           we take as little endian ,but for proper conversion
           of size value from char to int we need to convert it
           to big endian first.*/

        fseek(fp,3,SEEK_CUR);
        /* we skip 3 bytes , 2 bytes for Flags and 1 byte for NULL character
           as in frame content,it start with null character*/

        char content[size];
        // we need the size to understand how much contet is there in this tag,and write that much content
        fread(content,size-1,1,fp);
        //reading the tag contents excluding NULL character, so we take size-1

        content[size-1]='\0';
        //making it a string

        printf("%s\t->\t%s\n",name[i],content);
    }
    printf("=============================================================\n");
    fclose(fp);

    
}
int convert(int size)
{
    char *ptr = (char *)&size;

    for(int i=0; i< sizeof(size)/2;i++)
    {
        char temp=ptr[i];
        ptr[i]=ptr[sizeof(size)-i-1];
        ptr[sizeof(size)-i-1]=temp;
    }
    return size;
}
