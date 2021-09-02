/*****************************************************************
//
//  NAME:        Victor Ho
//
//  HOMEWORK:    Project 1
//
//  CLASS:       ICS 212
//
//  INSTRUCTOR:  Ravi Narayan
//
//  DATE:        March 16, 2021
//
//  FILE:        userinterface.c
//
//  DESCRIPTION:
//   This file contains the UI portion of managing a customer's
//   bank records. Allows you to interact with the database
//   with user inputs. 
//
****************************************************************/

#include <stdio.h>
#include <string.h>

#include "record.h"
#include "database.h"

int debugmode  = 0;

void getaddress(char [], int );
int getNumber(int );


/*****************************************************************
//
//  
//  Function name: main
//
//  DESCRIPTION:   The main function.
//                 Contains the user interface for modifying
//                 customer records. Displays a menu that asks
//                 the user to provide instructions and info.
//
//  Parameters:    argc (int)     : number of arguments
//                 argv (char*[]) : array of arguments
//
//  Return values:  0 : Success
//
****************************************************************/

int main(int argc, char* argv[])
{
    struct record * start = NULL;
    char input[20];
    int loop = 1;
    int length;
    int account;
    char name[25];
    char address[50];
    account = 1;
    if (argc == 1)
    {
        debugmode  = 0;
        printf("Welcome user\n");
    }
    else if (strncmp(argv[1], "debug", 6) == 0 && argc == 2)
    {
        debugmode  = 1;
        printf("***** DEBUG MODE *****\n\n");
    }
    else 
    {
        printf("Error - bad command line argument(s), exiting\n");
        loop = 0;
    }
    if (loop == 1)
    {
        printf("Loading stored consumer records\n");
        if (readfile(&start, "out.txt") == 0)
        {
            printf("Successfully loaded stored records\n");
        }
        else
        {
            printf("No consumer records are stored on this computer\n");
        }
    }
    while (loop == 1)
    {
        printf("\nPlease select a menu option by typing your selection\n");
        printf("add : Add a new record in the database.\n");
        printf("printall : Print all records in the database.\n");
        printf("find : Find record(s) within the database\n");
        printf("delete : Delete existing record(s) from the database.\n");
        printf("quit : Quit the program.\n");
        fgets(input, 20, stdin);
        length = strlen(input) - 1;
        if (strncmp(input, "add", length) == 0)
        {
            printf("add was selected. Please input account number, name, and address\n");
            account = getNumber(account);
            printf("Please enter a name for the account\n");
            fgets(name, 25, stdin);
            name[strlen(name) - 1] = '\0';
            printf("Please enter the address of the account holder\n");
            printf("When you are finished entering the address, input a '$' symbol\n");
            getaddress(address, 50);
            if (addRecord(&start, account, name, address) == 0)
            {
                printf("Success. A new record has been added.\n");
                printf("Account number - %d\n", account);
                printf("Name - %s\n", name);
                printf("Address - %s\n", address);
            }
            else
            {
                printf("Error. Accounts can't have the same account number\n"); 
            }  
        }
        else if (strncmp(input, "printall", length) == 0)
        {
            printf("printall was selected. Printing all records\n");
            printAllRecords(start);
        }
        else if (strncmp(input, "find", length) == 0)
        {
            printf("find was selected. Please input account number to search for.\n");
            account = getNumber(account);
            printf("Searching for %d\n", account);
            findRecord(start, account);
        }
        else if (strncmp(input, "delete", length) == 0)
        {
            printf("delete was selected. Please input number of account to delete\n");
            account = getNumber(account);
            if (deleteRecord(&start, account) == 0) 
            {
                printf("Success. Deleted account with number %d\n", account);
            }
            else
            {
                printf("Error. Account with number %d does not exist\n", account);
            }
        }
        else if (strncmp(input, "quit", length) == 0)
        {
            printf("quit was selected. Quitting the program.\n");
            writefile(start, "out.txt");
            cleanup(&start);
            loop = 0;
        }  
        else
        { 
            printf("Invalid option, please try again\n");
        }   
    }
    return 0;
}

/*****************************************************************
//
//  Function name: getaddress
//
//  DESCRIPTION:   Grabs the address that the user inputs.
//                 Can accept multiple lines, and stops when
//                 user inputs the  character '$', or when
//                 user inputs an address too large.
//
//  Parameters:    add (char[]) : array to store address
//                 size (int)   : maximum size of array
//
****************************************************************/

void getaddress (char add[], int size)
{
    int point;
    char letter;
    char clear[80];
    int condition;
    int i;
    point = 0;
    condition = 1;
    if (debugmode == 1)
    {
        printf("\n*** DEBUG MODE ***\n");
        printf("name = getaddress\n");
        printf("parameters = char add[], int size\n");
        printf("passed add[] = %s, size = %d\n", add, size);
        printf("*** DEBUG MODE ***\n\n");
    }
    for (i = 0; i < size; i += 1) 
    {
        add[i] = '\0';
    }
    while (condition != 0)
    {
        letter = fgetc(stdin);
        if (point == size)
        {
            condition = 0;
            printf("Maximum address length reached\n");
        }
        if (letter != '$')
        {
            add[point] = letter;
            point += 1;
        }
        else
        {
            add[strlen(add)] = '\0';
            condition = 0;
        }
    }
    fgets(clear, 80, stdin);
    return;    
}

/*****************************************************************
//
//  Function name: getNumber
//
//  DESCRIPTION:   Grabs the account number that the user inputs.
//                 If they provide a non-integer, or a negative
//                 number, then the program will keep asking
//                 until a valid number is provided.
//
//  Parameters:    number (int) : The int to store the number
//
//  Return Values: number : The account number the user inputted
//
****************************************************************/

int getNumber (int number)
{
    int result;
    int loop;
    char clear[80];
    if (debugmode == 1)
    {
        printf("\n*** DEBUG MODE ***\n");
        printf("name = getNumber\n");
        printf("parameters = int number\n");
        printf("passed number = %d\n", number);
        printf("*** DEBUG MODE ***\n\n");
    }
    loop = 1;
    while (loop == 1)
    {
        printf("Please input an account number\n");
        result = scanf("%d", &number);
        fgets(clear, 80, stdin);
        if (result != 1)
        {
            printf("Error - Not a number. Please enter a valid number\n");
        }
        else if (number < 0)
        {
            printf("Error - Account number can't be negative\n");    
        }
        else
        {
            loop = 0;
        }       
    }
    return number;    
}

