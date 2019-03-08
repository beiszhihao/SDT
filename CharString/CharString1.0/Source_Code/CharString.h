/*
CharString��
*/
#ifndef _CHAR_STRING_
#define _CHAR_STRING_

//δ�����Ŀ⣬�ַ�����ת��
#include <Shlwapi.h> 
#pragma comment(lib, "shlwapi.lib")
//malloc
#include <malloc.h>
//��׼c
#include <stdio.h>
//��չ����c��
#include <stdlib.h>
//�����ض���
typedef unsigned char STR_8BIT;//8bit
//�궨��
#define CHARSTRING_FRONT 0x00	//ǰ
#define CHARSTRING_AFTER 0x01	//��
#define STR_ERROR 0	//����
#define STR_CORRECT 1	//��ȷ
#define STR_FUNC_VOID void	//���ͺ�
#define STR_FUNC_UL unsigned long //���ͺ�
#define STR_FUNC_SLLI signed long long int //���ͺ�
#define STR_FUNC_CP char * //���ͺ�
#define STR_FUNC_I int //���ͺ�
#define STR_FUNC_BL bool //���ͺ�
#define STR_FUNC_D double //���ͺ�
#define STR_FUNC_C char //���ͺ�
#define STR_CLASS_DLL_PORT _declspec(dllexport) //�����ӿ�
#define STR_FUNC_8BIT STR_8BIT	//���ͺ�
#define STR_FUNC_LUGP LangUang* //�ṹ��
#define STR_FUNC_LUG LangUang //�ṹ��

class STR_CLASS_DLL_PORT CharString{
public:
	//����
	CharString();
	CharString(const char* str);
	CharString(char* str);
	//����
	~CharString();
	//�ͷ��ַ�
	STR_FUNC_VOID Relete();
	//ɾ��ָ���ַ�����ַ�
	STR_FUNC_8BIT DeleteAppointStr(char str, int Method/*���Ŀ�ʼ,0ǰ��1��*/, BOOL Retain/*�Ƿ���ԭ�ַ�*/);
	//��ȡ�ַ�����С
	STR_FUNC_SLLI GetStrSize();
	//��ӡ�ַ���cmd�������������
	STR_FUNC_8BIT Print_Cmd();
	//ѹ���ַ�
	STR_FUNC_8BIT Input(const char *Str);
	//����
	STR_FUNC_8BIT Input(char *Str);
	//�ַ�ƴ��
	STR_FUNC_8BIT Splicing(const char *Str);
	//����
	STR_FUNC_8BIT Splicing(char *Str);
	//����data
	STR_FUNC_CP GetData();
	//��copy
	STR_FUNC_CP GetReturnData();
	//�ַ����ü���aTob֮����ַ��ᱻ�ü�
	STR_FUNC_I TailoringIndexToIndex(int A, int B);
	//��ʽ���ַ�
	template <typename T>
	STR_FUNC_I Format_Str(T Format,int Index);
	//�����ı�
	STR_FUNC_I InsertTxT(const char* Str,int Index);
	STR_FUNC_I InsertTxT(char* Str, int Index);
	//�ı����
	STR_FUNC_I EmptyTxT();
	//�ı���ͳһֵ
	STR_FUNC_I SetTxT(char Str);
	//�ַ���������ȡ����ٷ�
	STR_FUNC_I GetStrTxTIndx(const char* Str);
	STR_FUNC_I GetStrTxTIndx(char* Str);
	STR_FUNC_I GetStrTxTIndxRepeat(const char* Str, int Repeat/*�ظ�����*/);
	STR_FUNC_I GetStrTxTIndxRepeat(char* Str, int Repeat/*�ظ�����*/);
	STR_FUNC_I GetStrTxTIndxA(char* Str);//��
	STR_FUNC_I GetStrTxTIndxA(const char* Str);
	STR_FUNC_I GetStrTxTIndxEx(const char* Str);
	STR_FUNC_I GetStrTxTIndxEx(char* Str);
	STR_FUNC_I GetStrTxTIndxRepeatA(char* Str, int Repeat/*�ظ�����*/);
	STR_FUNC_I GetStrTxTIndxRepeatA(const char* Str, int Repeat/*�ظ�����*/);
	STR_FUNC_I GetStrTxTIndxRepeatEx(char* Str, int Repeat/*�ظ�����*/);
	STR_FUNC_I GetStrTxTIndxRepeatEx(const char* Str, int Repeat/*�ظ�����*/);
	//�ж��ı��Ƿ����
	STR_FUNC_BL JumpTxTExits(char *Str);
	//ȡһ���ı�
	STR_FUNC_CP GetLineTxT(int LineIndex);
	//ȡ�ı�������
	STR_FUNC_I GetLineNum();
	//��ȡ�ı�������
	STR_FUNC_I GetTxTLineNum(char *Str);
	//ȡ�ұ��ı�
	STR_FUNC_CP GetRightTxT(int Length);
	//ȡ�ұ��ı�������
	STR_FUNC_I GetRightIndex();
	//ȡ����ı�
	STR_FUNC_CP GetLeftTxT(int Length);
	//ȡ����ı�������
	STR_FUNC_I GetLeftIndex();
	//ȡ�м��ı�
	STR_FUNC_CP GetMiddle(int Length);
	//ȡ�м��ı�������
	STR_FUNC_I GetMiddleIndex();
	//�������ַ��ü�
	STR_FUNC_CP IndexToCharCutOut(int Index, char Str);
	//�����ַ���ȡ
	STR_FUNC_CP CharToCharCutOut(char Str1, char Str2);
	//��Ӣ�ĸ���ת���ַ�ת��
	STR_FUNC_VOID FuncTion_CharInToCharAscii(char &Cstr);
	//�������ȡ�ı���ʹ�÷����������ı��� txt:1,2,3,4\r\n ʹ�÷�����AnalysisTxTtoArr(':',',','\r',x) ÿ�λ����x��������'1''2''3'
	STR_FUNC_CP ThreePoints_AnalysisTxTtoArr(char Str1/*��һ��char*/, char Str2/*�м�char*/, char Str3/*��βchar*/, int Index/*����*/);
	STR_FUNC_I ThreePoints_AnalysisGetTxTtoArrNum(char Str1/*��һ��char*/, char Str2/*�м�char*/, char Str3/*��βchar*/);
	//�ü��ı�
	STR_FUNC_I CutOutTxT(char *Str);
	STR_FUNC_I CutOutTxT(const char *Str);
	STR_FUNC_I CutOutTxT(char Str);
	STR_FUNC_I CutOutTxT(int Index);
	//�ı�����
	STR_FUNC_I TxTReveresOrder_AfterToFront();//��ǰ
	STR_FUNC_I TxTReveresOrder_FrontToAfter();//ǰ����
	//�ı��滻
	STR_FUNC_I TxTReplace(const char* Str1, const char* Str2);
	//�����ı��滻
	STR_FUNC_I TxTReplace(int Index, const char* Str);
	//�ַ�β����ȷ��
	STR_FUNC_I CORRECT_STR();
	//У�鵱ǰ�ַ����ǲ���һ����ȷ���ַ���
	STR_FUNC_I STR_IF_CORRECT();
	//��ʽ���
	STR_FUNC_CP GetFormatTwo(const char Format, int Str_Index);
	/*�ж��ַ��Ƿ����*/
	STR_FUNC_I IF_Char(char Char_);
	//ȡ��ʽ
	STR_FUNC_CP Clip(char Format, int About, int Index, char InFormat);
	//��
	STR_FUNC_CP ClipLine(char Format, int About, int Line, int Index, char InFormat);
	//ȡ�����ı�+���ַ�
	STR_FUNC_CP Mid(int Index, int Lent);
	//�ж��ַ��Ƿ����0
	STR_FUNC_BL Nsize();
	//�ж��ַ��Ƿ�Ϊ�����ַ�
	STR_FUNC_BL JuNum(int Index);
	//�жϵ�ǰ�ַ����Ƿ�Ϊ����
	STR_FUNC_BL JuNumStr();
	//��ȡָ���ַ����������
	STR_FUNC_I GetStrAfterNum(char* Str);
	STR_FUNC_CP GetStrAfterNumA(char* Str);
	STR_FUNC_D GetStrAfterDouble(char* Str);
	STR_FUNC_CP GetStrAfterDoubleA(char* Str);
	//��ʽ�ü�
	STR_FUNC_CP  Cin(char Format, int Index);
	//�ı����
	STR_FUNC_I CharSet(char Str1, char Str2);
	/*������*/
	//���������=
	CharString & operator = (const char * Str);
	//���������=
	CharString & operator = (const char Str);
	//-
	CharString & operator + (const char *Str);
	//-
	CharString & operator - (char *Str);
	//[]
	STR_FUNC_C & operator [] (int I);
	//%��
	STR_FUNC_CP operator % (int I);
	//==
	STR_FUNC_BL operator == (const char *Str);
	//()
	CharString & operator () (const char *Str);
private:
	char *m_str;	//�ַ�ָ��
};
#endif // !_CHAR_STRING_