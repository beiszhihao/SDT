/*
CharString��
*/
#ifndef _STOR_AGE_
#define _STOR_AGE_

//��׼����ͷ�ļ�
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//�궨��
#define STORAGE_ERROR 0
#define STORAGE_SUCCESS 1

//���Ͷ���
typedef int STORAGE_FUNC_I;
typedef void STORAGE_FUNC_V;
typedef bool STORAGE_FUNC_BL;
typedef char* STORAGE_FUNC_CP;

//�ַ��ֶ�ͳһ������
#define LIST_I '/'
#define LIST_H '='
#define LIST_IS "/"
#define LIST_HS "="
#define STO_CLASS_DLL_PORT _declspec(dllexport) //�����ӿ�
template<class T>
class STO_CLASS_DLL_PORT List{
public:
	//Ĭ�Ϲ���
	List();
	//���ȹ���
	List(int Len);
	//�޸�����
	STORAGE_FUNC_I Modify(int ArrIndex, T IutPut_Data);
	//������0
	STORAGE_FUNC_V DataMet();
	//��ȡͷ����
	STORAGE_FUNC_I Hand();
	//��ȡβ����
	STORAGE_FUNC_I End();
	//��ȡ�м�����
	STORAGE_FUNC_I In();
	//Ѱ������
	STORAGE_FUNC_BL SeekData(T SeekData);
	STORAGE_FUNC_BL SeekDataToIndex(T SeekData);
	//��ȡ����
	T GetData(int ArrIndex);
	//��������
	STORAGE_FUNC_I ExpanSion(int Len);
	//��̬���
	STORAGE_FUNC_I ExpanSionEx(int Len);
	//Add����
	STORAGE_FUNC_I Add(T ADD_Data);
	//��ȡ��С
	STORAGE_FUNC_I GetSize();
	//��������
	STORAGE_FUNC_V ReGrow(int Len);
	//ɾ��
	STORAGE_FUNC_I Delete(int Len);
	//ɾ��ָ��λ���ϵ�����
	STORAGE_FUNC_I DeleteIndex(int Index);
	//�ͷ�
	STORAGE_FUNC_V Relete();
	~List();
	//����ʽId����
	//Ϊ������id
	STORAGE_FUNC_I AddDataId(int Index, char *Id);
	//ͨ��ID�ҵ�������
	STORAGE_FUNC_I GetIdToIndex(char* Id);
	//ͨ��ID��ȡ����
	T GetIdToData(char* Id);
	//ɾ������Id,ɾ��Id������ͬ����һ��ɾ��
	STORAGE_FUNC_I DeleteId(char* Id);
	//ɾ������Id��ͬʱɾ������
	STORAGE_FUNC_I DeleteIdData(char* Id);
	//��ȡ����������Id
	STORAGE_FUNC_CP GetIdToIndex(int Index);
	//�����
	//+
	List & operator + (T AddData);
	//-
	List & operator - (int Len);
	//[]
	List & operator [] (int Len);
private:
	T *Data;	//����
	char *IdStatic;	//��������
	int ListSize;	//��С
	//�ַ��������������ڲ�������Id
	//ԭ��С����
	int  StrAdd(int i, int i1);
	//��ȡ�������ַ��Ĵ�С
	int GetIntToStr(int In);
	//����
	int StrCmd(char * Str, char* Strn, int Size);
	//����
	int GetStrTxTIndxRepeat(char* Str, int Repeat = 0/*�ظ�����*/);
	//ȡ��index
	int NStr(int i, char c);
	//�ı�ɾ��
	void DeleteStr(const char* Str);
};

/*��ϣ��*/
template<class T>
class STO_CLASS_DLL_PORT Hash{
public:
	//���ȹ���
	Hash(int Len);
	//��ʼ��
	STORAGE_FUNC_I InI();
	//�����ϣ
	STORAGE_FUNC_I ComputeHash(char* Key);
	//����
	STORAGE_FUNC_I LookupData(char* Key);
	//ѹ��
	STORAGE_FUNC_I Input(char* Key, T Data);
	//ɾ��
	STORAGE_FUNC_V Delete(char* Key);
	//��ȡ
	T GetData(char* Key);
	//�޸�
	STORAGE_FUNC_I SetData(char* Key, T Data);
	//��ȡ��С
	STORAGE_FUNC_I GetHashSize();

private:
	T *Data; //����
	int HashSize;

};
#endif//--!endif