#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"
#include <ctype.h>
int validate_email(char email[], AddressBook *addressBook);
int validate_phone(char phone[], AddressBook *addressBook);
void listContacts(AddressBook *addressBook) 
{
    // Sort contacts based on the chosen criteria
    printf("-------------------------------------------------------------\n");
    printf("%-5s %-20s %-15s %-30s\n","sl_no","Name","Phone","Email");
    printf("-------------------------------------------------------------\n");
    for(int i=0;i<addressBook->contactCount;i++)
    { 
        printf("%-5d %-20s %-15s %-30s\n", i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    printf("-------------------------------------------------------------\n");
    
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
    //loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}


void createContact(AddressBook *addressBook)
{
	/* Define the logic to create a Contacts */   
    // Input name

         char name[20];
         printf("Enter your name\n");
         scanf(" %[^\n]",name);
         strcpy(addressBook->contacts[addressBook->contactCount].name,name);

    // Input phone number
     int ret=0;
     do
     {
        char phone[20];
        printf("Enter the phone number\n");
        scanf("%s",phone);
        ret=validate_phone(phone,addressBook);
        if(ret)
        {
            strcpy(addressBook->contacts[addressBook->contactCount].phone,phone);
        }
        else
        {
            printf("Please enter a valid phone number\n");
        }
     }while(ret==0);

    // Input email
     int ret2=0;
     do
     {
        char email[50];
        printf("Enter your email\n");
        scanf("%s",email);
        ret2=validate_email(email,addressBook);
        if(ret2)
        {
            strcpy(addressBook->contacts[addressBook->contactCount].email,email);
        }
        else
        {
            printf("Please enter a valid email\n");
        } 
     }while(ret2==0);

     addressBook->contactCount++;
     printf("Contact added successfully!\n");
}

int searchContact(AddressBook *addressBook,int call) 
{
    /* Define the logic for search */
   
    char choice;
    do
    {    
        printf("\nCONTACT SEARCH\n");
        printf("\n1. Search by Name\n2. Search by Phone Number\n3. Search by Email\n4. Exit\n");
        printf("\nEnter your choice\n");
        scanf(" %c",&choice);
        switch(choice)
    {
        case '1': {
                  char name[50];
                  printf("Enter the name to search: ");
                  scanf(" %[^\n]", name);
                  int flag=0;
                  printf("------------------------------------------------------------------\n");
                  for(int i=0;i<addressBook->contactCount;i++)
                  { 
                    if(strstr(addressBook->contacts[i].name,name)!=NULL)
                    {
                        printf("%d -> Name: %s\t Phone: %s\t Email: %s\n",i,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                        flag=1;
                    }
                  }
                    if(flag)
                    {
                        printf("------------------------------------------------------------------\n");
                        if(call==1)
                        {
                            return 4;
                        }
                        else
                        {
                            break;
                        }
                    }
                    else
                    {
                        printf("Contact not found with the given name.\n");
                        printf("------------------------------------------------------------------\n");
                        
                    }
                 break;}

        case '2': {
                  char phone[20];
                  printf("Enter the phone number to search: ");
                  scanf("%s", phone);
                  int flag=0;
                  printf("------------------------------------------------------------------\n");
                  for(int i=0;i<addressBook->contactCount;i++)
                  {
                        if(strcmp(addressBook->contacts[i].phone,phone)==0)
                        {
                            printf("%d -> Name: %s\t Phone: %s\t Email: %s\n",i, addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                            flag=1;
                        }
                  }
                    if(flag)
                    {
                        printf("------------------------------------------------------------------\n");
                        if(call==1)
                        {
                            return 4;
                        }
                        else
                        {
                            break;
                        }
                    }
                    else
                    {
                        printf("Contact not found with the given phone number.\n");
                        
                    }
                    break;}

      case '3': { 
                     char email[50];
                     printf("Enter the email to search: ");
                     scanf("%s", email);
                     int flag=0;
                     printf("------------------------------------------------------------------\n");
                     for(int i=0;i<addressBook->contactCount;i++)
                     {
                        if(strcmp(addressBook->contacts[i].email,email)==0)
                        {
                            printf("Name: %s\t Phone: %s\t Email: %s\n", addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                            flag=1;
                        }
                    }
                    if(flag)
                    {
                         printf("------------------------------------------------------------------\n");
                         if(call==1)
                         {
                            return 4;
                         }
                         else
                         {
                            break;
                         }
                    }
                    else
                    {
                        printf("Contact not found with the given email.\n");
                    }
                    break;
                }

        case '4':  {
                        printf("exiting...");
                        break;
                   }

        default:   {
                       printf("Invalid choice. Please try again.\n");
                       break;
                   }
    }
}while(choice != '4');
}

int editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */
    int num,call=1;
    printf(" \nSearch the contact to edit by:\n");
    printf("-----------------------------------\n");
    int index=searchContact(addressBook,call);
    if(index==4)
    {    
        printf("Enter the serial no. to edit:\n");
        scanf("%d",&num);
        char choice;
        printf("Which field do you wish to edit\n");
        printf("1. name\n2. phone\n3. email\n4. exit\n");
        scanf(" %c",&choice);
        switch(choice)
        {
            case '1' :
                        {
                            char name[20];
                            printf("Edit name\n");
                            scanf(" %[^\n]",name);
                            strcpy(addressBook->contacts[num].name,name);
                            printf("Contact edited successfully\n");
                            break;
                        }
            case '2':
                        {

                            // phone
                            int ret=0;
                            do
                            {
                                char phone[20];
                                printf("Enter the new phone number\n");
                                scanf("%s",phone);
                                ret=validate_phone(phone,addressBook);
                                if(ret)
                                {
                                    strcpy(addressBook->contacts[num].phone,phone);
                                }
                                else
                                {
                                    printf("Please enter a valid phone number\n");
                                }
                            }while(ret==0);
                        }
             case '3':
                        {
                            // email
                            int ret2=0;
                            do
                            {
                                char email[50];
                                printf("Enter your new email\n");
                                scanf("%s",email);
                                ret2=validate_email(email,addressBook);
                                if(ret2)
                                {
                                    strcpy(addressBook->contacts[num].email,email);
                                }
                                else
                                {
                                    printf("Please enter a valid email\n");
                                } 
                            }while(ret2==0);
                        }          
             case '4':
                            printf("Contact edited successfully!\n");
}
 return 0;
}}

void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */
   
}
int validate_phone(char phone[], AddressBook *addressBook)
{
    if(strlen(phone)!=10)
    {
        printf("Invalid phone number. It should be 10 digits long.\n");
        return 0;
    }
    if(phone[0]=='0')
    {
        printf("Invalid phone number. It should not start with 0.\n");
        return 0;
    }
    int i=0;
    while(phone[i])
    {
        if (phone[i] < '0' || phone[i] > '9') 
        {
            printf("Invalid phone number. It should contain only digits.\n");
            return 0;
        }
        i++;
    }
    for(i=0;i<addressBook->contactCount;i++)
    {
        if(strcmp(phone,addressBook->contacts[i].phone)==0)
        {
            printf("Phone number already exists in the address book.\n");
            return 0;
        }
    }
    return 1;
}
int validate_email(char email[], AddressBook *addressBook)
{
    char * pos=0;
    if (email[0]=='@')
    {
        printf("Invalid email. It should not start with '@'.\n");
        return 0;
    }
    if(strchr(email,'@')==NULL)
    {
        printf("Invalid email. It should contain '@'.\n");
        return 0;
    }
    else
    {
        pos=strchr(email,'@');
        if((strcmp((pos+1),".")==0))
        {
            printf("Invalid email. There should be characters between '@' and '.'.\n");
            return 0;
        } 
    }
    if(strcmp(&email[strlen(email)-4],".com")!=0)
    {
        printf("Invalid email. It should end with '.com'.\n");
        return 0;
    }
    int i=0;
    while(email[i])
    {
     if(!islower(email[i]) && isalpha(email[i]))
        {
            printf("Invalid email. It should contain only lowercase letters.\n");
            return 0;
        }
        i++;
    } 
    for(i=0;i<addressBook->contactCount;i++)
    {
        if(strcmp(email,addressBook->contacts[i].email)==0)
        {
            printf("Email already exists in the address book.\n");
            return 0;
        }
    }
    pos=strchr(email,'@');
    if(isalpha(*(pos +1))|| (isalnum(*(pos+1))) )
        {
            return 1;
        }
        else
        {
            return 0;
}
        
    return 1;
}
