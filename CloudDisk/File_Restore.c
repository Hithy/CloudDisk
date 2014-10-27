
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "File_Restore.h"
#include "File_Divide_Calc.h"
#include "FileProcess.h"

char Output_Name[20];


double A_1_2[4][4] = { { 1, 2, 2, -1 }, { -2, -3, -1, 1 }, { 1, 0, 0, 0 }, { 0, 1, 0, 0 } };
double A_1_3[4][4] = { { -0.5, 0.5, 1.5, -0.5 }, { 1, 0, 0, 0 }, { -0.5, -1.5, -0.5, 0.5 }, { 0, 1, 0, 0 } };
double A_1_4[4][4] = { { -0.66666667, -0.333333, 1.3333333, -0.333333 }, { 1, 0, 0, 0 }, { 0, 1, 0, 0 }, { -0.3333333, -0.66666667, -0.33333333, 0.3333333 } };
double A_1_5[4][4] = { { -2, -3, -4, 1 }, { 1, 0, 0, 0 }, { 0, 1, 0, 0 }, { 0, 0, 1, 0 } };
double A_1_6[4][4] = { { -1, -1, -1, 1 }, { 1, 0, 0, 0 }, { 0, 1, 0, 0 }, { 0, 0, 1, 0 } };
double A_2_3[4][4] = { { 1, 0, 0, 0 }, { -2, 1, 3, -1 }, { 1, -2, -2, 1 }, { 0, 1, 0, 0 } };
double A_2_4[4][4] = { { 1, 0, 0, 0 }, { -1.5, -0.5, 2, -0.5 }, { 0, 1, 0, 0 }, { 0.5, -0.5, -1, 0.5 } };
double A_2_5[4][4] = { { 1, 0, 0, 0 }, { -0.5, -1.5, -2, 0.5 }, { 0, 1, 0, 0 }, { 0, 0, 1, 0 } };
double A_2_6[4][4] = { { 1, 0, 0, 0 }, { -1, -1, -1, 1 }, { 0, 1, 0, 0 }, { 0, 0, 1, 0 } };
double A_3_4[4][4] = { { 1, 0, 0, 0 }, { 0, 1, 0, 0 }, { -3, -2, 4, -1 }, { 2, 1, -3, 1 } };
double A_3_5[4][4] = { { 1, 0, 0, 0 }, { 0, 1, 0, 0 }, { -0.333333333, -0.666666667, -1.3333333333, 0.3333333333333 }, { 0, 0, 1, 0 } };
double A_3_6[4][4] = { { 1, 0, 0, 0 }, { 0, 1, 0, 0 }, { -1, -1, -1, 1 }, { 0, 0, 1, 0 } };
double A_4_5[4][4] = { { 1, 0, 0, 0 }, { 0, 1, 0, 0 }, { 0, 0, 1, 0 }, { -0.25, -0.5, -0.75, 0.25 } };
double A_4_6[4][4] = { { 1, 0, 0, 0 }, { 0, 1, 0, 0 }, { 0, 0, 1, 0 }, { -1, -1, -1, 1 } };
double A_5_6[4][4] = { { 1, 0, 0, 0 }, { 0, 1, 0, 0 }, { 0, 0, 1, 0 }, { 0, 0, 0, 1 } };


void Recover_Calc(int length, FILE *Calc1, FILE*  Calc2, FILE *Calc3, FILE *Calc4, double Array[][4])
{
	short int tempp;
	short int part1;
	short int part2;
	short int part3;
	short int part4;
	int i;
	FILE *Output;

	strcpy(Output_Name, "_");
	strcat(Output_Name, File_Inf1->File_Name);
	Output = fopen(Output_Name, "wb");

	for (i = 0; i < 4; i++){
		for (int j = 0; j < length / 4; j++){
			part1 = fgetc(Calc1);
			part2 = fgetc(Calc2);
			if (File_Inf3->Sign <= 4){
				part3 = fgetc(Calc3);
			}
			else {
				fread(&part3, sizeof(short int), 1, Calc3);
			}

			if (File_Inf4->Sign <= 4){
				part4 = fgetc(Calc4);
			}
			else {
				fread(&part4, sizeof(short int), 1, Calc4);
			}

			tempp = (short int)((double)part1 * Array[i][0] + (double)part2 * Array[i][1] + (double)part3 * Array[i][2] + (double)part4 * Array[i][3] + 0.5);

			fputc(tempp, Output);
		}
		fseek(Calc1, sizeof(struct File_Head), SEEK_SET);
		fseek(Calc2, sizeof(struct File_Head), SEEK_SET);
		fseek(Calc3, sizeof(struct File_Head), SEEK_SET);
		fseek(Calc4, sizeof(struct File_Head), SEEK_SET);
	}

	fclose(Calc1);
	fclose(Calc2);
	fclose(Calc3);
	fclose(Calc4);

	fseek(Output, 0, SEEK_END);
	fwrite(File_Inf1->Mod_Rest, File_Inf1->Rest_Count, 1, Output);
	fclose(Output);
}

void File_Recover(int length, char **childfile,int childnum)
{
	FILE *Point[7] = { NULL };
	int Select[4];
	int count = 0;
	int sum = 0;
	int lost1[2];

	FILE *Disk1;
	FILE *Disk2;
	FILE *Disk3;
	FILE *Disk4;

	char *__Part1 = childfile[0];
	char *__Part2 = childfile[1];
	char *__Part3 = childfile[2];
	char *__Part4 = childfile[3];

	Disk1 = fopen(__Part1, "rb");
	Disk2 = fopen(__Part2, "rb");
	Disk3 = fopen(__Part3, "rb");
	Disk4 = fopen(__Part4, "rb");

	fread(File_Inf1, sizeof(struct File_Head), 1, Disk1);
	fread(File_Inf2, sizeof(struct File_Head), 1, Disk2);
	fread(File_Inf3, sizeof(struct File_Head), 1, Disk3);
	fread(File_Inf4, sizeof(struct File_Head), 1, Disk4);

	for (int i = 0; i < 4; i++){
		Point[File_Inf1->Sign] = Disk1;
		Point[File_Inf2->Sign] = Disk2;
		Point[File_Inf3->Sign] = Disk3;
		Point[File_Inf4->Sign] = Disk4;
	}

	for (int j = 1; j <= 6; j++){
		if (Point[j] != NULL){
			Select[count] = j;
			++count;
		}
		else {
			lost1[sum] = j;
			++sum;
		}
	}

	if (lost1[0] == 1 && lost1[1] == 2){
		Recover_Calc(length, Point[Select[0]], Point[Select[1]], Point[Select[2]], Point[Select[3]], A_1_2);
	}
	else if (lost1[0] == 1 && lost1[1] == 3){
		Recover_Calc(length, Point[Select[0]], Point[Select[1]], Point[Select[2]], Point[Select[3]], A_1_3);
	}
	else if (lost1[0] == 1 && lost1[1] == 4){
		Recover_Calc(length, Point[Select[0]], Point[Select[1]], Point[Select[2]], Point[Select[3]], A_1_4);
	}
	else if (lost1[0] == 1 && lost1[1] == 5){
		Recover_Calc(length, Point[Select[0]], Point[Select[1]], Point[Select[2]], Point[Select[3]], A_1_5);
	}
	else if (lost1[0] == 1 && lost1[1] == 6){
		Recover_Calc(length, Point[Select[0]], Point[Select[1]], Point[Select[2]], Point[Select[3]], A_1_6);
	}
	else if (lost1[0] == 2 && lost1[1] == 3){
		Recover_Calc(length, Point[Select[0]], Point[Select[1]], Point[Select[2]], Point[Select[3]], A_2_3);
	}
	else if (lost1[0] == 2 && lost1[1] == 4){
		Recover_Calc(length, Point[Select[0]], Point[Select[1]], Point[Select[2]], Point[Select[3]], A_2_4);
	}
	else if (lost1[0] == 2 && lost1[1] == 5){
		Recover_Calc(length, Point[Select[0]], Point[Select[1]], Point[Select[2]], Point[Select[3]], A_2_5);
	}
	else if (lost1[0] == 2 && lost1[1] == 6){
		Recover_Calc(length, Point[Select[0]], Point[Select[1]], Point[Select[2]], Point[Select[3]], A_2_6);
	}
	else if (lost1[0] == 3 && lost1[1] == 4){
		Recover_Calc(length, Point[Select[0]], Point[Select[1]], Point[Select[2]], Point[Select[3]], A_3_4);
	}
	else if (lost1[0] == 3 && lost1[1] == 5){
		Recover_Calc(length, Point[Select[0]], Point[Select[1]], Point[Select[2]], Point[Select[3]], A_3_5);
	}
	else if (lost1[0] == 3 && lost1[1] == 6){
		Recover_Calc(length, Point[Select[0]], Point[Select[1]], Point[Select[2]], Point[Select[3]], A_3_6);
	}
	else if (lost1[0] == 4 && lost1[1] == 5){
		Recover_Calc(length, Point[Select[0]], Point[Select[1]], Point[Select[2]], Point[Select[3]], A_4_5);
	}
	else if (lost1[0] == 4 && lost1[1] == 6){
		Recover_Calc(length, Point[Select[0]], Point[Select[1]], Point[Select[2]], Point[Select[3]], A_4_6);
	}
	else if (lost1[0] == 5 && lost1[1] == 6){
		Recover_Calc(length, Point[Select[0]], Point[Select[1]], Point[Select[2]], Point[Select[3]], A_5_6);
	}
}
