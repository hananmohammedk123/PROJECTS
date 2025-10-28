/* Name   : HANAN MOHAMMED K
  Project : MP# Tag Reader
  Date    : 28/10/25
  */
#include"mp3_header.h"
int main(int argc,char *argv[])
{
    if(argc<2)
    {
        printf("few arguments passed\n");
        return 0;
    }
    else if(argc==2)
    {
        if(strcmp(argv[1],"--help")==0)
        {
            mp3_help();
            return 0;
        }
        else
        {
            printf("Invalid argument\n");
            return 0;
        }
    }
    else if(argc==3)
    {
        if(strcmp(argv[1],"-v")==0)
        {
            mp3_view(argv[2]);
            return 0;
        }
        else if(strcmp(argv[1],"-e")==0)
        {
            printf("TAG and content not passed\n");
            return 0;
        }
        else
        {
            printf("invalid argument passed\n");
            return 0;
        }
    }
    else if(argc==5)
    {
        if(strcmp(argv[1],"-e")==0)
        {
            mp3_edit(argv[2],argv[3],argv[4]);
            return 0;
        }
        else
        {
            printf("Argument passed is invalid\n");
        }
    }
    else if(argc>5)
    printf("More number of argument passed\n");
    else
    printf("argument passed is incomplete\n");
}