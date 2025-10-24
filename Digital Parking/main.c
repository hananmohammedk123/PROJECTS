#include<stdio.h>
int main()
{
    int x=5,y=5;
    char slot[x][y];
  
    // load parking data from file
    FILE *fp=fopen("vacancy.txt","r");
    if(fp==NULL)
    {
        printf("No Data Found!!\n");
        return 0;
    }
    for(int i=0;i<x;i++)
    {
        for(int j=0; j<y; j++)
        {
            fread(&slot[i][j],1,1,fp);
        }
    }
    printf("=======================================================\n");
    printf("                   Vacancy Details        \n");
    printf("=======================================================\n");
    for(int i=0;i<x;i++)
    {
        for(int j=0; j<y; j++)
        {
            if((i*y)+(j+1)<10)
            {
                if(slot[i][j]=='A')
                printf("P0%d : +%c | ",(i*y)+(j+1),slot[i][j]);
                else if(slot[i][j]=='N')
                printf("P0%d : -%c | ",(i*y)+(j+1),slot[i][j]);
            }
            else
            {
                if(slot[i][j]=='A')
                printf("P%d : +%c | ",(i*y)+(j+1),slot[i][j]);
                else if(slot[i][j]=='N')
                printf("P%d : -%c | ",(i*y)+(j+1),slot[i][j]);
            }
        }

        printf("\n");
    }
    printf("=======================================================\n");
    fclose(fp);
    start1: printf("\n1 -> ENTRY PARKING\n2 -> EXIT PARKING\n3 -> Exit app\n\nEnter your choice\n");
    char start;
    scanf(" %c",&start);
    if(start!='1' && start !='2')
    {
        printf("Invalid entry, please try again\n");
        goto start1;
    }
    else if(start=='3')
    return 0;
    else if(start=='1')
    {
        char choice;
        printf("Welcome to Digital Parking. you wish to park y/n ?\n");
        scanf(" %c",&choice);
        if(choice =='y')
        {
            int row=0,col=0,flag=0;
            for(int i=0;i<x;i++)
            {
                for(int j=0; j<y; j++)
                {
                    if(slot[i][j]=='A')
                    {
                        flag=1;
                        row=i;
                        col=j;
                        break;
                    }
                }
                if (flag)
                break;
            }
            if(flag)
            {
                printf("Your allocated position is P%d, confirm entry (y/n) ?\n",(row*y)+(col+1));
                char choice2;
                scanf(" %c",&choice2);
                if(choice2=='y')
                slot[row][col]='N';
                else if(choice2=='n')
                {
                    printf("exiting....");
                    return 0;
                }
                else
                {
                    printf("invalid entry, try again\n");
                    return 0;
                }
                printf("Entry confirmed, Please go and park in P%d\n",(row*y)+(col+1));
                printf("=======================================================\n");
                printf("                   Vacancy Details        \n");
                printf("=======================================================\n");
                for(int i=0;i<x;i++)
                {
                    for(int j=0; j<y; j++)
                    {
                        if((i*y)+(j+1)<10)
                        {
                            if(slot[i][j]=='A')
                            printf("P0%d : +%c | ",(i*y)+(j+1),slot[i][j]);
                            else if(slot[i][j]=='N')
                            printf("P0%d : -%c | ",(i*y)+(j+1),slot[i][j]);
                        }
                        else
                        {
                            if(slot[i][j]=='A')
                            printf("P%d : +%c | ",(i*y)+(j+1),slot[i][j]);
                            else if(slot[i][j]=='N')
                            printf("P%d : -%c | ",(i*y)+(j+1),slot[i][j]);
                        }
                    }

                    printf("\n");
                }
                printf("=======================================================\n");
                FILE *fp=fopen("vacancy.txt","w");
                if(fp==NULL)
                {
                    printf("No Data Found!!\n");
                    return 0;
                }
                for(int i=0;i<x;i++)
                {
                    for(int j=0; j<y; j++)
                    {
                        fwrite(&slot[i][j],1,1,fp);
                    }
                }
                fclose(fp);
            }
            else
            {
                printf("Slot not available\n");
                return 0;
            }
        }
        else if(choice=='n')
        {
            printf("Thank you have a nice day..\n");
            return 0;
        }
        else
        printf("invalid input\n");
    }
    else if(start=='2')
    {
        printf("Enter your parking slot number(1-%d):\n",x*y);
        int num;
        scanf("%d",&num);
        if(num>=1 && num<=(x * y))
        {
            if(*(&slot[0][0]+(num-1))=='N')
            {
                printf("Slot released, please take your vehicle\n");
                *(&slot[0][0]+(num-1))='A';
            }
            else if(*(&slot[0][0]+(num-1))=='A')
            {
                printf("non parked location\n");
                return 0;
            }
            printf("=======================================================\n");
            printf("                   Vacancy Details        \n");
            printf("=======================================================\n");
            for(int i=0;i<x;i++)
            {
                for(int j=0; j<y; j++)
                {
                    if((i*y)+(j+1)<10)
                    {
                        if(slot[i][j]=='A')
                        printf("P0%d : +%c | ",(i*y)+(j+1),slot[i][j]);
                        else if(slot[i][j]=='N')
                        printf("P0%d : -%c | ",(i*y)+(j+1),slot[i][j]);
                    }
                    else
                    {
                        if(slot[i][j]=='A')
                        printf("P%d : +%c | ",(i*y)+(j+1),slot[i][j]);
                        else if(slot[i][j]=='N')
                        printf("P%d : -%c | ",(i*y)+(j+1),slot[i][j]);
                    }
                }

                printf("\n");
            }
            printf("=======================================================\n");
            printf("\nThank you for Parking...\n");
            FILE *fp=fopen("vacancy.txt","w");
            if(fp==NULL)
            {
                printf("No Data Found!!\n");
                return 0;
            }
            for(int i=0;i<x;i++)
            {
                for(int j=0; j<y; j++)
                {
                    fwrite(&slot[i][j],1,1,fp);
                }
            }
            fclose(fp);
        }
        else
        {
            printf("Error.entry invalid\n");
        }
        

    }
}