/*
StorAge
*/
#include "StorAge.h"
/*
(List)
*/
/*
构造
*/
//默认构造
template<class T>
List<T>::List() :this->Data(NULL), this->ListSize(0), this->IdStatic(0){

}
//长度构造
template<class T>
List<T>::List(int Len){
	this->Data = new T[Len];	//分配数组
	this->ListSize = Len;
	this->DataMet();
	//id构建
	this->IdStatic = NULL;
}

/*
修改数据
*/
//修改数据
template<class T>
STORAGE_FUNC_I List<T>::Modify(int ArrIndex, T IutPut_Data){
	//比对要修改的数据索引是否越界
	if (ArrIndex > this->ListSize){
		return STORAGE_ERROR;
	}
	//因为类型萃取原因，这里我们可以直接修改值，c++已经为我们做了很多繁琐的工作
	this->Data[ArrIndex - 1] = IutPut_Data;
	return STORAGE_SUCCESS;
}

/*
获取数据
*/
//获取数据
template<class T>
T  List<T>::GetData(int ArrIndex){
	//获取数据大小
	if (ArrIndex > this->ListSize){
		return STORAGE_ERROR;
	}
	return this->Data[ArrIndex - 1];
}

/*
增加数据
*/
//扩充增加
template<class T>
STORAGE_FUNC_I  List<T>::ExpanSion(int Len){
	T *Data1 = new T[this->ListSize + Len];
	int i = 0;
	for (i = 0; i <= (this->ListSize + Len) - 1; ++i){
		if (i <= this->ListSize && this->ListSize != 0){
			Data1[i] = this->Data[i];
		}
		else{
			Data1[i] = 0;
		}
	}
	this->Relete();
	this->Data = Data1;
	this->ListSize += Len;
	return STORAGE_SUCCESS;
}

//动态变更
template<class T>
STORAGE_FUNC_I List<T>::ExpanSionEx(int Len){
	if (Len <= this->ListSize){
		return STORAGE_ERROR;
	}
	T *Data1 = new T[Len];
	int i = 0;
	for (i = 0; i <= Len - 1; ++i){
		if (i <= this->ListSize && this->ListSize != 0){
			Data1[i] = this->Data[i];
		}
		else{
			Data1[i] = 0;
		}
	}
	this->Relete();
	this->Data = Data1;
	this->ListSize = Len;
	return STORAGE_SUCCESS;
}

//Add增加
template<class T>
STORAGE_FUNC_I List<T>::Add(T ADD_Data){
	T *Data1 = new T[this->ListSize + 1];
	for (int i = 0; i <= this->ListSize - 1; ++i){
		Data1[i] = this->Data[i];
	}
	Data1[this->ListSize] = ADD_Data;
	int Fbl = this->ListSize;
	this->Relete();
	this->Data = Data1;
	this->ListSize = Fbl + 1;
	return STORAGE_SUCCESS;
}

/*
获取大小
*/
//获取大小
template<class T>
STORAGE_FUNC_I List<T>::GetSize(){
	return this->ListSize;//返回大小
}

/*
重新增长
*/
//重新增长
template<class T>
STORAGE_FUNC_V List<T>::ReGrow(int Len){
	this->Relete();
	this->Data = new T[Len];	//分配数组
	this->ListSize = Len;
	//id构建
	this->IdStatic = NULL;
}

/*
删除
*/
//删除
template<class T>
STORAGE_FUNC_I List<T>::Delete(int Len){
	if (Len >= this->ListSize){
		return STORAGE_ERROR;
	}
	//分配大小-Len是去掉尾巴
	T *Data1 = new T[this->ListSize - Len];
	int LinShi = 0;
	//循环到要删除的索引行，-1是因为i从0开始
	for (int i = 0; i <= (this->ListSize - Len) - 1; ++i){
		Data1[LinShi++] = this->Data[i];
	}
	this->Relete();
	this->Data = Data1;
	this->ListSize -= 1;
	return STORAGE_SUCCESS;
}

//删除指定位置上的数据
template<class T>
STORAGE_FUNC_I List<T>::DeleteIndex(int Index){
	if (Index - 1 > this->ListSize){
		return STORAGE_ERROR;
	}
	T *Data1 = new T[this->ListSize - 1];
	int LinShi = 0;
	for (int i = 0; i <= this->ListSize - 1; ++i){
		//判断是否到达索引，到达跳过不赋予值
		if (i == Index - 1){
			continue;
		}
		else{
			Data1[this->LinShi++] = Data[i];
		}
	}
	this->Relete();
	this->Data = Data1;
	this->ListSize -= 1;
	return STORAGE_SUCCESS;
}

/*
数据置0
*/
//数据置0
template<class T>
STORAGE_FUNC_V  List<T>::DataMet(){
	if (this->ListSize <= 0){
		return;
	}
	for (int i = 0; i <= this->ListSize - 1; ++i){
		this->Data[i] = 0;
	}
}

/*
获取索引
*/
//获取头索引
template<class T>
STORAGE_FUNC_I  List<T>::Hand(){
	if (this->ListSize <= 0){
		return STORAGE_ERROR;
	}
	return 1;
}
//获取尾索引
template<class T>
STORAGE_FUNC_I  List<T>::End(){
	if (this->ListSize <= 0){
		return STORAGE_ERROR;
	}
	return Lthis->istSize;
}
//获取中间索引
template<class T>
STORAGE_FUNC_I  List<T>::In(){
	if (this->ListSize <= 0){
		return STORAGE_ERROR;
	}
	return ListSize / 2;
}

/*
寻找数据
*/
//寻找数据
template<class T>
STORAGE_FUNC_BL List<T>::SeekData(T SeekData){
	if (this->Hand() == 0){
		return STORAGE_ERROR;
	}
	for (int i = 0; i <= this->ListSize - 1; ++i){
		if (this->Data[i] == SeekData){
			return true;
		}
	}
	return false;
}
template<class T>
STORAGE_FUNC_BL List<T>::SeekDataToIndex(T SeekData){
	if (this->Hand() == 0){
		return STORAGE_ERROR;
	}
	for (int i = 0; i <= this->ListSize - 1; ++i){
		if (this->Data[i] == SeekData){
			return i + 1;
		}
	}
	return false;
}

/*
释放
*/
//释放
template<class T>
STORAGE_FUNC_V List<T>::Relete(){
	//析构
	if (this->Data != NULL){
		delete[this->ListSize] this->Data;
		this->Data = NULL;
	}
	if (this->IdStatic != NULL){
		free(this->IdStatic);
		this->IdStatic = NULL;
	}
}
template<class T>
List<T>::~List(){
	this->Relete();
}

/*
字符处理函数
*/
//原大小增加
template<class T>
int  List<T>::StrAdd(int i, int i1){
	int size = (i + i1);
	if (this->IdStatic != NULL){
		size += strlen(this->IdStatic);
	}
	size += strlen(LIST_IS);
	size += strlen(LIST_HS);
	char* Str1 = (char*)malloc(size + 1);
	if (Str1 == NULL){
		return 0;
	}
	memset(Str1, 0, size + 1);
	if (this->IdStatic != NULL){
		strcpy(Str1, this->IdStatic);
		free(this->IdStatic);
		this->IdStatic = Str1;
		return 1;
	}
	this->IdStatic = Str1;
	return 1;
}

//获取整数到字符的大小
template<class T>
int  List<T>::GetIntToStr(int In){
	char *Str = (char*)malloc(In + 1);
	if (Str == NULL){
		return 0;
	}
	sprintf(Str, "%d", In);
	int StrSize = strlen(Str);
	free(Str);
	Str = NULL;
	return StrSize;
}

//连接
template<class T>
int List<T>::StrCmd(char * Str, char* Strn, int Size){
	char *Str1 = (char*)malloc(Size + strlen(Str) + strlen(LIST_HS) + strlen(LIST_IS) + 1);
	if (Str1 == NULL){
		return 0;
	}
	memset(Str1, 0, Size + strlen(Str) + strlen(LIST_HS) + strlen(LIST_IS) + 1);
	strcpy(Str1, Str);
	strcat(Str1, LIST_HS);
	strcat(Str1, Strn);
	strcat(Str1, LIST_IS);
	strcat(this->IdStatic, Str1);
	return 1;

}

//查找
template<class T>
int List<T>::GetStrTxTIndxRepeat(char* Str, int Repeat = 0/*重复次数*/){
	if (this->IdStatic == NULL || Str == NULL){
		return 0;
	}
	int StrSize = strlen(Str);
	if (StrSize <= 0){
		return 0;
	}
	int Str_m_str = strlen(this->IdStatic);
	int m_str_index = 0;/*二次循环坐标*/
	int y = 0;
	int Repeat_i = 0;
	for (int i = 0; i <= Str_m_str - 1; i++/*加一是因为i从0开始，下方循环是size+1是为了将坐标移动到下个字符*/){
		y = 0;
		m_str_index = i;
		for (int j = 0; j <= StrSize - 1; ++j, ++m_str_index){
			//printf("%d", j);
			if (Str[j] == this->IdStatic[m_str_index]){
				y += 1;
			}
			if (y == StrSize){
				if (Repeat_i == Repeat){
					return i + (strlen(Str) + 1);
				}
				else{
					Repeat_i++;
				}
			}
			if (Str[j] != this->IdStatic[m_str_index]){
				break;

			}
		}
	}
	return 0;
}

//取出index
template<class T>
int List<T>::NStr(int i, char c){
	int it = 0;
	for (int j = i - 1; j <= strlen(this->IdStatic); ++j){
		if (this->IdStatic[j] == c){
			break;
		}
		++it;
	}
	char * str1 = (char*)malloc(it + 1);
	memset(str1, 0, it + 1);
	int yun = 0;
	for (int j = i - 1; j <= i + it - 1; ++j, ++yun){
		str1[yun] = this->IdStatic[j];
	}

	int y = atoi(str1);
	free(str1);
	str1 = NULL;
	return y;
}

//文本删除
template<class T>
void List<T>::DeleteStr(const char* Str){
	int yun = 0;
	int yIndex = 0;
	int you = (strlen(this->IdStatic) - strlen(Str)) + 1;
	char *m_u = (char*)malloc(you);
	if (m_u == NULL){
		return;
	}
	memset(m_u, 0, (strlen(this->IdStatic) - strlen(Str)) + 1);
	for (int i = 0; i <= strlen(this->IdStatic); ++i){
		yun = i;
		for (int j = 0; j <= strlen(Str) - 1; ++j, ++yun){
			if (Str[j] != this->IdStatic[yun]){
				break;
			}
			if (j == strlen(Str) - 1){
				for (int u = 0; u <= i - 1; ++u){
					m_u[u] = this->IdStatic[u];
				}
				int c = i + strlen(Str);
				for (int u = i; u <= strlen(this->IdStatic) - 2; ++u, ++c){
					m_u[u] = this->IdStatic[c];
				}
				free(this->IdStatic);
				this->IdStatic = NULL;
				this->IdStatic = (char*)malloc(you);
				if (this->IdStatic == NULL){
					return;
				}
				memset(this->IdStatic, 0, you);
				strcpy(this->IdStatic, m_u);
				free(m_u);
				m_u = NULL;
				return;

			}
		}
	}
}

/*
关联式Id操作
*/
//为段增加id
template<class T>
STORAGE_FUNC_I  List<T>::AddDataId(int Index, char *Id){
	if (Index > this->ListSize){
		return STORAGE_ERROR;
	}
	//判断Id是否已经存在
	if (this->GetStrTxTIndxRepeat(Id) != 0){
		return STORAGE_ERROR;
	}
	int StrSize = this->GetIntToStr(Index);
	if (0 == StrSize){
		return STORAGE_ERROR;
	}
	if (0 == this->StrAdd(StrSize, strlen(Id))){
		return STORAGE_ERROR;
	}
	char * Str1 = (char*)malloc(StrSize + 1);
	if (Str1 == NULL){
		return STORAGE_ERROR;
	}
	memset(Str1, 0, StrSize + 1);
	sprintf(Str1, "%d", Index);
	if (0 == this->StrCmd(Id, Str1, strlen(Str1))){
		return STORAGE_ERROR;
	}
	return STORAGE_SUCCESS;
}

//通过ID找到段索引
template<class T>
STORAGE_FUNC_I List<T>::GetIdToIndex(char* Id){
	if (Id == NULL){
		return STORAGE_ERROR;
	}
	if (this->IdStatic == NULL){
		return STORAGE_ERROR;
	}
	//查找
	char *Str1 = (char*)malloc(strlen(Id) + strlen(LIST_HS) + 1);
	if (Str1 == NULL){
		return STORAGE_ERROR;
	}
	memset(Str1, 0, strlen(Id) + strlen(LIST_HS) + 1);
	strcpy(Str1, Id);
	strcat(Str1, LIST_HS);
	int Inde = this->GetStrTxTIndxRepeat(Str1);
	if (Inde == 0){
		return STORAGE_ERROR;
	}
	return this->NStr(Inde, LIST_I);
}

//通过ID获取数据
template<class T>
T List<T>::GetIdToData(char* Id){
	if (Id == NULL){
		return STORAGE_ERROR;
	}
	if (this->IdStatic == NULL){
		return STORAGE_ERROR;
	}
	int Y = this->GetIdToIndex(Id);
	if (Y == 0){
		return STORAGE_ERROR;
	}
	return this->GetData(Y);
}

//删除关联Id,删除Id不会连同数据一并删除
template<class T>
STORAGE_FUNC_I List<T>::DeleteId(char* Id){
	if (Id == NULL){
		return STORAGE_ERROR;
	}
	if (this->IdStatic == NULL){
		return STORAGE_ERROR;
	}
	//先获取与ID关联的数据索引
	int Index = this->GetIdToIndex(Id);
	if (Index == STORAGE_ERROR){
		return STORAGE_ERROR;
	}
	//获取Index关联的字符索引大小
	int InSi = this->GetIntToStr(Index);
	if (InSi == 0){
		return STORAGE_ERROR;
	}
	//索引转字符
	char* strInd = (char*)malloc(InSi + 1);
	memset(strInd, 0, InSi + 1);
	sprintf(strInd, "%d", Index);
	//通过索引拼接成要删除的字符
	char *Str1 = (char*)malloc(strlen(Id) + strlen(LIST_HS) + strlen(LIST_IS) + 1);
	memset(Str1, 0, strlen(Id) + strlen(LIST_HS) + strlen(LIST_IS) + 1);
	//拼接
	strcpy(Str1, Id);
	strcat(Str1, LIST_HS);
	strcat(Str1, strInd);
	strcat(Str1, LIST_IS);
	//删除文本
	this->DeleteStr(Str1);
	return STORAGE_SUCCESS;
}

//删除关联Id，同时删除数据
template<class T>
STORAGE_FUNC_I List<T>::DeleteIdData(char* Id){
	if (Id == NULL){
		return STORAGE_ERROR;
	}
	if (this->IdStatic == NULL){
		return STORAGE_ERROR;
	}
	//先获取与ID关联的数据索引
	int Index = this->GetIdToIndex(Id);
	if (Index == STORAGE_ERROR){
		return STORAGE_ERROR;
	}
	//删除Id
	this->DeleteId(Id);
	//删除索引
	this->DeleteIndex(Index);
}

//获取索引关联的Id
template<class T>
STORAGE_FUNC_CP List<T>::GetIdToIndex(int Index){
	if (this->IdStatic == NULL){
		return STORAGE_ERROR;
	}
	if (Index > this->ListSize){
		return STORAGE_ERROR;
	}
	//获取Index关联的字符索引大小
	int InSi = this->GetIntToStr(Index);
	if (InSi == 0){
		return STORAGE_ERROR;
	}
	//索引转字符
	char* strInd = (char*)malloc(InSi + 1);
	memset(strInd, 0, InSi + 1);
	sprintf(strInd, "%d", Index);
	int I = this->GetStrTxTIndxRepeat(strInd);
	if (I == 0){
		return STORAGE_ERROR;
	}
	int Inm = 0;
	for (int i = I - 2; i >= 0;){
		if (IdStatic[i--] == LIST_I){
			Inm = i;
			break;
		}
	}
	int ysize = 0;
	for (int i = Inm; this->IdStatic[i] != LIST_H; ++i){
		ysize++;
	}
	char* copystr = (char*)malloc(ysize + 1);
	memset(copystr, 0, ysize + 1);
	int t = 0;
	for (int i = Inm; this->IdStatic[i] != LIST_H; ++i){
		copystr[t++] = this->IdStatic[i];
	}
	return copystr;
}

//运算符
//+
template<class T>
List<T> & List<T>::operator + (T AddData){
	this->Add(AddData);
}
//-
template<class T>
List<T> & List<T>::operator - (int Len){
	this->Delete(Len)
}
//[]
template<class T>
List<T> & List<T>::operator [] (int Len){
	return this->GetData(Len);
}

/*
(Hash)
*/
/*
构造
*/
//长度构造
template<class T>
Hash<T>::Hash(int Len){
	this->Data = new T[Len];	//分配数组
	this->HashSize = Len;
	this->InI();
}

/*
初始化
*/
//初始化
template<class T>
STORAGE_FUNC_I Hash<T>::InI(){
	for (int i = 0; i <= this->HashSize - 1; ++i){
		this->Data[i] = NULL;
	}
	return STORAGE_SUCCESS;
}

/*
计算哈希
*/
//计算哈希
template<class T>
STORAGE_FUNC_I Hash<T>::ComputeHash(char* Key){
	if (Key == NULL){
		return STORAGE_ERROR;
	}
	signed int HashData = 0;//哈希值
	for (int i = 0; Key[i] != '\0'; ++i){
		HashData = HashData + 33 * Key[i];//计算
	}
	return HashData%HashSize;//取余返回
}

/*
查找
*/
//查找
template<class T>
STORAGE_FUNC_I Hash<T>::LookupData(char* Key){
	if (Key == NULL){
		return STORAGE_ERROR;
	}
	int HashIndex = this->ComputeHash(Key);
	//没有计算出哈希值
	if (HashIndex == STORAGE_ERROR){
		return STORAGE_ERROR;
	}
	//判断是否为0
	if (this->Data[HashIndex] == 0){
		return STORAGE_ERROR;
	}
	return HashIndex;    //返回已经开辟空间了的值
}

/*
压入
*/
//压入
template<class T>
STORAGE_FUNC_I Hash<T>::Input(char* Key, T Data){
	if (Key == NULL){
		return STORAGE_ERROR;
	}
	int Yoi = this->LookupData(Key);
	//此哈希空间没有被赋予值或者开辟空间
	if (Yoi == STORAGE_ERROR){
		int Ind = this->ComputeHash(Key);
		this->Data[Ind] = Data;
		return STORAGE_SUCCESS;
	}
	return STORAGE_ERROR;
}

/*
删除
*/
//删除
template<class T>
STORAGE_FUNC_V Hash<T>::Delete(char* Key){
	if (Key == NULL){
		return;
	}
	//哈希表大小是固定的，所以这里直接给0不释放
	signed int Ind = this->ComputeHash(Key);
	if (this->Data[Ind] != 0){
		this->Data[Ind] = 0;
	}
	return;
}

/*
获取
*/
//获取
template<class T>
T Hash<T>::GetData(char* Key){
	if (Key == NULL){
		return -1;
	}
	int Yoi = this->LookupData(Key);
	if (Yoi != -1){
		return this->Data[Yoi];
	}
	return -1;
}

/*
修改
*/
//修改
template<class T>
STORAGE_FUNC_I Hash<T>::SetData(char* Key, T Data){
	if (Key == NULL){
		return STORAGE_ERROR;
	}
	int Yoi = this->LookupData(Key);
	this->Data[Ind] = Data;
}

/*
获取大小
*/
//获取大小
template<class T>
STORAGE_FUNC_I Hash<T>::GetHashSize(){
	return this->HashSize;
}