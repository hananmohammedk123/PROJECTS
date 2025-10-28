#include"mp3_header.h"
void mp3_edit(char song[],char TAG[],char content[])
{
    FILE *tp =fopen("temp.mp3","wb");
    // create a temporary mp3 file to copy contents from your song

    FILE *fp =fopen(song,"rb");
    if (fp==NULL)
    {
        printf("file dont exist\n");
        return;
    }
    char word[5];
    check_tag(TAG,word);
    /* check whether the given TAG command is valid. and convert it to the tag name 
    using a string named word */

    int flag3=0;
    //to check whther editing is done or not

    char id3[10];
    fread(id3,sizeof(id3),1,fp);
    fwrite(id3,sizeof(id3),1,tp);
    //read and write first 10 bytes as it is to the temp.mp3 file

    //checking first 6 TAGS
    for(int i=0;i<6;i++)
    {
        char tag[5];
        fread(tag,(sizeof(tag)-1),1,fp);
        tag[4]='\0';

        fwrite(tag,(sizeof(tag)-1),1,tp);
        if((strcmp(word,tag)==0) || (strcmp(TAG,tag)==0))
        {
            if(strcmp(tag,"TYER")==0)
            {
                int res=validate(content);
                if(res==1)
                {
                    printf("Error, enter only digits in YEAR tag\n");
                    return;
                }
            }
            int size;
            size=strlen(content);
            //to edit you need the size of the edited content

            int temp=size;
            
            int og_size;
            /* to skip the original content of TAG from the music file, since we are replacing it with new contents, 
             also we can easily check the next TAG */

            fread(&og_size,4,1,fp);
            og_size=convert(og_size);
            //convert it so we can use it properly
            
            size=convert(size+1);//size + 1, due to the inclusion of '\0'
            fwrite(&size,4,1,tp);

            char flag[2];
            fread(flag,2,1,fp);
            fwrite(flag,2,1,tp);
            //skipping two flags

            char null='\0';
            fwrite(&null,1,1,tp);
            // writing null character in the start of the content,since it is stored in that manner

            fwrite(content,1,temp,tp);
            fseek(fp,og_size,SEEK_CUR);
            flag3=1;
            //edit is done.
        }   
        else
        {
            //if given TAG is not present then copy the TAG details as it is

            int size;
            fread(&size,4,1,fp);
            fwrite(&size,4,1,tp);
            //read and write Size as it is
            
            char flag2[2];
            fread(flag2,2,1,fp);
            fwrite(flag2,2,1,tp);
            //read and weite flag as it is

            size=convert(size);
            char content2[size];
            fread(content2,size,1,fp);
            fwrite(content2,size,1,tp);
            //read and write content as it is including null character.
        }
    }
    //copy paste the remaing data in the file as it is byte by byte.
    char buffer[1];
    while (fread(buffer,1,1,fp))//read till EOF.
    {
        fwrite(buffer,1,1,tp);
    }

    fclose(fp);
    fclose(tp);

    remove(song);
    rename("temp.mp3",song);
    
    if(flag3)
    {
        printf("Successfully edited the tag\n");
        printf("===========================\n");
    }
    else
    printf("Invalid tag passed, no change made\n");
    
}
int validate(char content[])
{
    int i=0,flag=0;
    while(content[i])
    {
        if(content[i]<'0' || content[i]>'9')
        {
            flag=1;
            break;
        }
        i++;
    }
    if(flag==1)
    return 1;
    else if(flag==0)
    return 0;
}
void check_tag(char *str,char*word)
{
    if(strcmp(str,"-a")==0)
    {
        strcpy(word,"TPE1");
    }
    else if(strcmp(str,"-t")==0)
    {
        strcpy(word,"TIT2");
    }
    else if(strcmp(str,"-A")==0)
    {
        strcpy(word,"TALB");
    }
    else if(strcmp(str,"-y")==0)
    {
        strcpy(word,"TYER");
    }
    else if(strcmp(str,"-c")==0)
    {
        strcpy(word,"COMM");
    }
    else if(strcmp(str,"-C")==0)
    {
        strcpy(word,"TCON");
    }
    else
    return;
}