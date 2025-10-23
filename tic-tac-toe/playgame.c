#include"game_header.h"
int play1(char arr[3][3],int row)
{
    
    while(1)
    {
        printf("%s enter your choice number\n",name1);
        int choice;
        scanf("%d",&choice);
        if(choice <=9 && choice >=1)
        {
            choice=choice-1;
            int r=choice/3;
            int c=choice%3;
            if(arr[r][c]==' ')
            {
                arr[r][c]='X';
                break;
            }
            else if(arr[r][c]=='X' || arr[r][c]=='O')
            printf("already filled/ invalid entry\n");
        }
        else
        printf("give a valid entry\n");
        getchar();
    }
     system("clear");
     printboard(arr);
    static int p1_count=0;
    p1_count++;
    return p1_count;
}


int play2(char arr[3][3],int row)
{
    
    while(1)
    {
        printf("%s enter your choice number\n",name2);
        int choice;
        scanf("%d",&choice);
        if(choice <=9 && choice >=1)
        {
            choice=choice-1;
            int r=choice/3;
            int c=choice%3;
            if(arr[r][c]==' ')
            {
            arr[r][c]='O';
            break;
            }
            else if(arr[r][c]=='X' || arr[r][c]=='O')
            printf("already filled/ invalid entry\n");
        }
        else
        printf("give a valid entry\n");
        getchar();
    }
    system("clear");
    printboard(arr);
    static int p2_count=0;
    p2_count++;
    return p2_count;
}

int check(char arr[3][3])
{
    int draw=0;
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            if(arr[i][j]== 'X' || arr[i][j] == 'O')
            draw=draw+1;
        }
    }
    if(draw==9)
    {
        printf("Game is draw\n");
        exit(1);
    }
    int countX=0,countO=0,fix=0;
    for(fix;fix<3;fix++)
    {
        for(int i=0;i<3;i++)
        {
            if(arr[fix][i]=='X')
            countX++;
            else if(arr[fix][i]=='O')
            countO++;
        }
        if(countO==3)
        {
            printf("congrats \033[34m%s\033[0m you won the game!!\n",name2);
            return 0;
        }
        if(countX==3)
        {
            printf("congrats \033[32m%s\033[0m you won the game!!\n",name1);
            return 0;
        }
        countO=0;
        countX=0;
    
        for(int i=0;i<3;i++)
        {
            if(arr[i][fix]=='X')
            countX++;
            else if(arr[i][fix]=='O')
            countO++;
        }
        //printf("countx = %d\n",countX);
        if(countO==3)
        {
            printf("congrats \033[34m%s\033[0m you won the game!!\n",name2);
            return 0;
        }
        if(countX==3)
        {
            printf("congrats \033[32m%s\033[0m you won the game!!\n",name1);
            return 0;
        }
        
            countO=0;
            countX=0;
        
    }
    for(int i=0;i<3;i++)
    {
        if(arr[i][i]=='X')
        {
            countX++;
        }
        if (arr[i][i]=='O')
        {
            countO++;
        }
    }
    if(countO==3)
    {
        printf("congrats \033[34m%s\033[0m you won the game!!\n",name2);
        return 0;
    }
    if(countX==3)
    {
        printf("congrats \033[32m%s\033[0m you won the game!!\n",name1);
        return 0;
    }
        
        countO=0;
        countX=0;
    
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            if(i+j==2)
            {
                if(arr[i][j]=='X')
                {
                    countX++;
                }
                if (arr[i][j]=='O')
                {
                    countO++;
                }
            }
        }
    }
    if(countO==3)
    {
        printf("congrats \033[34m%s\033[0m you won the game!!\n",name2);
        return 0;
    }
    if(countX==3)
    {
        printf("congrats \033[32m%s\033[0m you won the game!!\n",name1);
        return 0;
    }
    
        countO=0;
        countX=0;
    
    return 1;
}
void printboard(char arr[3][3])
{
    for(int i=0;i<3;i++)
    {
        printf("\t\t\t-------------------------\n");
        printf("\t\t\t|  \t|  \t|  \t|\n\t\t\t|");
        for(int j=0;j<3;j++)
        {
           if(arr[i][j]=='X')
           printf("\033[32m   %c\033[0m\t|",arr[i][j]);
           else if(arr[i][j]=='O')
           printf("\033[34m   %c\033[0m\t|",arr[i][j]);
           else
           printf("   %c\t|",arr[i][j]);
        }
        printf("\n");
        printf("\t\t\t|  \t|  \t|  \t|\n");
        if(i==2)
        {
            printf("\t\t\t-------------------------\n");
        }
    }
}