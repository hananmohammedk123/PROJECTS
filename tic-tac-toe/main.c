#include"game_header.h"
char name1[50];
char name2[50];
int main()
{
    system("clear");
    printf("\t\t--------------------TIC TAC TOE------------------\n");
    printf("\nEnter player 1 name\n");
    scanf("%[^\n]",name1);
    printf("Enter player 2 name\n");
    scanf(" %[^\n]",name2);
    char arr[3][3]={'1','2','3','4','5','6','7','8','9'};
    printf("\n Note the Block Numbering..\n\n");
    for(int i=0;i<3;i++)
    {
        printf("\t\t\t-------------------------\n");
        printf("\t\t\t|  \t|  \t|  \t|\n\t\t\t|");
        for(int j=0;j<3;j++)
        {
           printf("   \033[33m%c\033[0m\t|",arr[i][j]);
           arr[i][j]=' ';
        }
        printf("\n");
        printf("\t\t\t|  \t|  \t|  \t|\n");
        if(i==2)
        {
            printf("\t\t\t-------------------------\n");
        }
    }
    //printf("\t\t--------------------TIC TAC TOE------------------\n");
    printf("\n\t  ----------------all set please wait--------------");
    fflush(stdout);
    sleep(5);
    system("clear");
    printf("\rloading");
    fflush(stdout);
    for(int i=0;i<4;i++)
    {
        sleep(1);
        printf(".");
        fflush(stdout);
    }
    system("clear");
    printboard(arr);
    int res=1;
    int count1=play1(arr,3);
    int count2=play2(arr,3);
    while(res)
    {
        if((count1+count2)<=4)
        {
            count1+=play1(arr,3);
            count2+=play2(arr,3);   
        }
        else
        {
            res=check(arr);
            if(res)
            {
                play1(arr,3);
                res=check(arr);
                if(res)
                {
                    play2(arr,3);
                }
                else
                return 0;
            }
            else
            return 0;
        }
    }

}