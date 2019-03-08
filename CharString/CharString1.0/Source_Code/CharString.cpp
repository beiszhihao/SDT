/*
CharString.cpp
*/
#include "CharString.h"

/*
构造
*/
//无参构造
CharString::CharString(){
	if (this->m_str != NULL){
		this->Relete();
		this->m_str == NULL;
	}
}
//带参构造
CharString::CharString(const char* Str){
	if (this->m_str != NULL || Str == NULL) {
		this->Relete();
	}
	int strSize = strlen(Str);
	this->m_str = (char*)malloc(strSize + 1);	//\0
	memset(this->m_str, 0, strSize + 1);
	strcpy(this->m_str, Str);
}
//重载
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
析构
*/
//无参析构
CharString::~CharString(){
	if (this->m_str != NULL){	//重复判断，防止使用函数寄存器以及函数现场保护
		this->Relete();
	}
}

/*
释放字符串
*/
//释放字符串
STR_FUNC_VOID CharString::Relete(){
	if (this->m_str != NULL) {
		free(this->m_str);
		this->m_str = NULL;
	}
}

/*
获取字符串大小
*/
//不包含\0
STR_FUNC_SLLI CharString::GetStrSize(){
	if (this->m_str == NULL) {
		return 0;
	}
	int m_size;
	for (m_size = 0; this->m_str[m_size] != '\0'; ++m_size) {}
	return m_size;
}

/*
字符剔除
*/
//删除指定字符后的字符
STR_FUNC_8BIT CharString::DeleteAppointStr(char Str, int Method = CHARSTRING_FRONT/*从哪开始,0前，1后*/, BOOL Retain = FALSE/*是否保留原字符*/){
	if (Str == NULL) {
		return STR_ERROR;
	}
	if (this->m_str == NULL) {
		return STR_ERROR;
	}
	if (Method == CHARSTRING_FRONT) {
		for (int i = 0;i<=this->GetStrSize(); ++i) {

			if (Str == this->m_str[i]/*指针偏移递增*/) {
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
				copy_str = (char*)malloc(i);//\0和原字符
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
			if (Str == this->m_str[i]/*指针偏移递增*/) {
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
				copy_str = (char*)malloc(i);//\0和原字符
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
字符打印
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
字符压入
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
//重载
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
字符串拼接
*/
//字符拼接
STR_FUNC_8BIT CharString::Splicing(const char *Str){
	if (Str == NULL) {
		return STR_ERROR;
	}
	if (this->m_str != NULL) {
		//保存原字符
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
		//获取字符串大小
		signed long long int i = strlen(Str);
		this->m_str = (char*)malloc(L_Size + i + 1);
		memset(this->m_str, 0, L_Size + i + 1);
		strcpy(this->m_str, copy_str);
		//防止立即数copy之前将值复制一份
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
//重载
STR_FUNC_8BIT CharString::Splicing(char *Str){
	if (Str == NULL) {
		return STR_ERROR;
	}
	if (this->m_str != NULL) {
		//保存原字符
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
		//获取字符串大小
		signed long long int i = strlen(Str);
		this->m_str = (char*)malloc(L_Size + i + 1);
		memset(this->m_str, 0, L_Size + i + 1);
		strcpy(this->m_str, copy_str);
		//防止立即数copy之前将值复制一份
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
获取Data
*/
STR_FUNC_CP CharString::GetData(){
	if (this->m_str == NULL) {
		return STR_ERROR;
	}
	return this->m_str;
}
//深copy
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
字符裁剪
*/
//字符裁剪,裁剪a到b之间的数据
STR_FUNC_I CharString::TailoringIndexToIndex(int A, int B) {
	if (this->m_str == NULL) {
		return STR_ERROR;
	}
	if (strlen(this->m_str) > B) {
		return STR_ERROR;
	}
	//定位A
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
	//裁剪
	free(this->m_str);
	this->m_str = NULL;
	this->m_str = (char*)malloc(size + 1);
	memset(this->m_str, 0, size + 1);
	strcpy(this->m_str, str1);
	return STR_CORRECT;
}

/*
格式化字符;

*/
//其他类型到字符
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
插入文本
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
文本清空
*/
//文本清空，会删除所有的文本只留下\0
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
字符统一
*/
//文本置统一值
STR_FUNC_I CharString::SetTxT(char Str){
	if (this->m_str == NULL || this->GetStrSize() <= 0){
		return STR_ERROR;
	}
	for (int i = 0; i <= this->GetStrSize() - 1; ++i){
		this->m_str[i] = Str;
	}
}

/*
字符获取
*/
//获取指定文本索引,穷举法稳定
STR_FUNC_I CharString::GetStrTxTIndx(const char* Str){
	if (this->m_str == NULL || Str == NULL){
		return STR_ERROR;
	}
	int StrSize = strlen(Str);
	if (StrSize <= 0){
		return STR_ERROR;
	}
	int Str_m_str = this->GetStrSize();
	int m_str_index = 0;/*二次循环坐标*/
	int y = 0;
	for (int i = 0; i <= Str_m_str - 1; i++/*加一是因为i从0开始，下方循环是size+1是为了将坐标移动到下个字符*/){
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
	int m_str_index = 0;/*二次循环坐标*/
	int y = 0;
	for (int i = 0; i <= Str_m_str - 1; i++/*加一是因为i从0开始，下方循环是size+1是为了将坐标移动到下个字符*/){
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
STR_FUNC_I CharString::GetStrTxTIndxRepeat(const char* Str, int Repeat = 0/*重复次数*/){
	if (this->m_str == NULL || Str == NULL){
		return STR_ERROR;
	}
	int StrSize = strlen(Str);
	if (StrSize <= 0){
		return STR_ERROR;
	}
	int Str_m_str = this->GetStrSize();
	int m_str_index = 0;/*二次循环坐标*/
	int y = 0;
	int Repeat_i = 0;
	for (int i = 0; i <= Str_m_str - 1; i++/*加一是因为i从0开始，下方循环是size+1是为了将坐标移动到下个字符*/){
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
STR_FUNC_I CharString::GetStrTxTIndxRepeat(char* Str, int Repeat = 0/*重复次数*/){
	if (this->m_str == NULL || Str == NULL){
		return STR_ERROR;
	}
	int StrSize = strlen(Str);
	if (StrSize <= 0){
		return STR_ERROR;
	}
	int Str_m_str = this->GetStrSize();
	int m_str_index = 0;/*二次循环坐标*/
	int y = 0;
	int Repeat_i = 0;
	for (int i = 0; i <= Str_m_str - 1; i++/*加一是因为i从0开始，下方循环是size+1是为了将坐标移动到下个字符*/){
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
STR_FUNC_I CharString::GetStrTxTIndxRepeatA(char* Str, int Repeat = 0/*重复次数*/){
	return this->GetStrTxTIndxRepeat(Str, Repeat) + strlen(Str);
}
STR_FUNC_I CharString::GetStrTxTIndxRepeatA(const char* Str, int Repeat = 0/*重复次数*/){
	return this->GetStrTxTIndxRepeat(Str, Repeat) + strlen(Str);
}
STR_FUNC_I CharString::GetStrTxTIndxRepeatEx(char* Str, int Repeat = 0/*重复次数*/){
	return this->GetStrTxTIndxRepeat(Str, Repeat) + strlen(Str)+1;
}
STR_FUNC_I CharString::GetStrTxTIndxRepeatEx(const char* Str, int Repeat = 0/*重复次数*/){
	return this->GetStrTxTIndxRepeat(Str, Repeat) + strlen(Str)+1;
}
/*
判断文本是否存在
*/
STR_FUNC_BL CharString::JumpTxTExits(char *Str){
	if (GetStrTxTIndx(Str) == -1){
		return false;
	}
	return true;
}

/*
取一行文本
*/
//取一行文本
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
	for (int i = 0; i <= this->GetStrSize() + 1/*包含\0*/; ++i) {
		if (this->m_str[i] == '\n') {
			++l;
			if (l != LineIndex)
				u = i + 1;//+1跳过\n 这里递增1后面已经忽略0因为已经不是第一行坐标
		}
		if (l == LineIndex) {
			//判断此行多长用于分配内存
			for (j = u;; ++j) {
				if (this->m_str[j] == '\n' || this->m_str[j] == '\0') {
					int size = 0;
					if (u == 0){//防止从0下标导致计算实际长度少1，因为额外的1要用来\0
						size = j + 1;	//+1是因为分配内存不是从0做下标所以需要判断是否为0
					}
					else{
						size = j;
					}
					yun = (char*)malloc(size + 1);	//多分配额外字节,\0
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
获取文本多少行
*/
//获取文本多少行
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
获取文本所在行
*/
//获取文本所在行
STR_FUNC_I CharString::GetTxTLineNum(char *Str){
	if (Str == NULL || this->m_str == NULL){
		return NULL;
	}
	char *str1 = NULL;
	int i = 0;
	int u = this->GetLineNum();
	while (1){//查找这个文本格式在第几行里
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
取三边文本
*/
//取右边文本
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
//取右边文本索引
STR_FUNC_I CharString::GetRightIndex(){
	if (this->m_str == NULL || this->GetStrSize() <= 0){
		return STR_ERROR;
	}
	return this->GetStrSize();
}
//取左边文本
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
//取左边文本有效文本
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
//取中间文本
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
//取中间文本索引号
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
索引到字符截取
*/
//索引到字符截取
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
//两点字符截取
STR_FUNC_CP CharString::CharToCharCutOut(char Str1, char Str2){
	if (Str1 <= 0 || Str2 == 0){
		return NULL;
	}
	int Is = this->GetStrSize();
	int Size = 0;
	for (int i = 0; i <= this->GetStrSize(); ++i){
		if (this->m_str[i] == Str1){
			for (int d = i; d <= this->GetStrSize(); ++d){//计算长度
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
三点文本截取
*/
//三点解析取文本，使用方法：例如文本是 txt:1,2,3,4\r\n 使用方法：AnalysisTxTtoArr(':',',','\r',x) 每次会根据x索引返回'1''2''3'
//不允许三点字符出现重复的字符，索引是检索第几个目标比如<1,2,3><1,2,3> 索引是2的话就检索第二个
STR_FUNC_CP CharString::ThreePoints_AnalysisTxTtoArr(char Str1/*第一个char*/, char Str2/*中间char*/, char Str3/*结尾char*/, int Index/*索引*/){
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
	int uIndex = 0;//索引
	int c_size = 0;//大小从str1开始计算得到双倍字符防止小
	int iis = 0;	//定位上一次str2的坐标 
	int yuno = 0;	//上一个结尾字符
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
			//先看看上一个分隔符是不是一样的
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
//三点解析取文本，获取格式大小获取有多少个模板比如<1,2,3><1,2,3>  就返回2
STR_FUNC_I CharString::ThreePoints_AnalysisGetTxTtoArrNum(char Str1/*第一个char*/, char Str2/*中间char*/, char Str3/*结尾char*/){
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
裁剪文本
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
文本逆序
*/
//文本逆序_后到前
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
//文本逆序_前到后
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
文本替换
*/
STR_FUNC_I CharString::TxTReplace(const char* Str1, const char* Str2){
	if (this->m_str == NULL || Str1 == NULL || Str2 == NULL || this->GetStrSize() <= 0){
		return STR_ERROR;
	}
	int c = this->GetStrTxTIndx(Str1) - 1;
	if (c == STR_ERROR){
		return STR_ERROR;
	}
	this->CutOutTxT(Str1);	//删除
	this->InsertTxT(Str2, c);	//插入
	return STR_CORRECT;
}
//索引文本替换
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
	for (int i = 0; i <= Index - 2/*去掉自身索引*/; ++i){
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
字符尾部正确化
*/
//字符尾部正确化
STR_FUNC_I CharString::CORRECT_STR(){
	if (this->m_str == NULL || this->GetStrSize() <= 0){
		return STR_ERROR;
	}
	this->m_str[this->GetStrSize()] = '\0';
	return STR_CORRECT;
}

/*
格式拆分
*/
STR_FUNC_CP CharString::GetFormatTwo(const char Format, int Str_Index){
	if (this->m_str == NULL || this->GetStrSize() <= 0){
		return STR_ERROR;
	}
	//1是取左边，2是取右边
	if (Str_Index > 2){//若大于2则重置
		Str_Index = 2;
	}
	if (Str_Index < 1){	///1也一样
		Str_Index = 1;
	}
	for (int i = 0; i <= this->GetStrSize() - 1; ++i){
		if (this->m_str[i] == Format){
			//取字符
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
				//取后半部分大小
				for (int k = i+1; this->m_str[k] != '\0'; ++k){
					++c;
				}
				char * str = (char*)malloc(c + 1);
				memset(str, 0, c + 1);
				int u = i+1;//跳过原本的字符
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
判断字符是否存在
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
取指定格式字符
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
	//常规替换处理
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
校验当前字符是否正确
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
取索引文本+长字符
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
判断字符是否大于0
*/
STR_FUNC_BL CharString::Nsize(){
	if (this->GetStrSize() <= 0){
		return true;
	}
	return false;
}

/*
判断字符是否为数字字符
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
获取指定字符串后的数字
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
		if (this->m_str[i] == '.'){//如果是.23之类的浮点表示法默认整数是0
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
		if (this->m_str[i] == '.'){//如果是.23之类的浮点表示法默认整数是0
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
分式裁剪
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
			if (InD != Index){	//如果不等于保留上一次的坐标
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

/*字符变更*/
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

/*运算符*/
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
//%获取行
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
辅助性功能实现
*/
//中英文浮点转换字符转换
STR_FUNC_VOID CharString::FuncTion_CharInToCharAscii(char &Cstr){
	switch (Cstr){
	case '：':
		Cstr = ':';
		break;
	case '，':
		Cstr = ',';
		break;
	case '。':
		Cstr = '.';
		break;
	case '‘':
		Cstr = '\'';
		break;
	case '’':
		Cstr = '\'';
		break;
	case '》':
		Cstr = '>';
		break;
	case '||':
		Cstr = '|';
		break;
	case '《':
		Cstr = '<';
	case '、':
		Cstr = '\\';
	case '？':
		Cstr = '?';
		break;
	default:
		break;
	}
}
