#include"mp3_header.h"
void mp3_help()
{
    printf("\nTo view the TAGS type    ->   ./a.out -v \"mp3name.mp3\"\n");
    printf("To edit the TAGS type    ->   ./a.out -e \"mp3name.mp3\" \"command\" \"edited content\"\n");
    printf("\n=============================================================\n");
    printf("                  MP3 TAG READER (help)\n");
    printf("=============================================================\n");
    printf(" TAGS       COMMAND\n");
    printf("--------------------------------------------------------------\n");
    char *name[6]={"TITLE","ARTIST","ALBUM","YEAR","CONTENT","COMMENT"};
    char *content[6]={"-t","-a","-A","-y","-C","-c"};
    for(int i=0;i<6;i++)
    {
        printf("%s\t->\t%s\n",name[i],content[i]);
    }
    printf("=============================================================\n");
}