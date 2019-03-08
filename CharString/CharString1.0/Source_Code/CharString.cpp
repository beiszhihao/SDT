/*
CharString.cpp
*/
#include "CharString.h"

/*
����
*/
//�޲ι���
CharString::CharString(){
	if (this->m_str != NULL){
		this->Relete();
		this->m_str == NULL;
	}
}
//���ι���
CharString::CharString(const char* Str){
	if (this->m_str != NULL || Str == NULL) {
		this->Relete();
	}
	int strSize = strlen(Str);
	this->m_str = (char*)malloc(strSize + 1);	//\0
	memset(this->m_str, 0, strSize + 1);
	strcpy(this->m_str, Str);
}
//����
CharString::CharString(char* Str){
	if (this->m_str != NULL || Str == NULL) {
		this->Relete();
	}
	int strSize = strlen(Str);
	this->m_str = (char*)malloc(strSize + 1);	//\0
	memset(this->m_str, 0, strSize + 1);
	strcpy(this->m_str, Str);
}

/*
����
*/
//�޲�����
CharString::~CharString(){
	if (this->m_str != NULL){	//�ظ��жϣ���ֹʹ�ú����Ĵ����Լ������ֳ�����
		this->Relete();
	}
}

/*
�ͷ��ַ���
*/
//�ͷ��ַ���
STR_FUNC_VOID CharString::Relete(){
	if (this->m_str != NULL) {
		free(this->m_str);
		this->m_str = NULL;
	}
}

/*
��ȡ�ַ�����С
*/
//������\0
STR_FUNC_SLLI CharString::GetStrSize(){
	if (this->m_str == NULL) {
		return 0;
	}
	int m_size;
	for (m_size = 0; this->m_str[m_size] != '\0'; ++m_size) {}
	return m_size;
}

/*
�ַ��޳�
*/
//ɾ��ָ���ַ�����ַ�
STR_FUNC_8BIT CharString::DeleteAppointStr(char Str, int Method = CHARSTRING_FRONT/*���Ŀ�ʼ,0ǰ��1��*/, BOOL Retain = FALSE/*�Ƿ���ԭ�ַ�*/){
	if (Str == NULL) {
		return STR_ERROR;
	}
	if (this->m_str == NULL) {
		return STR_ERROR;
	}
	if (Method == CHARSTRING_FRONT) {
		for (int i = 0;i<=this->GetStrSize(); ++i) {

			if (Str == this->m_str[i]/*ָ��ƫ�Ƶ���*/) {
				char *copy_str = NULL;
				int copy_num = 0;	//copy num
				if (Retain == TRUE) {
					copy_num = i;
					i = i + 2;
					copy_num = copy_num + 1;
				}
				else {
					copy_num = i;
					i = i + 1;
				}
				copy_str = (char*)malloc(i);//\0��ԭ�ַ�
				memset(copy_str, 0, i);
				strncpy(copy_str, this->m_str, copy_num);
				this->Relete();
				this->m_str = (char*)malloc(i);
				memset(this->m_str, 0, i);
				strcpy(this->m_str, copy_str);
				free(copy_str);
				copy_str = NULL;
				break;

			}
		}
		return STR_ERROR;
	}
	if (Method == CHARSTRING_AFTER) {
		int i = this->GetStrSize();
		for (;i!=0; --i) {
			if (Str == this->m_str[i]/*ָ��ƫ�Ƶ���*/) {
				char *copy_str = NULL;
				int copy_num = 0;	//copy num
				if (Retain == TRUE) {
					copy_num = i;
					i = i + 2;
					copy_num = copy_num + 1;
				}
				else {
					copy_num = i;
					i = i + 1;
				}
				copy_str = (char*)malloc(i);//\0��ԭ�ַ�
				memset(copy_str, 0, i);
				strncpy(copy_str, this->m_str, copy_num);
				this->Relete();
				this->m_str = (char*)malloc(i);
				memset(this->m_str, 0, i);
				strcpy(this->m_str, copy_str);
				free(copy_str);
				copy_str = NULL;
				break;
			}
		}
		return STR_ERROR;
	}

	return STR_CORRECT;
}

/*
�ַ���ӡ
*/
STR_FUNC_8BIT CharString::Print_Cmd(){
	if (this->m_str == NULL) {
		return STR_ERROR;
	}
	char str = 0;
	for (int i = 0; this->m_str[i] != '\0'; ++i) {
		printf("%c", this->m_str[i]);
	}
	return STR_CORRECT;
}

/*
�ַ�ѹ��
*/
STR_FUNC_8BIT CharString::Input(const char *Str){
	if (this->m_str != NULL) {
		this->Relete();
	}
	//Relete();
	if (Str == NULL) {
		return STR_ERROR;
	}
	signed long long int i = 0;
	for (; Str[i] != '\0'; ++i) {}
	m_str = (char*)malloc(i + 1);
	memset(this->m_str, 0, i + 1);
	strcpy(this->m_str, Str);
	return STR_CORRECT;
}
//����
STR_FUNC_8BIT CharString::Input(char *Str){
	if (this->m_str != NULL) {
		this->Relete();
	}
	//Relete();
	if (Str == NULL) {
		return STR_ERROR;
	}
	signed long long int i = 0;
	for (; Str[i] != '\0'; ++i) {}
	m_str = (char*)malloc(i + 1);
	memset(this->m_str, 0, i + 1);
	strcpy(this->m_str, Str);
	return STR_CORRECT;
}

/*
�ַ���ƴ��
*/
//�ַ�ƴ��
STR_FUNC_8BIT CharString::Splicing(const char *Str){
	if (Str == NULL) {
		return STR_ERROR;
	}
	if (this->m_str != NULL) {
		//����ԭ�ַ�
		char *copy_str = NULL;
		int m_size = this->GetStrSize();
		if (m_size <= 0){
			return STR_ERROR;
		}
		copy_str = (char*)malloc(m_size + 1);//\0
		memset(copy_str, 0, m_size + 1);
		strcpy(copy_str,this-> m_str);
		int L_Size = m_size;
		this->Relete();
		//��ȡ�ַ�����С
		signed long long int i = strlen(Str);
		this->m_str = (char*)malloc(L_Size + i + 1);
		memset(this->m_str, 0, L_Size + i + 1);
		strcpy(this->m_str, copy_str);
		//��ֹ������copy֮ǰ��ֵ����һ��
		char *copy_str_1 = (char*)malloc(i + 1);
		strcpy(copy_str_1, Str);
		strcat(m_str, copy_str_1);
		free(copy_str);
		copy_str = NULL;
		free(copy_str_1);
		copy_str_1 = NULL;
	}
	return STR_CORRECT;
}
//����
STR_FUNC_8BIT CharString::Splicing(char *Str){
	if (Str == NULL) {
		return STR_ERROR;
	}
	if (this->m_str != NULL) {
		//����ԭ�ַ�
		char *copy_str = NULL;
		int m_size = this->GetStrSize();
		if (m_size <= 0){
			return STR_ERROR;
		}
		copy_str = (char*)malloc(m_size + 1);//\0
		memset(copy_str, 0, m_size + 1);
		strcpy(copy_str, this->m_str);
		int L_Size = m_size;
		this->Relete();
		//��ȡ�ַ�����С
		signed long long int i = strlen(Str);
		this->m_str = (char*)malloc(L_Size + i + 1);
		memset(this->m_str, 0, L_Size + i + 1);
		strcpy(this->m_str, copy_str);
		//��ֹ������copy֮ǰ��ֵ����һ��
		char *copy_str_1 = (char*)malloc(i + 1);
		strcpy(copy_str_1, Str);
		strcat(m_str, copy_str_1);
		free(copy_str);
		copy_str = NULL;
		free(copy_str_1);
		copy_str_1 = NULL;
	}
	return STR_CORRECT;
}

/*
��ȡData
*/
STR_FUNC_CP CharString::GetData(){
	if (this->m_str == NULL) {
		return STR_ERROR;
	}
	return this->m_str;
}
//��copy
STR_FUNC_CP CharString::GetReturnData(){
	if (this->m_str == NULL) {
		return STR_ERROR;
	}
	int Size = this->GetStrSize();
	char* ReturnStr = (char*)malloc(Size);
	if (ReturnStr == NULL) {
		return NULL;
	}
	memset(ReturnStr, 0, Size);
	strcpy(ReturnStr, this->m_str);
	return ReturnStr;
}

/*
�ַ��ü�
*/
//�ַ��ü�,�ü�a��b֮�������
STR_FUNC_I CharString::TailoringIndexToIndex(int A, int B) {
	if (this->m_str == NULL) {
		return STR_ERROR;
	}
	if (strlen(this->m_str) > B) {
		return STR_ERROR;
	}
	//��λA
	int size = 0;
	for (int i = 0; i <= B - 1; ++i) {
		if (i >= A) {
			size++;
		}

	}
	char *str1 = (char*)malloc(size + 1);
	memset(str1, 0, size + 1);
	int u = 0;
	for (int i = 0; i <= B - 1; ++i) {
		if (i >= A) {
			str1[u++] = this->m_str[i];
		}
	}
	//�ü�
	free(this->m_str);
	this->m_str = NULL;
	this->m_str = (char*)malloc(size + 1);
	memset(this->m_str, 0, size + 1);
	strcpy(this->m_str, str1);
	return STR_CORRECT;
}

/*
��ʽ���ַ�;

*/
//�������͵��ַ�
template <typename T>
STR_FUNC_I CharString::Format_Str(T Format,int Index = 0) {
	if (Index == 0){
		//int
		if (typeid(Format) == typeid(int)) {
			Relete();
			m_strmalloc(sizeof(int));
			sprintf(m_str, "%d", Format);
			return STR_CORRECT;
		}
		//double
		if (typeid(Format) == typeid(double)) {
			Relete();
			m_strmalloc(sizeof(double));
			sprintf(m_str, "%lf", Format);
			return STR_CORRECT;
		}
		//float
		if (typeid(Format) == typeid(float)) {
			Relete();
			m_strmalloc(sizeof(float));
			sprintf(m_str, "%f", Format);
			return STR_CORRECT;
		}
		//char
		if (typeid(Format) == typeid(char)) {
			Relete();
			m_strmalloc(sizeof(char)+1);	//\0
			sprintf(m_str, "%c", Format);
			return STR_CORRECT;
		}
		//unsigned
		if (typeid(Format) == typeid(unsigned)) {
			Relete();
			m_strmalloc(sizeof(int));
			sprintf(m_str, "%u", Format);
			return STR_CORRECT;
		}
		//unsigned int
		if (typeid(Format) == typeid(unsigned int)) {
			Relete();
			m_strmalloc(sizeof(int));
			sprintf(m_str, "%lu", Format);
			return STR_CORRECT;
		}
		//unsigned long
		if (typeid(Format) == typeid(unsigned long)) {
			Relete();
			m_strmalloc(sizeof(int));
			sprintf(m_str, "%lu", Format);
			return STR_CORRECT;
		}
		//long long
		if (typeid(Format) == typeid(long long)) {
			Relete();
			m_strmalloc(sizeof(int));
			sprintf(m_str, "%l", Format);
			return STR_CORRECT;
		}
	}
	if (Index > this->GetStrSize() || Index <= 0){
		return STR_ERROR;
	}
	Index = Index - 1;
	int size = 0;
	char format[20] = { 0 };
	//int
	if (typeid(Format) == typeid(int)) {
		size = sizeof(int);
		strcpy(format, "%s%d");
	}
	//double
	if (typeid(Format) == typeid(double)) {
		size = sizeof(double);
		strcpy(format, "%s%f");
	}
	//float
	if (typeid(Format) == typeid(float)) {
		size = sizeof(float);
		strcpy(format, "%s%f");
	}
	//char
	if (typeid(Format) == typeid(char)) {
		size = sizeof(char);
		strcpy(format, "%s%c");
	}
	//unsigned
	if (typeid(Format) == typeid(unsigned)) {
		size = sizeof(unsigned);
		strcpy(format, "%s%u");
	}
	//unsigned int
	if (typeid(Format) == typeid(unsigned int)) {
		size = sizeof(unsigned int);
		strcpy(format, "%s%ul");
	}
	//unsigned long
	if (typeid(Format) == typeid(unsigned long)) {
		size = sizeof(unsigned long);
		strcpy(format, "%s%ul");
	}
	//long long
	if (typeid(Format) == typeid(long long)) {
		size = sizeof(long long); 
		strcpy(format, "%s%ll");
	}
	this->InsertTxT(format, Index);
	return STR_ERROR;
}

/*
�����ı�
*/
STR_FUNC_I CharString::InsertTxT(const char* Str, int Index){
	if (Index > this->GetStrSize() || Index <= 0){
		return STR_ERROR;
	}
	if (Str == NULL || this->m_str == NULL){
		return STR_ERROR;
	}
	Index = Index - 1;
	char *strp_1 = (char*)malloc((Index + (this->GetStrSize() + 1)));
	if (strp_1 == NULL){
		return STR_ERROR;
	}
	int h = 0;
	int c = 0;
	int j = 0;
	int strsize = this->GetStrSize();
	int c_str = strlen(Str);
	bool bl = false;
	memset(strp_1, 0, (Index + (this->GetStrSize()) + 1));
	for (int i = 0; i <= strsize - 1; ++i){
		if (bl == false){
			strp_1[i] = this->m_str[i];
		}
		else{
			++c;
		}
		if (i == Index){
			for (j = i; j <= i + (c_str - 1); ++j, ++h){
				strp_1[j] = Str[h];
			}
			bl = true;
			c = j;
		}
		if (bl){
			strp_1[c] = this->m_str[i];
		}
	}
	strp_1[c + 1] = '\0';
	this->Relete();
	this->m_str = (char*)malloc(strlen(strp_1) + 1);
	memset(this->m_str, 0, strlen(strp_1) + 1);
	strcpy(this->m_str, strp_1);
	free(strp_1);
	strp_1 = NULL;
	return STR_CORRECT;
}
STR_FUNC_I CharString::InsertTxT(char* Str, int Index){
	if (Index > this->GetStrSize() || Index <= 0){
		return STR_ERROR;
	}
	if (Str == NULL || this->m_str == NULL){
		return STR_ERROR;
	}
	Index = Index - 1;
	char *strp_1 = (char*)malloc((Index + (this->GetStrSize() + 1)));
	if (strp_1 == NULL){
		return STR_ERROR;
	}
	int h = 0;
	int c = 0;
	int j = 0;
	int strsize = this->GetStrSize();
	int c_str = strlen(Str);
	bool bl = false;
	memset(strp_1, 0, (Index + (this->GetStrSize()) + 1));
	for (int i = 0; i <= strsize - 1; ++i){
		if (bl == false){
			strp_1[i] = this->m_str[i];
		}
		else{
			++c;
		}
		if (i == Index){
			for (j = i; j <= i + (c_str - 1); ++j, ++h){
				strp_1[j] = Str[h];
			}
			bl = true;
			c = j;
		}
		if (bl){
			strp_1[c] = this->m_str[i];
		}
	}
	strp_1[c + 1] = '\0';
	this->Relete();
	this->m_str = (char*)malloc(strlen(strp_1) + 1);
	memset(this->m_str, 0, strlen(strp_1) + 1);
	strcpy(this->m_str, strp_1);
	free(strp_1);
	strp_1 = NULL;
	return STR_CORRECT;
}

/*
�ı����
*/
//�ı���գ���ɾ�����е��ı�ֻ����\0
STR_FUNC_I CharString::EmptyTxT(){
	if (this->m_str == NULL){
		return STR_ERROR;
	}
	this->Relete();
	this->m_str = (char*)malloc(1);
	if (m_str == NULL){
		return STR_ERROR;
	}
	m_str[0] = '\0';
}

/*
�ַ�ͳһ
*/
//�ı���ͳһֵ
STR_FUNC_I CharString::SetTxT(char Str){
	if (this->m_str == NULL || this->GetStrSize() <= 0){
		return STR_ERROR;
	}
	for (int i = 0; i <= this->GetStrSize() - 1; ++i){
		this->m_str[i] = Str;
	}
}

/*
�ַ���ȡ
*/
//��ȡָ���ı�����,��ٷ��ȶ�
STR_FUNC_I CharString::GetStrTxTIndx(const char* Str){
	if (this->m_str == NULL || Str == NULL){
		return STR_ERROR;
	}
	int StrSize = strlen(Str);
	if (StrSize <= 0){
		return STR_ERROR;
	}
	int Str_m_str = this->GetStrSize();
	int m_str_index = 0;/*����ѭ������*/
	int y = 0;
	for (int i = 0; i <= Str_m_str - 1; i++/*��һ����Ϊi��0��ʼ���·�ѭ����size+1��Ϊ�˽������ƶ����¸��ַ�*/){
		y = 0;
		m_str_index = i;
		for (int j = 0; j <= StrSize - 1; ++j, ++m_str_index){
			if (Str[j] == this->m_str[m_str_index]){
				y += 1;
			}
			if (y == StrSize){
				return i + 1;
			}
			if (Str[j] != this->m_str[m_str_index]){
				break;

			}
		}
	}
	return STR_ERROR;
}
STR_FUNC_I CharString::GetStrTxTIndx(char* Str){
	if (this->m_str == NULL || Str == NULL){
		return STR_ERROR;
	}
	int StrSize = strlen(Str);
	if (StrSize <= 0){
		return STR_ERROR;
	}
	int Str_m_str = this->GetStrSize();
	int m_str_index = 0;/*����ѭ������*/
	int y = 0;
	for (int i = 0; i <= Str_m_str - 1; i++/*��һ����Ϊi��0��ʼ���·�ѭ����size+1��Ϊ�˽������ƶ����¸��ַ�*/){
		y = 0;
		m_str_index = i;
		for (int j = 0; j <= StrSize - 1; ++j, ++m_str_index){
			if (Str[j] == this->m_str[m_str_index]){
				y += 1;
			}
			if (y == StrSize){
				return i + 1;
			}
			if (Str[j] != this->m_str[m_str_index]){
				break;

			}
		}
	}
	return STR_ERROR;
}
STR_FUNC_I CharString::GetStrTxTIndxRepeat(const char* Str, int Repeat = 0/*�ظ�����*/){
	if (this->m_str == NULL || Str == NULL){
		return STR_ERROR;
	}
	int StrSize = strlen(Str);
	if (StrSize <= 0){
		return STR_ERROR;
	}
	int Str_m_str = this->GetStrSize();
	int m_str_index = 0;/*����ѭ������*/
	int y = 0;
	int Repeat_i = 0;
	for (int i = 0; i <= Str_m_str - 1; i++/*��һ����Ϊi��0��ʼ���·�ѭ����size+1��Ϊ�˽������ƶ����¸��ַ�*/){
		y = 0;
		m_str_index = i;
		for (int j = 0; j <= StrSize - 1; ++j, ++m_str_index){
			//printf("%d", j);
			if (Str[j] == this->m_str[m_str_index]){
				y += 1;
			}
			if (y == StrSize){
				if (Repeat_i == Repeat){
					return i + 1;
				}
				else{
					Repeat_i++;
				}
			}
			if (Str[j] != this->m_str[m_str_index]){
				break;

			}
		}
	}
	return STR_ERROR;
}
STR_FUNC_I CharString::GetStrTxTIndxRepeat(char* Str, int Repeat = 0/*�ظ�����*/){
	if (this->m_str == NULL || Str == NULL){
		return STR_ERROR;
	}
	int StrSize = strlen(Str);
	if (StrSize <= 0){
		return STR_ERROR;
	}
	int Str_m_str = this->GetStrSize();
	int m_str_index = 0;/*����ѭ������*/
	int y = 0;
	int Repeat_i = 0;
	for (int i = 0; i <= Str_m_str - 1; i++/*��һ����Ϊi��0��ʼ���·�ѭ����size+1��Ϊ�˽������ƶ����¸��ַ�*/){
		y = 0;
		m_str_index = i;
		for (int j = 0; j <= StrSize - 1; ++j, ++m_str_index){
			//printf("%d", j);
			if (Str[j] == this->m_str[m_str_index]){
				y += 1;
			}
			if (y == StrSize){
				if (Repeat_i == Repeat){
					return i + 1;
				}
				else{
					Repeat_i++;
				}
			}
			if (Str[j] != this->m_str[m_str_index]){
				break;

			}
		}
	}
	return STR_ERROR;
}
STR_FUNC_I CharString::GetStrTxTIndxA(char* Str){
	return this->GetStrTxTIndx(Str) + strlen(Str);
}
STR_FUNC_I CharString::GetStrTxTIndxA(const char* Str){
	return this->GetStrTxTIndx(Str) + strlen(Str);
}
STR_FUNC_I CharString::GetStrTxTIndxEx(const char* Str){
	return this->GetStrTxTIndx(Str) + strlen(Str)+1;
}
STR_FUNC_I CharString::GetStrTxTIndxEx(char* Str){
	return this->GetStrTxTIndx(Str) + strlen(Str) + 1;
}
STR_FUNC_I CharString::GetStrTxTIndxRepeatA(char* Str, int Repeat = 0/*�ظ�����*/){
	return this->GetStrTxTIndxRepeat(Str, Repeat) + strlen(Str);
}
STR_FUNC_I CharString::GetStrTxTIndxRepeatA(const char* Str, int Repeat = 0/*�ظ�����*/){
	return this->GetStrTxTIndxRepeat(Str, Repeat) + strlen(Str);
}
STR_FUNC_I CharString::GetStrTxTIndxRepeatEx(char* Str, int Repeat = 0/*�ظ�����*/){
	return this->GetStrTxTIndxRepeat(Str, Repeat) + strlen(Str)+1;
}
STR_FUNC_I CharString::GetStrTxTIndxRepeatEx(const char* Str, int Repeat = 0/*�ظ�����*/){
	return this->GetStrTxTIndxRepeat(Str, Repeat) + strlen(Str)+1;
}
/*
�ж��ı��Ƿ����
*/
STR_FUNC_BL CharString::JumpTxTExits(char *Str){
	if (GetStrTxTIndx(Str) == -1){
		return false;
	}
	return true;
}

/*
ȡһ���ı�
*/
//ȡһ���ı�
STR_FUNC_CP CharString::GetLineTxT(int LineIndex = 1) {
	if (LineIndex == 0){
		return STR_ERROR;
	}
	if (this->m_str == NULL) {
		return STR_ERROR;
	}
	int l = 0;
	char *yun = NULL;
	int j = 0;
	int u = 0;
	for (int i = 0; i <= this->GetStrSize() + 1/*����\0*/; ++i) {
		if (this->m_str[i] == '\n') {
			++l;
			if (l != LineIndex)
				u = i + 1;//+1����\n �������1�����Ѿ�����0��Ϊ�Ѿ����ǵ�һ������
		}
		if (l == LineIndex) {
			//�жϴ��ж೤���ڷ����ڴ�
			for (j = u;; ++j) {
				if (this->m_str[j] == '\n' || this->m_str[j] == '\0') {
					int size = 0;
					if (u == 0){//��ֹ��0�±굼�¼���ʵ�ʳ�����1����Ϊ�����1Ҫ����\0
						size = j + 1;	//+1����Ϊ�����ڴ治�Ǵ�0���±�������Ҫ�ж��Ƿ�Ϊ0
					}
					else{
						size = j;
					}
					yun = (char*)malloc(size + 1);	//���������ֽ�,\0
					memset(yun, 0, size + 1);
					break;
				}
			}
			int in = 0;
			for (int n = u; n <= j; ++n, ++in) {
				yun[in] = this->m_str[n];
			}
			return yun;
		}
	}
}

/*
��ȡ�ı�������
*/
//��ȡ�ı�������
STR_FUNC_I CharString::GetLineNum(){
	if (this->m_str == NULL){
		return STR_ERROR;
	}
	int Size = 0;
	for (int i = 0; i <= this->GetStrSize(); ++i){
		if (this->m_str[i] == '\n'){
			++Size;
		}
		if (this->m_str[i] == '\0'){
			if (this->m_str[i - 1] != '\n'){
				Size++;
			}
			return Size;
		}
	}
}

/*
��ȡ�ı�������
*/
//��ȡ�ı�������
STR_FUNC_I CharString::GetTxTLineNum(char *Str){
	if (Str == NULL || this->m_str == NULL){
		return NULL;
	}
	char *str1 = NULL;
	int i = 0;
	int u = this->GetLineNum();
	while (1){//��������ı���ʽ�ڵڼ�����
		str1 = GetLineTxT(i);
		if (str1 == NULL){
			return NULL;
		}
		if (JumpTxTExits(str1) == TRUE){
			break;
		}
		++i;
		if (i > u){
			return 0;
		}
	}
	return i;
}

/*
ȡ�����ı�
*/
//ȡ�ұ��ı�
STR_FUNC_CP CharString::GetRightTxT(int Length){
	if (Length == 0){
		return STR_ERROR;
	}
	if (Length >= GetStrSize() - Length){
		return STR_ERROR;
	}
	if (this->m_str == NULL){
		return STR_ERROR;
	}
	char *str = (char*)malloc(Length + 1);
	memset(str, 0, Length + 1);
	int in = 0;
	for (int i = (this->GetStrSize()-1)-Length; i <= (this->GetStrSize()-1); ++i, ++in){
		str[in] = this->m_str[i];
	}
	return str;
}
//ȡ�ұ��ı�����
STR_FUNC_I CharString::GetRightIndex(){
	if (this->m_str == NULL || this->GetStrSize() <= 0){
		return STR_ERROR;
	}
	return this->GetStrSize();
}
//ȡ����ı�
STR_FUNC_CP CharString::GetLeftTxT(int Length){
	if (Length == 0){
		return STR_ERROR;
	}
	if (Length >= GetStrSize() - Length){
		return STR_ERROR;
	}
	if (this->m_str == NULL){
		return 0;
	}
	char *str = (char*)malloc(Length + 1);
	memset(str, 0, Length + 1);
	int in = 0;
	for (int i = 0; i <= Length; ++i, ++in){
		str[in] = this->m_str[i];
	}
	return str;
}
//ȡ����ı���Ч�ı�
STR_FUNC_I CharString::GetLeftIndex(){
	if (this->m_str == NULL || this->GetStrSize() <= 0){
		return STR_ERROR;
	}
	for (int i = 0; i <= this->GetStrSize() - 1; ++i){
		if (this->m_str[i] != '\0'){
			return i + 1;
		}
	}
	return STR_ERROR;
}
//ȡ�м��ı�
STR_FUNC_CP CharString::GetMiddle(int Length){
	if (Length == 0){
		return STR_ERROR;
	}
	if (Length >= GetStrSize() - Length){
		return STR_ERROR;
	}
	if (this->m_str == NULL){
		return STR_ERROR;
	}
	int s_cp = this->GetStrSize() / 2;
	if (s_cp <= 0){
		return STR_ERROR;
	}
	char* m_c = (char*)malloc(Length + 1);
	if (m_c == NULL){
		return STR_ERROR;
	}
	int y = 0;
	for (int i = s_cp; i <= s_cp + Length; ++i){
		m_c[y] = this->m_str[i];
	}
	return m_c;
}
//ȡ�м��ı�������
STR_FUNC_I CharString::GetMiddleIndex(){
	if (this->m_str == NULL || this->GetStrSize() <= 0){
		return STR_ERROR;
	}
	int s_cp = this->GetStrSize() / 2;
	if (s_cp <= 0){
		return STR_ERROR;
	}
	return s_cp;
}

/*
�������ַ���ȡ
*/
//�������ַ���ȡ
STR_FUNC_CP CharString::IndexToCharCutOut(int Index, char Str){
	if (Index <= 0 || Str == 0 || Index > this->GetStrSize()){
		return STR_ERROR;
	}
	int Is = this->GetStrSize();
	int Size = 1;
	for (int i = Index - 1; i <= this->GetStrSize(); ++i){
		if (this->m_str[i] == Str){
			char* r_str = (char*)malloc(Size + 1);
			if (r_str == NULL){
				return STR_ERROR;
			}
			memset(r_str, 0, Size + 1);
			int s = Index - 1;
			for (int j = 0; j <= Size - 1; ++j, ++s){
				r_str[j] = this->m_str[s];
			}
			return r_str;
		}
		++Size;
	}
	return STR_ERROR;
}
//�����ַ���ȡ
STR_FUNC_CP CharString::CharToCharCutOut(char Str1, char Str2){
	if (Str1 <= 0 || Str2 == 0){
		return NULL;
	}
	int Is = this->GetStrSize();
	int Size = 0;
	for (int i = 0; i <= this->GetStrSize(); ++i){
		if (this->m_str[i] == Str1){
			for (int d = i; d <= this->GetStrSize(); ++d){//���㳤��
				++Size;
				if (this->m_str[d] == Str2){
					break;
				}
			}
			char* r_str = (char*)malloc(Size + 1);
			memset(r_str, 0, Size + 1);
			if (r_str == NULL){
				return NULL;
			}
			int s = i;
			for (int j = 0; j <= Size - 1; ++j, ++s){
				r_str[j] = this->m_str[s];
			}
			return r_str;
		}
	}
	return NULL;
}

/*
�����ı���ȡ
*/
//�������ȡ�ı���ʹ�÷����������ı��� txt:1,2,3,4\r\n ʹ�÷�����AnalysisTxTtoArr(':',',','\r',x) ÿ�λ����x��������'1''2''3'
//�����������ַ������ظ����ַ��������Ǽ����ڼ���Ŀ�����<1,2,3><1,2,3> ������2�Ļ��ͼ����ڶ���
STR_FUNC_CP CharString::ThreePoints_AnalysisTxTtoArr(char Str1/*��һ��char*/, char Str2/*�м�char*/, char Str3/*��βchar*/, int Index/*����*/){
	if (this->m_str == NULL){
		return STR_ERROR;
	}
	if (Str1 == Str2 || Str2 == Str3){
		return STR_ERROR;
	}
	if (this->GetStrSize() <= 0){
		return STR_ERROR;
	}
	if (Index <= 0){
		return STR_ERROR;
	}
	Index = Index - 1;
	this->FuncTion_CharInToCharAscii(Str1);
	this->FuncTion_CharInToCharAscii(Str2);
	this->FuncTion_CharInToCharAscii(Str3);
	int uIndex = 0;//����
	int c_size = 0;//��С��str1��ʼ����õ�˫���ַ���ֹС
	int iis = 0;	//��λ��һ��str2������ 
	int yuno = 0;	//��һ����β�ַ�
	for (int i = 0; i <= this->GetStrSize(); ++i){
		if (this->m_str[i] == Str1){

			for (int j = i; j <= this->GetStrSize(); ++j){
				if (this->m_str[j] == Str2){
					yuno = j;
					++uIndex;
				}
				++c_size;
				if (uIndex == Index){
					if (Index != 1){
						iis = j - 1;
					}
					else{
						iis = i + 1;
					}
					char* str = (char*)malloc(c_size + 1);
					memset(str, 0, c_size + 1);
					int y = 0;
					for (int u = iis; u <= this->GetStrSize(); ++u, ++y){
						if (this->m_str[u] == Str2){
							char *i_str = NULL;
							i_str = (char*)malloc(strlen(str) + 1);
							memset(i_str, 0, strlen(str) + 1);
							strcpy(i_str, str);
							free(str);
							str = NULL;
							return i_str;
						}
						str[y] = m_str[u];
					}

				}
				else{
					if (Index == 1){
						iis = i + 1;
					}
				}
			}
			//	return NULL;
		}
		if (m_str[i] == Str3){
			//�ȿ�����һ���ָ����ǲ���һ����
			int usize = 0;
			int y = 0;
			if (m_str[yuno] == Str2){
				for (int i = yuno; i <= this->GetStrSize(); ++i){
					++usize;
				}
				char *i_str = NULL;
				i_str = (char*)malloc(usize + 1);
				memset(i_str, 0, usize + 1);
				for (int i = yuno + 1; i <= this->GetStrSize(); ++i, ++y){
					if (m_str[i] == Str3){
						return i_str;
					}
					i_str[y] = m_str[i];
				}


			}
			return NULL;
		}
	}
}
//�������ȡ�ı�����ȡ��ʽ��С��ȡ�ж��ٸ�ģ�����<1,2,3><1,2,3>  �ͷ���2
STR_FUNC_I CharString::ThreePoints_AnalysisGetTxTtoArrNum(char Str1/*��һ��char*/, char Str2/*�м�char*/, char Str3/*��βchar*/){
	if (this->m_str == NULL){
		return STR_ERROR;
	}
	if (Str1 == Str2 || Str2 == Str3){
		return NULL;
	}
	this->FuncTion_CharInToCharAscii(Str1);
	this->FuncTion_CharInToCharAscii(Str2);
	this->FuncTion_CharInToCharAscii(Str3);
	int u = 0;
	for (int i = 0; i <= this->GetStrSize(); ++i){
		if (this->m_str[i] == Str2){
			++u;
		}
		if (this->m_str[i] == Str3){
			return u + 1;
		}
	}
}

/*
�ü��ı�
*/
STR_FUNC_I CharString::CutOutTxT(char *Str){
	if (this->m_str == NULL || Str == NULL || this->GetStrSize() <= 0){
		return STR_ERROR;
	}
	int yun = 0;
	int yIndex = 0;
	int you = (strlen(this->m_str) - strlen(Str)) + 1;
	int F1 = this->GetStrSize();
	int yF = strlen(Str);
	char *m_u = (char*)malloc(you);
	if (m_u == NULL){
		return STR_ERROR;
	}
	memset(m_u, 0, (strlen(this->m_str) - strlen(Str)) + 1);
	for (int i = 0; i <= F1; ++i){
		yun = i;
		for (int j = 0; j <= yF - 1; ++j, ++yun){
			if (Str[j] != this->m_str[yun]){
				break;
			}
			if (j == strlen(Str) - 1){
				for (int u = 0; u <= i - 1; ++u){
					m_u[u] = this->m_str[u];
				}
				int c = i + strlen(Str);
				for (int u = i; u <= F1 - 2; ++u, ++c){
					m_u[u] = this->m_str[c];
				}
				free(this->m_str);
				this->m_str = NULL;
				this->m_str = (char*)malloc(you);
				if (this->m_str == NULL){
					return STR_ERROR;
				}
				memset(this->m_str, 0, you);
				strcpy(this->m_str, m_u);
				free(m_u);
				m_u = NULL;
				return STR_CORRECT;

			}
		}
	}
}
STR_FUNC_I CharString::CutOutTxT(const char *Str){
	if (this->m_str == NULL || Str == NULL || this->GetStrSize() <= 0){
		return STR_ERROR;
	}
	int yun = 0;
	int yIndex = 0;
	int you = (strlen(this->m_str) - strlen(Str)) + 1;
	int F1 = this->GetStrSize();
	int yF = strlen(Str);
	char *m_u = (char*)malloc(you);
	if (m_u == NULL){
		return STR_ERROR;
	}
	memset(m_u, 0, (strlen(this->m_str) - strlen(Str)) + 1);
	for (int i = 0; i <= F1; ++i){
		yun = i;
		for (int j = 0; j <= yF - 1; ++j, ++yun){
			if (Str[j] != this->m_str[yun]){
				break;
			}
			if (j == strlen(Str) - 1){
				for (int u = 0; u <= i - 1; ++u){
					m_u[u] = this->m_str[u];
				}
				int c = i + strlen(Str);
				for (int u = i; u <= F1 - 2; ++u, ++c){
					m_u[u] = this->m_str[c];
				}
				free(this->m_str);
				this->m_str = NULL;
				this->m_str = (char*)malloc(you);
				if (this->m_str == NULL){
					return STR_ERROR;
				}
				memset(this->m_str, 0, you);
				strcpy(this->m_str, m_u);
				free(m_u);
				m_u = NULL;
				return STR_CORRECT;

			}
		}
	}
}
STR_FUNC_I CharString::CutOutTxT(char Str){
	if (this->m_str == NULL || Str == NULL || this->GetStrSize() <= 0){
		return STR_ERROR;
	}
	char st[4] = { 0 };
	sprintf(st, "%c", Str);
	this->CutOutTxT(st);
	return STR_CORRECT;
}
STR_FUNC_I CharString::CutOutTxT(int Index){
	if (this->m_str == NULL || Index > this->GetStrSize() || this->GetStrSize() <= 0){
		return STR_ERROR;
	}
	char st[4] = { 0 };
	sprintf(st, "%c", this->m_str[Index]);
	this->CutOutTxT(st);
	return STR_CORRECT;
}


/*
�ı�����
*/
//�ı�����_��ǰ
STR_FUNC_I  CharString::TxTReveresOrder_AfterToFront(){
	if (this->m_str == NULL || this->GetStrSize()<=0){
		return STR_ERROR;
	}
	int c = this->GetStrSize();
	char *str = (char*)malloc(this->GetStrSize() + 1);
	if (str == NULL){
		return STR_ERROR;
	}
	memset(str, 0, this->GetStrSize() + 1);
	for (int i = 0; i <= this->GetStrSize() - 1; ++i,--c){
		str[i] = this->m_str[c];
	}
	str[this->GetStrSize() + 1] = '\0';
	this->Relete();
	m_str = (char*)malloc(strlen(str) + 1);
	memset(m_str, 0, strlen(str) + 1);
	strcpy(m_str, str);
	free(str);
	str = NULL;
	return STR_CORRECT;
}
//�ı�����_ǰ����
STR_FUNC_I CharString::TxTReveresOrder_FrontToAfter(){
	if (this->m_str == NULL || this->GetStrSize() <= 0){
		return STR_ERROR;
	}
	int c = 0;
	char *str = (char*)malloc(this->GetStrSize() + 1);
	if (str == NULL){
		return STR_ERROR;
	}
	memset(str, 0, this->GetStrSize() + 1);
	for (int i = this->GetStrSize(); i >= 0 ; --i, ++c){
		str[i] = this->m_str[c];
	}
	str[this->GetStrSize() + 1] = '\0';
	this->Relete();
	m_str = (char*)malloc(strlen(str) + 1);
	memset(m_str, 0, strlen(str) + 1);
	strcpy(m_str, str);
	free(str);
	str = NULL;
	return STR_CORRECT;
}

/*
�ı��滻
*/
STR_FUNC_I CharString::TxTReplace(const char* Str1, const char* Str2){
	if (this->m_str == NULL || Str1 == NULL || Str2 == NULL || this->GetStrSize() <= 0){
		return STR_ERROR;
	}
	int c = this->GetStrTxTIndx(Str1) - 1;
	if (c == STR_ERROR){
		return STR_ERROR;
	}
	this->CutOutTxT(Str1);	//ɾ��
	this->InsertTxT(Str2, c);	//����
	return STR_CORRECT;
}
//�����ı��滻
STR_FUNC_I CharString::TxTReplace(int Index, const char* Str){
	if (this->m_str == NULL || Index <= 0 || Str == NULL || this->GetStrSize() <= 0){
		return STR_ERROR;
	}
	char* st = NULL;
	int c = 0;
	if ((strlen(this->m_str) - Index) - strlen(Str) != 0){
		c = strlen(this->m_str) + 1;
	}
	else{
		c = strlen(this->m_str) + strlen(Str) + 1;
	}
	st = (char*)malloc(c);
	if (st == NULL){
		return STR_ERROR;
	}

	memset(st, 0, c);
	for (int i = 0; i <= Index - 2/*ȥ����������*/; ++i){
		st[i] = this->m_str[i];
	}
	int o = 0;
	for (int i = Index - 1; i <= Index + strlen(Str) - 1; ++i, ++o){
		st[i] = Str[o];
	}
	int u = Index + strlen(Str);
	for (int i = Index + strlen(Str) - 1; i <= c - 1; ++i){
		st[i] = this->m_str[i];

	}
	free(this->m_str);
	this->m_str = NULL;
	this->m_str = (char*)malloc(c);
	memset(this->m_str, 0, c);
	strcpy(this->m_str, st);
	free(st);
	st = NULL;
	return STR_CORRECT;
}

/*
�ַ�β����ȷ��
*/
//�ַ�β����ȷ��
STR_FUNC_I CharString::CORRECT_STR(){
	if (this->m_str == NULL || this->GetStrSize() <= 0){
		return STR_ERROR;
	}
	this->m_str[this->GetStrSize()] = '\0';
	return STR_CORRECT;
}

/*
��ʽ���
*/
STR_FUNC_CP CharString::GetFormatTwo(const char Format, int Str_Index){
	if (this->m_str == NULL || this->GetStrSize() <= 0){
		return STR_ERROR;
	}
	//1��ȡ��ߣ�2��ȡ�ұ�
	if (Str_Index > 2){//������2������
		Str_Index = 2;
	}
	if (Str_Index < 1){	///1Ҳһ��
		Str_Index = 1;
	}
	for (int i = 0; i <= this->GetStrSize() - 1; ++i){
		if (this->m_str[i] == Format){
			//ȡ�ַ�
			if (Str_Index == 1){
				char * str = (char*)malloc(i + 1);
				memset(str, 0, i + 1);
				for (int j = 0; j < i; ++j){
					str[j] = this->m_str[j];
				}
				return str;
			}
			else{
				int c = 0;
				//ȡ��벿�ִ�С
				for (int k = i+1; this->m_str[k] != '\0'; ++k){
					++c;
				}
				char * str = (char*)malloc(c + 1);
				memset(str, 0, c + 1);
				int u = i+1;//����ԭ�����ַ�
				for (int j = 0; j < c; ++j,++u){
					str[j] = this->m_str[u];
				}
				return str;
			}
		}
	}
	return STR_ERROR;
}

/*
�ж��ַ��Ƿ����
*/
STR_FUNC_I CharString::IF_Char(char Char_){
	if (this->STR_IF_CORRECT() == STR_ERROR){
		return STR_ERROR;
	}
	for (int i = 0; i < this->GetStrSize(); ++i){
		if (this->m_str[i] == Char_){
			return STR_CORRECT;
		}
	}
	return STR_ERROR;
}

/*
ȡָ����ʽ�ַ�
*/
STR_FUNC_CP CharString::Clip(char Format, int About, int Index = 1, char InFormat = 0x20){
	if (this->STR_IF_CORRECT() == STR_ERROR){
		return STR_ERROR;
	}
	int InF = 0;
	int InD = 0;
	for (int i = 0; i <= strlen(this->m_str) - 1; ++i){
		if (this->m_str[i] == Format){
			++InF;
			if (InF == Index){
				if (About == 1){
					int size = 0;
					for (int j = InD; this->m_str[j] != Format; ++j){
						++size;
					}
					char* str = (char*)malloc(size + 1);
					memset(str, 0, size + 1);
					int u = 0;
					for (int j = InD; this->m_str[j] != Format; ++j, ++u){
						str[u] = this->m_str[j];
					}
					return str;
				}
				if (About == 2){
					int size = 0;
					for (int j = i + 1;; ++j){
						if (this->m_str[j] == InFormat || this->m_str[j] == '\0'){
							break;
						}
						++size;
					}
					char* str = (char*)malloc(size + 1);
					memset(str, 0, size + 1);
					int u = 0;
					for (int j = i + 1;; ++j, ++u){
						if (this->m_str[j] == InFormat || this->m_str[j] == '\0'){
							break;
						}
						str[u] = this->m_str[j];
					}
					return str;
				}
			}
		}
		if (this->m_str[i] == InFormat){
			InD = i + 1;
		}
	}
	return STR_ERROR;
}
STR_FUNC_CP CharString::ClipLine(char Format, int About, int Line, int Index = 1, char InFormat = 0x20){
	if (this->STR_IF_CORRECT() != STR_CORRECT){
		return STR_ERROR;
	}
	if (Line > this->GetLineNum()){
		return STR_ERROR;
	}
	//�����滻����
	char* str = this->GetLineTxT(Line);
	char* strcopy = (char*)malloc(this->GetStrSize() + 1);
	memset(strcopy, 0, this->GetStrSize() + 1);
	strcpy(strcopy, this->m_str);
	this->Relete();
	this->m_str = (char*)malloc(strlen(str)+1);
	memset(this->m_str, 0, strlen(str) + 1);
	strcpy(this->m_str, strcopy);
	char *rstr = this->Clip(Format, About, Index, InFormat);
	this->Relete();
	this->m_str = (char*)malloc(strlen(strcopy) + 1);
	memset(this->m_str, 0, strlen(strcopy) + 1);
	strcpy(this->m_str, strcopy);
	free(strcopy);
	strcopy = NULL;
	return rstr;
}
/*
У�鵱ǰ�ַ��Ƿ���ȷ
*/
STR_FUNC_I CharString::STR_IF_CORRECT(){
	if (this->m_str == NULL || this->GetStrSize() <= 0){
		return STR_ERROR;
	}
	if (this->m_str[GetStrSize()] != '\0'){
		this->m_str[this->GetStrSize()] = '\0';
	}
	return STR_CORRECT;
}

/*
ȡ�����ı�+���ַ�
*/
STR_FUNC_CP CharString::Mid(int Index, int Lent){
	if (this->STR_IF_CORRECT() != STR_CORRECT){
		return STR_ERROR;
	}
	char* str = (char*)malloc(Lent + 1);
	memset(str, 0, Lent + 1);
	int u = 0;
	for (int i = Index - 1; i <= (Index + Lent) - 2; ++i, ++u){
		str[u] = this->m_str[i];
	}
	return str;
}

/*
�ж��ַ��Ƿ����0
*/
STR_FUNC_BL CharString::Nsize(){
	if (this->GetStrSize() <= 0){
		return true;
	}
	return false;
}

/*
�ж��ַ��Ƿ�Ϊ�����ַ�
*/
STR_FUNC_BL CharString::JuNum(int Index){
	if (this->STR_IF_CORRECT() != STR_CORRECT){
		return STR_ERROR;
	}
	if (this->m_str[Index] >= '0' && this->m_str[Index] <= '9'){
		return true;
	}
	return false;
}
STR_FUNC_BL CharString::JuNumStr(){
	if (this->STR_IF_CORRECT() != STR_CORRECT){
		return STR_ERROR;
	}
	for (int i = 0; i <= strlen(m_str) - 1; ++i){
		if (JuNum(i) != true){
			return false;
		}
	}
	return true;
}

/*
��ȡָ���ַ����������
*/
STR_FUNC_I CharString::GetStrAfterNum(char* Str){
	if (this->STR_IF_CORRECT() != STR_CORRECT){
		return STR_ERROR;
	}
	int Y = this->GetStrTxTIndx(Str) + strlen(Str) + 1;
	int size = 0;
	for (int i = Y; JuNum(i) == true; ++i){
		++size;
	}
	char* str1 = (char*)malloc(size + 1);
	memset(str1, 0, size + 1);
	int u = 0;
	for (int i = Y; JuNum(i) == true; ++i, ++u){
		str1[u] = m_str[i];
	}
	return atoi(str1);
}
STR_FUNC_CP CharString::GetStrAfterNumA(char* Str){
	if (this->STR_IF_CORRECT() != STR_CORRECT){
		return STR_ERROR;
	}
	int Y = this->GetStrTxTIndx(Str) + strlen(Str) + 1;
	int size = 0;
	for (int i = Y; JuNum(i) == true; ++i){
		++size;
	}
	char* str1 = (char*)malloc(size + 1);
	memset(str1, 0, size + 1);
	int u = 0;
	for (int i = Y; JuNum(i) == true; ++i, ++u){
		str1[u] = this->m_str[i];
	}
	return str1;
}
STR_FUNC_D CharString::GetStrAfterDouble(char* Str){
	if (this->STR_IF_CORRECT() != STR_CORRECT){
		return STR_ERROR;
	}
	int Y = this->GetStrTxTIndx(Str) + strlen(Str) + 1;
	int size = 0;
	int fo = 0;
	for (int i = Y;; ++i){
		if (this->m_str[i] == '.'){
			if (fo == 0){
				++size;
				++fo;
				continue;
			}
			else{
				break;
			}
		}
		else if (JuNum(i) != true){
			break;
		}
		++size;
	}
	char* str1 = (char*)malloc(size + 1);
	memset(str1, 0, size + 1);
	int u = 0;
	int uy = 0;
	for (int i = Y;; ++i, ++u){
		if (this->m_str[i] == '.'){//�����.23֮��ĸ����ʾ��Ĭ��������0
			if (uy == 0){
				str1[0] = '0';
				++uy;
			}
		}
		else if (JuNum(i) != true){
			return atof(str1);
		}
		str1[u] = this->m_str[i];
	}
	return STR_ERROR;
}
STR_FUNC_CP CharString::GetStrAfterDoubleA(char* Str){
	if (this->STR_IF_CORRECT() != STR_CORRECT){
		return STR_ERROR;
	}
	int Y = this->GetStrTxTIndx(Str) + strlen(Str) + 1;
	int size = 0;
	int fo = 0;
	for (int i = Y;; ++i){
		if (this->m_str[i] == '.'){
			if (fo == 0){
				++size;
				++fo;
				continue;
			}
			else{
				break;
			}
		}
		else if (JuNum(i) != true){
			break;
		}
		++size;
	}
	char* str1 = (char*)malloc(size + 1);
	memset(str1, 0, size + 1);
	int u = 0;
	int uy = 0;
	for (int i = Y;; ++i, ++u){
		if (this->m_str[i] == '.'){//�����.23֮��ĸ����ʾ��Ĭ��������0
			if (uy == 0){
				str1[0] = '0';
				++uy;
			}
		}
		else if (JuNum(i) != true){
			return str1;
		}
		str1[u] = this->m_str[i];
	}
	return STR_ERROR;
}

/*
��ʽ�ü�
*/
STR_FUNC_CP  CharString::Cin(char Format, int Index){
	if (this->STR_IF_CORRECT() != STR_CORRECT){
		return STR_ERROR;
	}
	int InD = 0;
	int InI = 0;
	int size = 0;
	int u = 0;
	int ucn = 0;
	bool Bu = true;
	for (int i = 0; i <= strlen(this->m_str) - 1; ++i){
		if (this->m_str[i] == Format){
			++InD;
			if (InD != Index){	//��������ڱ�����һ�ε�����
				InI = i + 1;
			}
		}
		if (InD == Index){
			for (int j = InI; j <= i - 1; ++j){
				++size;
			}
			char* str1 = (char*)malloc(size + 1);
			memset(str1, 0, size + 1);
			for (int j = InI; j <= i - 1; ++j, ++u){
				str1[u] = this->m_str[j];
			}
			return str1;
		}
	}
	return STR_ERROR;
}

/*�ַ����*/
STR_FUNC_I CharString::CharSet(char Str1, char Str2){
	if (this->STR_IF_CORRECT() != STR_CORRECT){
		return STR_ERROR;
	}
	for (int i = 0; i <= this->GetStrSize(); ++i){
		if (this->m_str[i] == Str1){
			this->m_str[i] = Str2;
		}
	}
}

/*�����*/
CharString & CharString::operator = (const char * Str){
	this->Input(Str);
	return *this;
}
CharString & CharString::operator = (const char  Str){
	this->Relete();
	this->m_str = (char*)malloc(sizeof(char)+1);
	memset(this->m_str, 0, sizeof(char)+1);
	sprintf(this->m_str, "%c", Str);
	return *this;
}
//+
CharString & CharString:: operator + (const char *Str) {
	this->Splicing(Str);
	return *this;
}
//-
CharString & CharString::operator - (char *Str) {
	this->CutOutTxT(Str);
	return *this;
}
//[]
STR_FUNC_C & CharString::operator [] (int I){
	return this->m_str[I-1];
}
//%��ȡ��
STR_FUNC_CP CharString::operator % (int I) {
	return this->GetLineTxT(I);
}
//==
STR_FUNC_BL CharString::operator == (const char *Str) {
	if (0 == strcmp(this->m_str, Str)) {
		return true;
	}
	else {
		return false;
	}
}
//()
CharString & CharString::operator () (const char *Str) {
	this->Relete();
	this->Input(Str);
	return *this;
}
/*
�����Թ���ʵ��
*/
//��Ӣ�ĸ���ת���ַ�ת��
STR_FUNC_VOID CharString::FuncTion_CharInToCharAscii(char &Cstr){
	switch (Cstr){
	case '��':
		Cstr = ':';
		break;
	case '��':
		Cstr = ',';
		break;
	case '��':
		Cstr = '.';
		break;
	case '��':
		Cstr = '\'';
		break;
	case '��':
		Cstr = '\'';
		break;
	case '��':
		Cstr = '>';
		break;
	case '||':
		Cstr = '|';
		break;
	case '��':
		Cstr = '<';
	case '��':
		Cstr = '\\';
	case '��':
		Cstr = '?';
		break;
	default:
		break;
	}
}
