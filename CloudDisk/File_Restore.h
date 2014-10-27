#ifndef FILERESTORE_H
#define FILERESTORE_H




extern char Output_Name[20];
extern void File_Recover(int length, char **childfile, int childnum);

struct File_Head *File_Inf1;
struct File_Head *File_Inf2;
struct File_Head *File_Inf3;
struct File_Head *File_Inf4;


#endif