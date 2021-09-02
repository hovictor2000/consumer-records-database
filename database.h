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
//  FILE:        database.h
//
//  DESCRIPTION:
//   Contains the prototypes for the database functions used
//   to modify records.
//
****************************************************************/

int addRecord (struct record ** , int , char [ ], char [ ]);
void printAllRecords(struct record *);
int findRecord (struct record * , int );
int deleteRecord(struct record ** , int );
int readfile(struct record **, char[]);
int writefile(struct record *, char[]);
void cleanup(struct record **);
