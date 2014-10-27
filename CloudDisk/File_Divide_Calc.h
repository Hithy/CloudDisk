#ifndef FILEDIVIDE_H
#define FILEDIVIDE_H

#define DateType short int



#pragma warning (disable : 4996)

extern long File_Length;
extern short int moderest;
extern char Source[20];



struct File_Head
{
	short int Sign;          // 块标识
	short int Rest_Count;    // 文件尾剩余字节数
	char File_Name[20];      // 文件名称
	char Mod_Rest[20];       // 文件尾剩余内容
	//char Creat_Date[20];     // 文件创建日期
};

/*********声明文件头**********/
struct File_Head *_Part_Point1;
struct File_Head *_Part_Point2;
struct File_Head *_Part_Point3;
struct File_Head *_Part_Point4;
struct File_Head *_Check_Point1;
struct File_Head *_Check_Point2;


extern void Calc_Check(int length, char **childfile, int childnum);
extern void Divide_File(char *filepath, char **childname, int childnum);

#endif