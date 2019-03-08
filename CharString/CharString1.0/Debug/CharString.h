/*
CharString类
*/
#ifndef _CHAR_STRING_
#define _CHAR_STRING_

//未公开的库，字符进制转换
#include <Shlwapi.h> 
#pragma comment(lib, "shlwapi.lib")
//malloc
#include <malloc.h>
//标准c
#include <stdio.h>
//扩展处理c库
#include <stdlib.h>
//类型重定义
typedef unsigned char STR_8BIT;//8bit
//宏定义
#define CHARSTRING_FRONT 0x00	//前
#define CHARSTRING_AFTER 0x01	//后
#define STR_ERROR 0	//错误
#define STR_CORRECT 1	//正确
#define STR_FUNC_VOID void	//类型宏
#define STR_FUNC_UL unsigned long //类型宏
#define STR_FUNC_SLLI signed long long int //类型宏
#define STR_FUNC_CP char * //类型宏
#define STR_FUNC_I int //类型宏
#define STR_FUNC_BL bool //类型宏
#define STR_FUNC_D double //类型宏
#define STR_FUNC_C char //类型宏
#define STR_CLASS_DLL_PORT _declspec(dllexport) //导出接口
#define STR_FUNC_8BIT STR_8BIT	//类型宏
#define STR_FUNC_LUGP LangUang* //结构宏
#define STR_FUNC_LUG LangUang //结构宏

class STR_CLASS_DLL_PORT CharString{
public:
	//构造
	CharString();
	CharString(const char* str);
	CharString(char* str);
	//析构
	~CharString();
	//释放字符
	STR_FUNC_VOID Relete();
	//删除指定字符后的字符
	STR_FUNC_8BIT DeleteAppointStr(char str, int Method/*从哪开始,0前，1后*/, BOOL Retain/*是否保留原字符*/);
	//获取字符串大小
	STR_FUNC_SLLI GetStrSize();
	//打印字符到cmd窗口输出缓冲区
	STR_FUNC_8BIT Print_Cmd();
	//压入字符
	STR_FUNC_8BIT Input(const char *Str);
	//重载
	STR_FUNC_8BIT Input(char *Str);
	//字符拼接
	STR_FUNC_8BIT Splicing(const char *Str);
	//重载
	STR_FUNC_8BIT Splicing(char *Str);
	//返回data
	STR_FUNC_CP GetData();
	//深copy
	STR_FUNC_CP GetReturnData();
	//字符串裁剪，aTob之间的字符会被裁剪
	STR_FUNC_I TailoringIndexToIndex(int A, int B);
	//格式化字符
	template <typename T>
	STR_FUNC_I Format_Str(T Format,int Index);
	//插入文本
	STR_FUNC_I InsertTxT(const char* Str,int Index);
	STR_FUNC_I InsertTxT(char* Str, int Index);
	//文本清空
	STR_FUNC_I EmptyTxT();
	//文本置统一值
	STR_FUNC_I SetTxT(char Str);
	//字符串索引获取，穷举法
	STR_FUNC_I GetStrTxTIndx(const char* Str);
	STR_FUNC_I GetStrTxTIndx(char* Str);
	STR_FUNC_I GetStrTxTIndxRepeat(const char* Str, int Repeat/*重复次数*/);
	STR_FUNC_I GetStrTxTIndxRepeat(char* Str, int Repeat/*重复次数*/);
	STR_FUNC_I GetStrTxTIndxA(char* Str);//后
	STR_FUNC_I GetStrTxTIndxA(const char* Str);
	STR_FUNC_I GetStrTxTIndxEx(const char* Str);
	STR_FUNC_I GetStrTxTIndxEx(char* Str);
	STR_FUNC_I GetStrTxTIndxRepeatA(char* Str, int Repeat/*重复次数*/);
	STR_FUNC_I GetStrTxTIndxRepeatA(const char* Str, int Repeat/*重复次数*/);
	STR_FUNC_I GetStrTxTIndxRepeatEx(char* Str, int Repeat/*重复次数*/);
	STR_FUNC_I GetStrTxTIndxRepeatEx(const char* Str, int Repeat/*重复次数*/);
	//判断文本是否存在
	STR_FUNC_BL JumpTxTExits(char *Str);
	//取一行文本
	STR_FUNC_CP GetLineTxT(int LineIndex);
	//取文本多少行
	STR_FUNC_I GetLineNum();
	//获取文本所在行
	STR_FUNC_I GetTxTLineNum(char *Str);
	//取右边文本
	STR_FUNC_CP GetRightTxT(int Length);
	//取右边文本索引号
	STR_FUNC_I GetRightIndex();
	//取左边文本
	STR_FUNC_CP GetLeftTxT(int Length);
	//取左边文本索引号
	STR_FUNC_I GetLeftIndex();
	//取中间文本
	STR_FUNC_CP GetMiddle(int Length);
	//取中间文本索引号
	STR_FUNC_I GetMiddleIndex();
	//索引到字符裁剪
	STR_FUNC_CP IndexToCharCutOut(int Index, char Str);
	//两点字符截取
	STR_FUNC_CP CharToCharCutOut(char Str1, char Str2);
	//中英文浮点转换字符转换
	STR_FUNC_VOID FuncTion_CharInToCharAscii(char &Cstr);
	//三点解析取文本，使用方法：例如文本是 txt:1,2,3,4\r\n 使用方法：AnalysisTxTtoArr(':',',','\r',x) 每次会根据x索引返回'1''2''3'
	STR_FUNC_CP ThreePoints_AnalysisTxTtoArr(char Str1/*第一个char*/, char Str2/*中间char*/, char Str3/*结尾char*/, int Index/*索引*/);
	STR_FUNC_I ThreePoints_AnalysisGetTxTtoArrNum(char Str1/*第一个char*/, char Str2/*中间char*/, char Str3/*结尾char*/);
	//裁剪文本
	STR_FUNC_I CutOutTxT(char *Str);
	STR_FUNC_I CutOutTxT(const char *Str);
	STR_FUNC_I CutOutTxT(char Str);
	STR_FUNC_I CutOutTxT(int Index);
	//文本逆序
	STR_FUNC_I TxTReveresOrder_AfterToFront();//后到前
	STR_FUNC_I TxTReveresOrder_FrontToAfter();//前到后
	//文本替换
	STR_FUNC_I TxTReplace(const char* Str1, const char* Str2);
	//索引文本替换
	STR_FUNC_I TxTReplace(int Index, const char* Str);
	//字符尾部正确化
	STR_FUNC_I CORRECT_STR();
	//校验当前字符串是不是一个正确的字符串
	STR_FUNC_I STR_IF_CORRECT();
	//格式拆分
	STR_FUNC_CP GetFormatTwo(const char Format, int Str_Index);
	/*判断字符是否存在*/
	STR_FUNC_I IF_Char(char Char_);
	//取格式
	STR_FUNC_CP Clip(char Format, int About, int Index, char InFormat);
	//行
	STR_FUNC_CP ClipLine(char Format, int About, int Line, int Index, char InFormat);
	//取索引文本+长字符
	STR_FUNC_CP Mid(int Index, int Lent);
	//判断字符是否大于0
	STR_FUNC_BL Nsize();
	//判断字符是否为数字字符
	STR_FUNC_BL JuNum(int Index);
	//判断当前字符串是否为数字
	STR_FUNC_BL JuNumStr();
	//获取指定字符串后的数字
	STR_FUNC_I GetStrAfterNum(char* Str);
	STR_FUNC_CP GetStrAfterNumA(char* Str);
	STR_FUNC_D GetStrAfterDouble(char* Str);
	STR_FUNC_CP GetStrAfterDoubleA(char* Str);
	//分式裁剪
	STR_FUNC_CP  Cin(char Format, int Index);
	//文本变更
	STR_FUNC_I CharSet(char Str1, char Str2);
	/*操作符*/
	//运算符重载=
	CharString & operator = (const char * Str);
	//运算符重载=
	CharString & operator = (const char Str);
	//-
	CharString & operator + (const char *Str);
	//-
	CharString & operator - (char *Str);
	//[]
	STR_FUNC_C & operator [] (int I);
	//%行
	STR_FUNC_CP operator % (int I);
	//==
	STR_FUNC_BL operator == (const char *Str);
	//()
	CharString & operator () (const char *Str);
private:
	char *m_str;	//字符指针
};
#endif // !_CHAR_STRING_