#include "FileProcess.h"
extern "C" {
	#include "File_Restore.h"
	#include "File_Divide_Calc.h"
	void Calc_Check(int length, char **childfile, int childnum);
	void Divide_File(char *filepath, char **childname, int childnum);
	void File_Recover(int length, char **childfile, int childnum);
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *GetFilename(char *p)
{
	//int x = strlen(p);
	char ch = '\\';
	char *q = strrchr(p, ch) + 1;

	return q;
}

bool file_divide(char *filename, char **childname, int childnum)
{
	
	strcpy(Source, GetFilename(filename));
	Divide_File(filename, childname, 6);
	Calc_Check(File_Length - moderest, childname, 6);
	return true;

}

bool file_recover(char **childname, int childnum)
{
	File_Inf1 = (struct File_Head *)malloc(sizeof(struct File_Head));
	File_Inf2 = (struct File_Head *)malloc(sizeof(struct File_Head));
	File_Inf3 = (struct File_Head *)malloc(sizeof(struct File_Head));
	File_Inf4 = (struct File_Head *)malloc(sizeof(struct File_Head));

	int length;
	FILE *fp = fopen(childname[0], "rb");
	fseek(fp, 0, SEEK_END); //定位到文件末 
	length = ftell(fp); //文件长度
	fclose(fp);
	length -= sizeof(struct File_Head);

	length *= 4;

	File_Recover(length, childname, childnum);


	free(File_Inf1);
	free(File_Inf2);
	free(File_Inf3);
	free(File_Inf4);
	return true;
}