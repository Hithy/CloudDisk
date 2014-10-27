#ifndef FILEDIVIDE_H
#define FILEDIVIDE_H

#define DateType short int



#pragma warning (disable : 4996)

extern long File_Length;
extern short int moderest;
extern char Source[20];



struct File_Head
{
	short int Sign;          // ���ʶ
	short int Rest_Count;    // �ļ�βʣ���ֽ���
	char File_Name[20];      // �ļ�����
	char Mod_Rest[20];       // �ļ�βʣ������
	//char Creat_Date[20];     // �ļ���������
};

/*********�����ļ�ͷ**********/
struct File_Head *_Part_Point1;
struct File_Head *_Part_Point2;
struct File_Head *_Part_Point3;
struct File_Head *_Part_Point4;
struct File_Head *_Check_Point1;
struct File_Head *_Check_Point2;


extern void Calc_Check(int length, char **childfile, int childnum);
extern void Divide_File(char *filepath, char **childname, int childnum);

#endif