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
//  DATE:        March 21, 2021
//
//  FILE:        database.c
//
//  DESCRIPTION:
//   Contains the methods needed to interact
//   with customer records.
//
****************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "record.h"

extern int debugmode;

/*****************************************************************
//
//  Function name: addRecord
//
//  DESCRIPTION:   Adds a record in ascending order. Will fail if
//                 it is given a duplicate account number
//
//  Parameters:    rec (struct record **) - pointer of first record
//                 acc (int) - account number
//                 name (char []) - name of customer
//                 add (char []) - address of customer
//
//  Return values:  0 : Success
//                 -1 : Duplicate account numbers, account not added
//
****************************************************************/

int addRecord (struct record ** rec, int acc, char name[], char add[])
{
    int loop;
    struct record *temp;
    struct record *prev;
    loop = 1;
    temp = * rec;
    prev = NULL;
    if (debugmode == 1)
    {
        printf("\n*** DEBUG MODE ***\n");
        printf("name = addRecord\n");
        printf("parameters = struct record ** rec, int acc, char name[], char add[]\n");
        printf("passed - rec = %p, acc = %d, name = %s, add = %s\n", (void *) rec, acc, name, add);
        printf("*** DEBUG MODE ***\n\n");
    }
    if (*rec == NULL)
    {
        *rec = (struct record *) malloc(sizeof(struct record));
        (**rec).accountno = acc;
        strcpy((**rec).name, name);
        strcpy((**rec).address, add); 
        (**rec).next = NULL;
        loop = 0;
    }
    while (loop == 1)
    {
        if (temp != NULL && (*temp).accountno == acc)
        {
            loop = -1;
        }
        if (temp == NULL || (*temp).accountno > acc)
        {
            if (temp == *rec)
            {
                temp = (struct record *) malloc(sizeof(struct record));
                (*temp).accountno = acc;
                strcpy((*temp).name, name);
                strcpy((*temp).address, add);
                (*temp).next = *rec;
                *rec = temp;
            }
            else 
            {
                temp = (struct record *) malloc(sizeof(struct record));
                (*temp).accountno = acc;
                strcpy((*temp).name, name);
                strcpy((*temp).address, add);
                (*temp).next = (*prev).next;
                (*prev).next = temp;
                loop = 0;
            }
        }
        else
        {
            prev = temp;
            temp = (*temp).next;
        }
    }
    return loop;
}

/*****************************************************************
//
//  Function name: printAllRecords
//
//  DESCRIPTION:   Method to print all records.
//
//  Parameters:    rec (struct record *) - Pointer to the first record
//
****************************************************************/

void printAllRecords(struct record * rec)
{
    int loop;
    if (debugmode == 1)
    {
        printf("\n*** DEBUG MODE ***\n");
        printf("name = printAllRecords\n");
        printf("parameters = struct record * rec\n");
        printf("passed - rec = %p\n", (void *) rec);
        printf("*** DEBUG MODE ***\n\n");
    }
    loop = 1;
    if (rec == NULL)
    {
        printf("\nNo records are currently stored\n");
        loop = 0;
    }
    while (loop == 1)
    {
        printf("\nAccount Number : %d\n", (*rec).accountno);
        printf("Account Name : %s\n", (*rec).name);
        printf("Address : %s\n", (*rec).address);
        rec = (*rec).next;
        if (rec == NULL) 
        {
            loop = 0;
        }    
    }   
    return;
}

/*****************************************************************
//
//  Function name: findRecord
//
//  DESCRIPTION:   Finds a record with the given account number and
//                 prints it. Fails if the record doesn't exist.
//
//  Parameters:    rec (struct record *) - Pointer to first record
//                 acc (int) - account number to look for
//
//  Return values:  0 : Success
//                 -1 : Account doesn't exist
//
****************************************************************/

int findRecord (struct record * rec, int acc)
{
    int loop;
    if (debugmode == 1)
    {
        printf("\n*** DEBUG MODE ***\n");
        printf("name = findRecord\n");
        printf("parameters = struct record * rec, int acc\n");
        printf("passed - rec = %p, acc = %d\n", (void *) rec, acc);
        printf("*** DEBUG MODE ***\n\n");
    }
    loop = 1;
    if (rec == NULL)
    {
        printf("Not found");
        loop = -1;
    }
    while (loop == 1)
    {
        if ((*rec).accountno == acc)
        {
            printf("\nFound account with number %d\n", acc);
            printf("Account name : %s\n", (*rec).name);
            printf("Address : %s\n", (*rec).address);
            loop = 0;
        }
        else
        {
            rec = (*rec).next;
            if (rec == NULL)
            {
                printf("\nAccount with number %d doesn't exist\n", acc);
                loop = -1;
            }
        }
    }
    return loop;
}

/*****************************************************************
//
//  Function name: deleteRecord
//
//  DESCRIPTION:   Attempts to delete the record with the given account number
//
//  Parameters:    rec (struct record **) - Pointer to the first record
//                 acc (int) - the account number to delete
//
//  Return values:  0 : Success
//                 -1 : Account doesn't exist
//
****************************************************************/

int deleteRecord(struct record ** rec, int acc)
{
    int loop;
    struct record * temp;
    struct record * prev;
    if (debugmode == 1)
    {
        printf("\n*** DEBUG MODE ***\n");
        printf("name = deleteRecord\n");
        printf("parameters = struct record **, int acc\n");
        printf("passed - rec = %p, acc = %d\n", (void *) rec, acc);
        printf("*** DEBUG MODE ***\n\n");
    }
    loop = 1;
    temp = *rec;
    prev = NULL;
    while (loop == 1)
    {
        if (temp == NULL)
        {
            loop = -1;
        }
        else if ((*temp).accountno == acc)
        {
            if (temp == *rec)
            {
                *rec = NULL;
            }
            else
            {
                (*prev).next = (*temp).next;
            }
            free(temp);
            loop = 0;
        }
        else
        {
            prev = temp;
            temp = (*temp).next;
        }
    }
    return 0;
}

/*****************************************************************
//
//  Function name: readfile
//
//  DESCRIPTION:   Reads the stored record data in the file and adds it to the
//                 database
//
//  Parameters:    rec (struct record **) - Pointer to the first record
//                 filename (char[]) - Name of file containing stored records
//
//  Return values:  0 : Success
//                 -1 : File not successfully opened
//
****************************************************************/

int readfile(struct record ** rec, char filename[])
{
    FILE * inf;
    int loop;
    int condition;
    int point;
    int accNum;
    int i;
    char letter;
    char accName[25];
    char accAdd[50];
    char clear[80];
    if (debugmode == 1)
    {
        printf("\n*** DEBUG MODE ***\n");
        printf("name = readfile\n");
        printf("parameters = struct record ** rec, char []\n");
        printf("passed - rec = %p, filename = %s\n",(void *) rec, filename);
        printf("*** DEBUG MODE ***\n\n");
    }

    loop = 1;
    inf = fopen(filename, "r");
    if (inf == NULL)
    {
        loop = -1;
    }  
    while (loop == 1)
    {
        if(fscanf(inf, "%d", &accNum) != EOF)
        {
            fgets(clear, 80, inf);
            fgets(accName, 25, inf);
            accName[strlen(accName) - 1] = '\0';
            /* get address */
            for (i = 0; i < 50; i += 1)
            {
                accAdd[i] = '\0';
            }
            condition = 1;
            point = 0;
            while (condition == 1)
            {
                letter = fgetc(inf);
                if (letter != '$')
                {
                    accAdd[point] = letter;
                    point += 1;
                }
                else
                {
                    accAdd[strlen(accAdd) - 1] = '\0';
                    condition = 0;
                }
            }
            fgets(clear, 80, inf);
            addRecord(rec, accNum, accName, accAdd);
        }
        else
        {
            fclose(inf);
            loop = 0;
        }
    }
    return loop;  
}

/*****************************************************************
//
//  Function name: writeFile
//
//  DESCRIPTION:   Writes to given file name to save current records
//
//  Parameters:    rec (struct record *) - Pointer to first record
//                 out (char []) - File name
//
//  Return values:  0 : Success
//                 -1 : File not successfully opened 
//
****************************************************************/

int writefile(struct record * rec, char out[])
{
    FILE * write;
    int loop;
    if (debugmode == 1)
    {
        printf("\n*** DEBUG MODE ***\n");
        printf("name = writefile\n");
        printf("parameters = struct record * rec, char []\n");
        printf("passed - rec = %p, out = %s\n",(void *) rec, out);
        printf("*** DEBUG MODE ***\n\n");
    }
    loop = 1;
    write = fopen(out, "w");
    if (write == NULL)
    {
        loop = -1; 
    }
    if (rec == NULL)
    {
        loop = 0;
    }
    while (loop == 1)
    {
        fprintf(write, "%d\n", (*rec).accountno);
        fprintf(write, "%s\n", (*rec).name);
        fprintf(write, "%s\n", (*rec).address);
        fprintf(write, "$\n");
        rec = (*rec).next;
        if (rec == NULL) 
        {
            fclose(write);
            loop = 0;
        }    
    }   
    return loop;
}


/*****************************************************************
//
//  Function name: cleanup
//
//  DESCRIPTION:   Unallocates memory for all stored records. Used
//                 when user quits
//
//  Parameters:    rec (struct record **) - Pointer to first record
//
****************************************************************/

void cleanup(struct record ** rec)
{
    int loop;
    struct record * temp;
    if (debugmode == 1)
    {
        printf("\n*** DEBUG MODE ***\n");
        printf("name = cleanup\n");
        printf("parameters = struct record **\n");
        printf("passed - rec = %p\n", (void *) rec);
        printf("*** DEBUG MODE ***\n\n");
    }
    temp = NULL;
    loop = 1;
    while (loop == 1)
    {
        if (*rec == NULL)
        {
            temp = NULL;
            loop = 0;
        }
        else
        {
            temp = *rec;
            *rec = (**rec).next;
            free(temp);
        }
    }
    return;
}
