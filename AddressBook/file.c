#include <stdio.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook) {
    FILE *fp=fopen("contacts.csv","w");
    if(fp==NULL)
    {
        printf("Error");
        return;
    }
    fprintf(fp,"%d\n",addressBook->contactCount);
    for(int i=0;i<addressBook->contactCount;i++)
    {
        fprintf(fp,"%s,%s,%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    fclose(fp);
  
}

void loadContactsFromFile(AddressBook *addressBook) {
    FILE *fp=fopen("contacts.csv","r");
    if(fp==NULL)
    {
        printf("Error in opening saved contact file");
        fclose(fp);
        return;
    }
     fscanf(fp,"%d",&addressBook->contactCount);
     fgetc(fp);
     if(addressBook->contactCount>100)
     {
        printf("Contact count exeeded 100");
        fclose(fp);
        return;
     }
    for(int i=0;i<addressBook->contactCount;i++)
    {
        fscanf(fp,"%[^,],%[^,],%[^\n]\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    fclose(fp);
    
}
