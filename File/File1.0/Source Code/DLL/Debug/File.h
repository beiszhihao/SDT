/*
File
*/
#ifndef _FILE_AGE_
#define _FILE_AGE_
//头文件
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//类型定义
typedef int FILE_FUNC_I;
typedef void FILE_FUNC_V;
typedef bool FILE_FUNC_BL;
typedef char* FILE_FUNC_CP;
typedef FILE* FILE_FUNC_FP;
typedef signed long long int FILE_FUNC_LLI;

//宏定义
#define FILE_CLASS_DLL_PORT  __declspec(dllimport)//导出接口
#define FILE_ERROR 0
#define FILE_SUCCESS 1
//class
class FILE_CLASS_DLL_PORT File{
public:
	//构造
	File();
	//判断文件是否存在
	FILE_FUNC_I JudegFileStay(char *FileName);
	//读文件内容
	FILE_FUNC_CP ReadFile(char* FileName, signed long long int  FileTxT_Seek, bool Seek_End, bool Binary);
	//写文件内容
	FILE_FUNC_I WriteFile(char* FileName, void *Data, signed long long int Size, bool Binary);
	//文件附加
	FILE_FUNC_I WriteFileAdd(char* FileName, void *Data, signed long long int Size, bool Binary);
	//新建文件
	FILE_FUNC_I NewFile(char* FileName);
	//新建文件，文件存储则覆盖
	FILE_FUNC_I NewFileEx(char* FileName);
	//删除文件
	FILE_FUNC_I DeleteFile(char* FileName);
	//移动文件
	FILE_FUNC_I MoveFile(char* FileName1, char* FileName2, bool Binary);
	//复制文件
	FILE_FUNC_I CopyFile(char* FileName1, char* FileName2, bool Binary);
	//获取文件大小
	FILE_FUNC_LLI GetFileSize(char* FileName1);
	//占用文件，并不是所有编译器和系统都支持，该函数会占用文件并且其它程序不可读写
	//同时需要文件支持x特权
	FILE_FUNC_FP OccupyFile(char* FileName);
	//释放
	FILE_FUNC_V ReleteFIle(FILE* FP);
	~File();

private:
	FILE *FILE_P;		//文件指针-保留
	char *FILE_PATH;	//工作路径-保留
};
#endif //--!endif