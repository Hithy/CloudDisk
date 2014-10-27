#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "File_Divide_Calc.h"
#include "FileProcess.h"

char Source[20];                                 // 文件名宏定义

DateType Van_2_4[20][20];
long File_Length;
short int moderest;

void Init_Vandmonde()
{
	int i, j;

	for (i = 0; i < 4; i++){
		Van_2_4[0][i] = 1;
	}

	for (j = 0; j < 4; j++){
		Van_2_4[1][j] = j + 1;
	}
}

void Calc_Check(int length, char **childfile, int childnum)
{
	int i;
	DateType Temp1;
	DateType Temp2;
	DateType Temp3;
	DateType Temp4;
	DateType Temp_All;

	Init_Vandmonde();

	FILE *Part1 = fopen(childfile[0], "rb");
	FILE *Part2 = fopen(childfile[1], "rb");
	FILE *Part3 = fopen(childfile[2], "rb");
	FILE *Part4 = fopen(childfile[3], "rb");
	FILE *Check1 = fopen(childfile[4], "ab");
	FILE *Check2 = fopen(childfile[5], "ab");

	fseek(Part1, sizeof(struct File_Head), SEEK_SET);
	fseek(Part2, sizeof(struct File_Head), SEEK_SET);
	fseek(Part3, sizeof(struct File_Head), SEEK_SET);
	fseek(Part4, sizeof(struct File_Head), SEEK_SET);
	fseek(Check1, sizeof(struct File_Head), SEEK_SET);
	fseek(Check2, sizeof(struct File_Head), SEEK_SET);

	for (i = 0; i < length / 4; i++){
		Temp1 = fgetc(Part1);
		if (!feof(Part1)){
			Temp2 = fgetc(Part2);
			Temp3 = fgetc(Part3);
			Temp4 = fgetc(Part4);

			Temp_All = Temp1 * Van_2_4[0][0] + Temp2 * Van_2_4[0][1] + Temp3 * Van_2_4[0][2] + Temp4 * Van_2_4[0][3];

			fwrite(&Temp_All, sizeof(DateType), 1, Check1);
		}
	}
	fclose(Check1);

	fseek(Part1, sizeof(struct File_Head), SEEK_SET);
	fseek(Part2, sizeof(struct File_Head), SEEK_SET);
	fseek(Part3, sizeof(struct File_Head), SEEK_SET);
	fseek(Part4, sizeof(struct File_Head), SEEK_SET);

	for (i = 0; i < length / 4; i++){
		Temp1 = fgetc(Part1);
		if (!feof(Part1)){
			Temp2 = fgetc(Part2);
			Temp3 = fgetc(Part3);
			Temp4 = fgetc(Part4);

			Temp_All = Temp1 * Van_2_4[1][0] + Temp2 * Van_2_4[1][1] + Temp3 * Van_2_4[1][2] + Temp4 * Van_2_4[1][3];

			fwrite(&Temp_All, sizeof(DateType), 1, Check2);
		}
	}
	fclose(Check2);

	fclose(Part1);
	fclose(Part2);
	fclose(Part3);
	fclose(Part4);

}

long Get_Length(FILE *in)                       // 获取文件长度
{
	fseek(in, 0, SEEK_END);
	long total = ftell(in);
	fseek(in, 0, SEEK_SET);
	printf("\n\nthe length is %ld !\n\n", total);

	return total;
}

void Init_EachPart(short int restcont, char moderest[20])        // 初始化各文件头
{
	_Part_Point1 = (struct File_Head *)malloc(sizeof(struct File_Head));
	_Part_Point2 = (struct File_Head *)malloc(sizeof(struct File_Head));
	_Part_Point3 = (struct File_Head *)malloc(sizeof(struct File_Head));
	_Part_Point4 = (struct File_Head *)malloc(sizeof(struct File_Head));
	_Check_Point1 = (struct File_Head *)malloc(sizeof(struct File_Head));
	_Check_Point2 = (struct File_Head *)malloc(sizeof(struct File_Head));

	_Part_Point1->Sign = 1;
	_Part_Point2->Sign = 2;
	_Part_Point3->Sign = 3;
	_Part_Point4->Sign = 4;
	_Check_Point1->Sign = 5;
	_Check_Point2->Sign = 6;

	_Part_Point1->Rest_Count = restcont;
	_Part_Point2->Rest_Count = restcont;
	_Part_Point3->Rest_Count = restcont;
	_Part_Point4->Rest_Count = restcont;
	_Check_Point1->Rest_Count = restcont;
	_Check_Point2->Rest_Count = restcont;

	strcpy(_Part_Point1->Mod_Rest, moderest);
	strcpy(_Part_Point2->Mod_Rest, moderest);
	strcpy(_Part_Point3->Mod_Rest, moderest);
	strcpy(_Part_Point4->Mod_Rest, moderest);
	strcpy(_Check_Point1->Mod_Rest, moderest);
	strcpy(_Check_Point2->Mod_Rest, moderest);

	strcpy(_Part_Point1->File_Name, Source);
	strcpy(_Part_Point2->File_Name, Source);
	strcpy(_Part_Point3->File_Name, Source);
	strcpy(_Part_Point4->File_Name, Source);
	strcpy(_Check_Point1->File_Name, Source);
	strcpy(_Check_Point2->File_Name, Source);
}

void Divide_File(char *filepath, char **childname, int childnum)      //  分割文件
{
	int i;
	char temp;
	char restsymbol[4];

	FILE *Orign_File = fopen(filepath, "rb");
	char *__Part1 = childname[0];
	char *__Part2 = childname[1];
	char *__Part3 = childname[2];
	char *__Part4 = childname[3];
	char *__Check1 = childname[4];
	char *__Check2 = childname[5];

	strcat(__Part1, Source);
	strcat(__Part2, Source);
	strcat(__Part3, Source);
	strcat(__Part4, Source);
	strcat(__Check1, Source);
	strcat(__Check2, Source);

	FILE *UndoFile;
	FILE *Part1 = fopen(__Part1, "ab");
	FILE *Part2 = fopen(__Part2, "ab");
	FILE *Part3 = fopen(__Part3, "ab");
	FILE *Part4 = fopen(__Part4, "ab");
	FILE *Check1 = fopen(__Check1, "ab");
	FILE *Check2 = fopen(__Check2, "ab");

	File_Length = Get_Length(Orign_File);
	moderest = File_Length % 4;

	UndoFile = fopen("UndoFile", "wb");
	for (i = 0; i < File_Length - moderest; i++){
		fputc(fgetc(Orign_File), UndoFile);
	}
	fclose(UndoFile);

	fread(restsymbol, moderest, 1, Orign_File);
	fclose(Orign_File);

	Init_EachPart(moderest, restsymbol);
	fwrite(_Part_Point1, sizeof(struct File_Head), 1, Part1);
	fwrite(_Part_Point2, sizeof(struct File_Head), 1, Part2);
	fwrite(_Part_Point3, sizeof(struct File_Head), 1, Part3);
	fwrite(_Part_Point4, sizeof(struct File_Head), 1, Part4);
	fwrite(_Check_Point1, sizeof(struct File_Head), 1, Check1);
	fwrite(_Check_Point2, sizeof(struct File_Head), 1, Check2);

	UndoFile = fopen("UndoFile", "rb");

	for (i = 1; i <= (File_Length - moderest) / 4; i++){
		temp = fgetc(UndoFile);
		if (!feof(UndoFile))
			fputc(temp, Part1);
		else
			break;
	}

	for (i = 1; i <= (File_Length - moderest) / 4; i++){
		temp = fgetc(UndoFile);
		if (!feof(UndoFile))
			fputc(temp, Part2);
		else
			break;
	}

	for (i = 1; i <= (File_Length - moderest) / 4; i++){
		temp = fgetc(UndoFile);
		if (!feof(UndoFile))
			fputc(temp, Part3);
		else
			break;
	}

	for (i = 1; i <= (File_Length - moderest) / 4; i++){
		temp = fgetc(UndoFile);
		if (!feof(UndoFile))
			fputc(temp, Part4);
		else
			break;
	}

	fclose(Part1);
	fclose(Part2);
	fclose(Part3);
	fclose(Part4);
	fclose(UndoFile);
	fclose(Check1);
	fclose(Check2);

	remove("UndoFile");
}

