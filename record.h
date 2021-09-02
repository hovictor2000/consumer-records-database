/*****************************************************************
//
//  NAME:        Victor Ho
//
//  HOMEWORK:    3b
//
//  CLASS:       ICS 212
//
//  INSTRUCTOR:  Ravi Narayan
//
//  DATE:        March 16, 2021
//
//  FILE:        record.h
//
//  DESCRIPTION:
//   Contains the prototype for the structure for account records
//
****************************************************************/

struct record
{
    int               accountno;
    char              name[25];
    char              address[50];
    struct record*    next;
};
