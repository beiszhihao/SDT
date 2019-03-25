/*
File
*/
#include "File.h"
/*
����
*/
File::File() :FILE_P(NULL), FILE_PATH(NULL){}

/*
�ж��ļ��Ƿ����
*/
//�ж��ļ��Ƿ����
FILE_FUNC_I File::JudegFileStay(char *FileName){
	FILE *fp = fopen(FileName, "r+");
	if (fp == NULL){
		return FILE_ERROR;
	}
	fclose(fp);
	return FILE_SUCCESS;
}

/*
��д�ļ�
*/
//���ļ�����
FILE_FUNC_CP File::ReadFile(char* FileName, signed long long int  FileTxT_Seek = 0L, bool Seek_End = false, bool Binary = false){
	if (FILE_ERROR == this->JudegFileStay(FileName)){
		return FILE_ERROR;
	}
	FILE *fp = NULL;
	if (Binary == true){
		fp = fopen(FileName, "rb+");
	}
	else{
		fp = fopen(FileName, "r+");
	}
	if (fp == NULL){
		return FILE_ERROR;
	}
	fseek(fp, 0L, SEEK_END);
	signed long long int size = ftell(fp);
	fseek(fp, 0L, SEEK_SET);
	char* FileTxt = (char*)malloc((size + 1) - FileTxT_Seek);
	if (FileTxt == NULL){
		return FILE_ERROR;
	}
	memset(FileTxt, 0, (size + 1) - FileTxT_Seek);
	if (Seek_End == true){
		fseek(fp, FileTxT_Seek, SEEK_END);
	}
	else{
		fseek(fp, FileTxT_Seek, SEEK_SET);
	}
	fread(FileTxt, (size + 1) - FileTxT_Seek, 1, fp);
	if (FileTxt == NULL){
		return FILE_ERROR;
	}
	fclose(fp);
	return FileTxt;

}
//д�ļ�����
FILE_FUNC_I File::WriteFile(char* FileName, void *Data, signed long long int Size, bool Binary = false){
	if (FILE_ERROR == this->JudegFileStay(FileName)){
		return FILE_ERROR;
	}
	FILE *fp = NULL;
	if (Binary == true){
		fp = fopen(FileName, "wb+");
	}
	else{
		fp = fopen(FileName, "w+");
	}
	fwrite(Data, Size, 1, fp);
	fclose(fp);
	return FILE_SUCCESS;
}
//�ļ�����
FILE_FUNC_I File::WriteFileAdd(char* FileName, void *Data, signed long long int Size, bool Binary = false){
	if (FILE_ERROR == this->JudegFileStay(FileName)){
		return FILE_ERROR;
	}
	FILE *fp = NULL;
	if (Binary == true){
		fp = fopen(FileName, "ab+");
	}
	else{
		fp = fopen(FileName, "at+");
	}
	fwrite(Data, Size, 1, fp);
	fclose(fp);
	return FILE_SUCCESS;
}

/*
�½��ļ�
*/
//�½��ļ�
FILE_FUNC_I File::NewFile(char* FileName){
	if (FILE_ERROR == this->JudegFileStay(FileName)){
		return FILE_ERROR;
	}
	FILE *fp = fopen(FileName, "w+");
	fclose(fp);
	return FILE_SUCCESS;
}
//�½��ļ����ļ��洢�򸲸�
FILE_FUNC_I File::NewFileEx(char* FileName){
	FILE *fp = fopen(FileName, "w+");
	fclose(fp);
	return FILE_SUCCESS;
}

/*
ɾ���ļ�
*/
//ɾ���ļ�
FILE_FUNC_I File::DeleteFile(char* FileName){
	if (-1 == remove(FileName)){
		return FILE_ERROR;
	}
	return FILE_SUCCESS;
}

/*
�ƶ��ļ�
*/
//�ƶ��ļ�
FILE_FUNC_I File::MoveFile(char* FileName1, char* FileName2, bool Binary = false){
	if (FILE_ERROR == this->JudegFileStay(FileName1)){
		return FILE_ERROR;
	}
	char* Str1 = this->ReadFile(FileName1, 0, false, Binary);
	this->NewFileEx(FileName2);
	this->WriteFile(FileName2, Str1, strlen(Str1), Binary);
	this->DeleteFile(FileName1);
	return FILE_SUCCESS;
}

/*
�����ļ�
*/
//�����ļ�
FILE_FUNC_I File::CopyFile(char* FileName1, char* FileName2, bool Binary = false){
	if (FILE_ERROR == this->JudegFileStay(FileName1)){
		return FILE_ERROR;
	}
	char* Str1 = this->ReadFile(FileName1, 0, false, Binary);
	this->NewFileEx(FileName2);
	this->WriteFile(FileName2, Str1, strlen(Str1), Binary);
	return FILE_SUCCESS;
}

/*
ռ���ļ�
*/
//ռ���ļ������������б�������ϵͳ��֧�֣��ú�����ռ���ļ������������򲻿ɶ�д
//ͬʱ��Ҫ�ļ�֧��x��Ȩ
FILE_FUNC_FP File::OccupyFile(char* FileName){
	if (FILE_ERROR == this->JudegFileStay(FileName)){
		return FILE_ERROR;
	}
	FILE *fp = NULL;
	fp = fopen(FileName, "x");
	return fp;
}

/*
��ȡ�ļ���С
*/
FILE_FUNC_LLI File::GetFileSize(char* FileName){
	if (FILE_ERROR == this->JudegFileStay(FileName)){
		return FILE_ERROR;
	}
	FILE *fp = NULL;
	fp = fopen(FileName, "r+");
	fseek(fp, 0L, SEEK_END);
	signed long long int size = ftell(fp);
	fseek(fp, 0L, SEEK_SET);
	fclose(fp);
	return size;
}

/*
�ͷ�
*/
//�ͷ�
FILE_FUNC_V File::ReleteFIle(FILE* FP){
	fclose(FP);
	FP = NULL;
}
File::~File(){}