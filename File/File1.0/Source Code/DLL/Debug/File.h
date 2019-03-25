/*
File
*/
#ifndef _FILE_AGE_
#define _FILE_AGE_
//ͷ�ļ�
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//���Ͷ���
typedef int FILE_FUNC_I;
typedef void FILE_FUNC_V;
typedef bool FILE_FUNC_BL;
typedef char* FILE_FUNC_CP;
typedef FILE* FILE_FUNC_FP;
typedef signed long long int FILE_FUNC_LLI;

//�궨��
#define FILE_CLASS_DLL_PORT  __declspec(dllimport)//�����ӿ�
#define FILE_ERROR 0
#define FILE_SUCCESS 1
//class
class FILE_CLASS_DLL_PORT File{
public:
	//����
	File();
	//�ж��ļ��Ƿ����
	FILE_FUNC_I JudegFileStay(char *FileName);
	//���ļ�����
	FILE_FUNC_CP ReadFile(char* FileName, signed long long int  FileTxT_Seek, bool Seek_End, bool Binary);
	//д�ļ�����
	FILE_FUNC_I WriteFile(char* FileName, void *Data, signed long long int Size, bool Binary);
	//�ļ�����
	FILE_FUNC_I WriteFileAdd(char* FileName, void *Data, signed long long int Size, bool Binary);
	//�½��ļ�
	FILE_FUNC_I NewFile(char* FileName);
	//�½��ļ����ļ��洢�򸲸�
	FILE_FUNC_I NewFileEx(char* FileName);
	//ɾ���ļ�
	FILE_FUNC_I DeleteFile(char* FileName);
	//�ƶ��ļ�
	FILE_FUNC_I MoveFile(char* FileName1, char* FileName2, bool Binary);
	//�����ļ�
	FILE_FUNC_I CopyFile(char* FileName1, char* FileName2, bool Binary);
	//��ȡ�ļ���С
	FILE_FUNC_LLI GetFileSize(char* FileName1);
	//ռ���ļ������������б�������ϵͳ��֧�֣��ú�����ռ���ļ������������򲻿ɶ�д
	//ͬʱ��Ҫ�ļ�֧��x��Ȩ
	FILE_FUNC_FP OccupyFile(char* FileName);
	//�ͷ�
	FILE_FUNC_V ReleteFIle(FILE* FP);
	~File();

private:
	FILE *FILE_P;		//�ļ�ָ��-����
	char *FILE_PATH;	//����·��-����
};
#endif //--!endif