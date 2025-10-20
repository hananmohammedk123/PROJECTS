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
    //populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
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

int searchContact(AddressBook *addressBook,int call,int arr[]) 
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
            case '1':
                    {
                        char name[50];
                        printf("Enter the name to search: ");
                        scanf(" %[^\n]", name);
                        int flag=0;
                        printf("------------------------------------------------------------------\n");
                        int n=0;
                        for(int i=0;i<addressBook->contactCount;i++)
                        { 
                            if(strstr(addressBook->contacts[i].name,name)!=NULL)
                            {
                                printf("%d -> Name: %s\t Phone: %s\t Email: %s\n",n+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                                flag=1;
                                if(call==1) //check whether it is called from another function(edit/delete)
                                {
                                    arr[n]=i;
                                    n++;
                                }
                                else
                                     n++;
                            }
                        }
                        if(flag)
                        {
                            printf("------------------------------------------------------------------\n");
                            if(call==1)
                            {
                                return 2;
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
                        break;
                    }

            case '2':
                    {
                        char phone[20];
                        printf("Enter the phone number to search: ");
                        scanf("%s", phone);
                        int flag=0;
                        int n=1;
                        printf("------------------------------------------------------------------\n");
                        for(int i=0;i<addressBook->contactCount;i++)
                        {
                            if(strcmp(addressBook->contacts[i].phone,phone)==0)
                            {
                                printf("%d -> Name: %s\t Phone: %s\t Email: %s\n",n, addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                                flag=1;
                                if(call==1)
                                {
                                    arr[0]=i;
                                    n++;
                                }
                            }
                        }
                        if(flag)
                        {
                            printf("------------------------------------------------------------------\n");
                            if(call==1)
                            {
                                return 1;
                            }
                            else
                            {
                                break;
                            }
                        }
                        else
                        {
                            printf("Contact not found with the given phone number.\n");
                            printf("------------------------------------------------------------------\n");
                        }
                        break;
                    }

        case '3':   { 
                        char email[50];
                        printf("Enter the email to search: ");
                        scanf("%s", email);
                        int flag=0;
                        int n=1;
                        printf("------------------------------------------------------------------\n");
                        for(int i=0;i<addressBook->contactCount;i++)
                        {
                            if(strcmp(addressBook->contacts[i].email,email)==0)
                            {
                                printf("%d ->Name: %s\t Phone: %s\t Email: %s\n",n,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                                flag=1;
                                if(call==1)
                                {
                                n++;
                                arr[0]=i;
                                }
                            }
                        }
                        if(flag)
                        {
                             printf("------------------------------------------------------------------\n");
                            if(call==1)
                            {
                                return 1;
                            }
                            else
                            {
                                break;
                            }
                        }
                        else
                        {
                            printf("Contact not found with the given email.\n");
                            printf("------------------------------------------------------------------\n");
                        }
                        break;
                    }

         case '4':  {
                        printf("exiting...");
                        return 0;
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
    char choice;
    int arr[100];
    printf(" \nEDIT CONTACT:\n");
    printf("---------------\n");
    
    do
    {   
        int index=searchContact(addressBook,call,arr);
        if (index==0)
        {
            return 0;// exiting;
        }
        else if(index==1 || index==2)
        {
            if(index==2)
            {
                printf("Enter the serial no. to edit:\n");
                scanf("%d",&num);
                num=arr[num-1];
            }
            else if(index==1)
            {
                num=arr[0];
            }
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
                                        printf("Contact edited successfully!\n");
                                    }
                                    else
                                    {
                                        printf("Please enter a valid phone number\n");
                                    }
                                }while(ret==0);
                                break;
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
                                        printf("Contact edited successfully!\n");
                                    }
                                    else
                                    {
                                        printf("Please enter a valid email\n");
                                    } 
                                }while(ret2==0);
                                break;
                            }          
                case '4':
                                break;
                default :   
                                printf("Invalid entry.please retry.");
                                break;                
            }
        }
      
    } while(choice != '4');
                return 0;     
}

void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */
    int arr2[100];
    int call=1,exit=0;
    printf(" \nDELETE CONTACT:\n");
    printf("---------------\n");
    do
    {
        int num=0,flag=0;
        int index=searchContact(addressBook,call,arr2);
        if (index==0)
        {
            exit=1;// exiting;
        }
        else if(index==1 || index==2)
        {
            char choice;
            if(index==2)
            {
                printf("Enter the serial no. to Delete:\n");
                scanf("%d",&num);
                num=arr2[num-1];
                do
                {
                    printf("Do you want to delete this contact permanently? (y/n):\n");
                    scanf(" %c",&choice);
                    if(choice=='y'|| choice =='Y')
                    flag=1;
                    else if(choice =='n' || choice =='N')
                    flag=2;
                    else
                    printf("invalid choice\n");
                }while(flag==0);
            }
            else if(index==1)
            {
                num=arr2[0];
                do
                {
                    printf("Do you want to delete this contact permanently? (y/n):\n");
                    scanf(" %c",&choice);
                    if(choice=='y'|| choice =='Y')
                    flag=1;
                    else if(choice =='n' || choice =='N')
                    flag=2;
                    else
                    printf("invalid choice\n");
                }while(flag==0);
            }
        }
        if(flag==1)
        {
            for(int i=num;i<addressBook->contactCount;i++)
            {
                addressBook->contacts[i]=addressBook->contacts[i+1];
            }
            addressBook->contactCount--;
            exit=1;
            printf("Contact Deleted Successfully\n");
            printf("----------------------------\n");
        }
        else if(flag==2)
        {
            continue;
        }
        /* code */
    } while (exit!=1);
   
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
        if (pos != NULL && *(pos + 1) == '.')
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
