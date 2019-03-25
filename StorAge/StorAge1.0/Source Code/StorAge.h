/*
CharString类
*/
#ifndef _STOR_AGE_
#define _STOR_AGE_

//标准处理头文件
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//宏定义
#define STORAGE_ERROR 0
#define STORAGE_SUCCESS 1

//类型定义
typedef int STORAGE_FUNC_I;
typedef void STORAGE_FUNC_V;
typedef bool STORAGE_FUNC_BL;
typedef char* STORAGE_FUNC_CP;

//字符字段统一符定义
#define LIST_I '/'
#define LIST_H '='
#define LIST_IS "/"
#define LIST_HS "="
#define STO_CLASS_DLL_PORT _declspec(dllexport) //导出接口
template<class T>
class STO_CLASS_DLL_PORT List{
public:
	//默认构造
	List();
	//长度构造
	List(int Len);
	//修改数据
	STORAGE_FUNC_I Modify(int ArrIndex, T IutPut_Data);
	//数据置0
	STORAGE_FUNC_V DataMet();
	//获取头索引
	STORAGE_FUNC_I Hand();
	//获取尾索引
	STORAGE_FUNC_I End();
	//获取中间索引
	STORAGE_FUNC_I In();
	//寻找数据
	STORAGE_FUNC_BL SeekData(T SeekData);
	STORAGE_FUNC_BL SeekDataToIndex(T SeekData);
	//获取数据
	T GetData(int ArrIndex);
	//扩充增加
	STORAGE_FUNC_I ExpanSion(int Len);
	//动态变更
	STORAGE_FUNC_I ExpanSionEx(int Len);
	//Add增加
	STORAGE_FUNC_I Add(T ADD_Data);
	//获取大小
	STORAGE_FUNC_I GetSize();
	//重新增长
	STORAGE_FUNC_V ReGrow(int Len);
	//删除
	STORAGE_FUNC_I Delete(int Len);
	//删除指定位置上的数据
	STORAGE_FUNC_I DeleteIndex(int Index);
	//释放
	STORAGE_FUNC_V Relete();
	~List();
	//关联式Id操作
	//为段增加id
	STORAGE_FUNC_I AddDataId(int Index, char *Id);
	//通过ID找到段索引
	STORAGE_FUNC_I GetIdToIndex(char* Id);
	//通过ID获取数据
	T GetIdToData(char* Id);
	//删除关联Id,删除Id不会连同数据一并删除
	STORAGE_FUNC_I DeleteId(char* Id);
	//删除关联Id，同时删除数据
	STORAGE_FUNC_I DeleteIdData(char* Id);
	//获取索引关联的Id
	STORAGE_FUNC_CP GetIdToIndex(int Index);
	//运算符
	//+
	List & operator + (T AddData);
	//-
	List & operator - (int Len);
	//[]
	List & operator [] (int Len);
private:
	T *Data;	//数据
	char *IdStatic;	//关联数据
	int ListSize;	//大小
	//字符操作函数，用于操作关联Id
	//原大小增长
	int  StrAdd(int i, int i1);
	//获取整数到字符的大小
	int GetIntToStr(int In);
	//连接
	int StrCmd(char * Str, char* Strn, int Size);
	//查找
	int GetStrTxTIndxRepeat(char* Str, int Repeat = 0/*重复次数*/);
	//取出index
	int NStr(int i, char c);
	//文本删除
	void DeleteStr(const char* Str);
};

/*哈希表*/
template<class T>
class STO_CLASS_DLL_PORT Hash{
public:
	//长度构造
	Hash(int Len);
	//初始化
	STORAGE_FUNC_I InI();
	//计算哈希
	STORAGE_FUNC_I ComputeHash(char* Key);
	//查找
	STORAGE_FUNC_I LookupData(char* Key);
	//压入
	STORAGE_FUNC_I Input(char* Key, T Data);
	//删除
	STORAGE_FUNC_V Delete(char* Key);
	//获取
	T GetData(char* Key);
	//修改
	STORAGE_FUNC_I SetData(char* Key, T Data);
	//获取大小
	STORAGE_FUNC_I GetHashSize();

private:
	T *Data; //数据
	int HashSize;

};
#endif//--!endif