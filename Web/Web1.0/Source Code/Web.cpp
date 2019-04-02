#include "Web.h"
//构造析构
Web::Web():Data(NULL){
#if(_WIN32i_)
		//初始化WSA  
		WORD sockVersion = MAKEWORD(2, 2);
		WSADATA wsaData;
		if (WSAStartup(sockVersion, &wsaData) != 0)
		{
			this->Web_Socket = 99;
			return;
		}
#endif
		this->Web_Socket = 0;
		this->Data = (char*)malloc(WEB_WINDOW_SIZE + 1);
		memset(this->Data, 0, WEB_WINDOW_SIZE + 1);
		this->Window_Size = WEB_WINDOW_SIZE;
		//send
		this->Send_Data = (char*)malloc(WEB_SEND_WINDOW_SIZE + 1);
		memset(this->Send_Data, 0, WEB_SEND_WINDOW_SIZE + 1);
		this->Send_Window_Size = WEB_SEND_WINDOW_SIZE;
	}
Web::Web(int Len){
#if(_WIN32i_)
	//初始化WSA  
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA wsaData;
	if (WSAStartup(sockVersion, &wsaData) != 0)
	{
		this->Web_Socket = 99;
		return;
	}
#endif
	this->Web_Socket = 0;
	this->Data = (char*)malloc(Len + 1);
	memset(this->Data, 0, Len + 1);
	this->Window_Size = Len;
	//send
	this->Send_Data = (char*)malloc(Len + 1);
	memset(this->Send_Data, 0, Len + 1);
	this->Send_Window_Size = Len + 1;
}
Web::~Web(){
	this->Relete();
}
//创建Socket
WEB_FUNC_I Web::CreateSocket(const char* Ip, int Post, int CometType, int IPParage, int SockType){
	if (Post <= 0){
		return WEB_ERROR;
	}
	//设置连接方式
	int IPPTYPE = 0;//默认tcp
	switch (CometType){
	case WEB_TCP:
#if(_WIN32i_)
		IPPTYPE = IPPROTO_TCP;
#endif
		break;
	case WEB_UDP:
#if(_WIN32i_)
		IPPTYPE = IPPROTO_UDP;
		break;
#endif
		IPPTYPE = 1;
		break;
	default://若都没有指定则使用TCP
#if(_WIN32i_)
		IPPTYPE = IPPROTO_TCP;
		break;
#endif
		IPPTYPE = 0;
		break;
	}
	//设置连接协议
	int Iarge = 0;
	switch (IPParage){
	case WEB_IP4:
		Iarge = AF_INET;
		break;
	case WEB_IP6:
		Iarge = AF_INET6;
		break;
	case WEB_NOT:
		Iarge = AF_UNSPEC;
		break;
	case WEB_IPUNIX:
		Iarge = AF_UNIX;
		break;
	default:	//默认使用ip4
		Iarge = AF_INET;
		break;
	}
	//设置连接类型
	int Cole = 0;
	switch (SockType){
	case WEB_SOCKTYPE_RELIABLE:
		Cole = SOCK_STREAM;
		break;
	case WEB_SOCKTYPE_NORELIABLE:
		Cole = SOCK_DGRAM;
		break;
	case WEB_SOCKTYPE_IP:
		Cole = SOCK_RAW;
		break;
	case WEB_SOCKTYPE_MESSAGE:
		Cole = SOCK_SEQPACKET;
		break;
	default:	//默认使用可靠的字节流连接
		Cole = SOCK_STREAM;
		break;
	}
	//创建一个套接字
	this->Web_Socket = socket(Iarge, Cole, IPPTYPE);
	if (Web_Socket <= 0)
	{
		return WEB_ERROR;
	}
	struct sockaddr_in saddr;
	//初始化服务器套接字数据结构
	saddr.sin_family = Iarge;
	saddr.sin_port = htons(Post);
	if (Ip == WEB_IP_THIS){
		saddr.sin_addr.s_addr = htonl(INADDR_ANY);	//回访地址 127.0.0.1 转化为网络字节序
	}
	else{
		saddr.sin_addr.s_addr = inet_addr(Ip);
	}
	if (bind(Web_Socket, (LPSOCKADDR)&saddr, sizeof(saddr)) == SOCKET_ERROR){
		return WEB_ERROR;
	}
	return WEB_SUCCESS;

}
//动态修改接收窗口缓冲区大小
WEB_FUNC_I Web::SetRecvWindowSize(int Size){
	if (this->Data != NULL){
		free(Data);
		Data = NULL;
	}
	if (Size <= 0){
		return WEB_ERROR;
	}
	this->Window_Size = 0;
	this->Data = (char*)malloc(Size + 1);
	memset(this->Data, 0, Size + 1);
	this->Window_Size = Size;
}
//动态修改发送窗口缓冲区大小
WEB_FUNC_I Web::SetSendWindowSize(int Size){
	if (this->Send_Data != NULL){
		free(this->Send_Data);
		this->Send_Data = NULL;
	}
	if (Size <= 0){
		return WEB_ERROR;
	}
	this->Send_Window_Size = 0;
	this->Send_Data = (char*)malloc(Size + 1);
	memset(this->Send_Data, 0, Size + 1);
	this->Send_Window_Size = Size;
}
//接收数据，阻塞函数
WEB_FUNC_I Web::RecvData(int RecvSize){
		if (this->Web_Socket == 0){
			return WEB_ERROR;
		}
		if (this->Data == NULL || this->Window_Size <= 0){
			return WEB_ERROR;
		}
		int RecvSizeor = 0;
		if (RecvSize == WEB_RECV_WINDOW){
			RecvSizeor = this->Window_Size;
		}
		memset(this->Data, 0, this->Window_Size + 1);
		//开始监听  
		if (listen(this->Web_Socket, WEB_LISTEN_SIZE) == -1)
		{
			return WEB_ERROR;
		}
		this->Web_AcceptSock = accept(this->Web_Socket, NULL, NULL);
		if (this->Web_AcceptSock == NULL)
		{
			return WEB_ERROR;
		}
		int ret = recv(this->Web_Socket, this->Data, RecvSizeor, 0);
		if (ret <= 0){
			return WEB_ERROR;
		}
		return WEB_SUCCESS;
	}
//接收数据，最近一次的接收连接
WEB_FUNC_I Web::RecvNowData(int RecvSize){
	if (this->Web_Socket == 0){
		return WEB_ERROR;
	}
	if (this->Data == NULL || this->Window_Size <= 0){
		return WEB_ERROR;
	}
	int RecvSizeor = 0;
	if (RecvSize == WEB_RECV_WINDOW){
		RecvSizeor = this->Window_Size;
	}
	memset(this->Data, 0, this->Window_Size + 1);
	//开始监听  
	if (listen(this->Web_Socket, WEB_LISTEN_SIZE) == -1)
	{
		return WEB_ERROR;
	}
	this->Web_AcceptSock = accept(this->Web_Socket, NULL, NULL);
	if (this->Web_AcceptSock == NULL)
	{
		return WEB_ERROR;
	}
	int ret = recv(this->Web_AcceptSock, this->Data, RecvSizeor, 0);
	if (ret <= 0){
		return WEB_ERROR;
	}
	return WEB_SUCCESS;
}
//获取发送缓冲区数据
WEB_FUNC_CP Web::GetSendData(){
	if (this->Send_Data != NULL){
		return this->Send_Data;
	}
	return WEB_ERROR;
}
//获取接收缓冲区数据
WEB_FUNC_CP Web::GetRecvData(){
	if (this->Data != NULL){
		return this->Data;
	}
	return WEB_ERROR;
}
//设置发送缓冲区内容
WEB_FUNC_I Web::SetSendData(char* Data){
	if (strlen(this->Send_Data) < strlen(Data)){
		return WEB_ERROR;
	}
	strcpy(this->Send_Data, Data);
	return WEB_SUCCESS;
}
//设置接收缓冲区内容
WEB_FUNC_I Web::SetRecvData(char* Data){
	if (strlen(this->Data) < strlen(Data)){
		return WEB_ERROR;
	}
	strcpy(this->Data, Data);
	return WEB_SUCCESS;
}
//返回最近一次正在连接的ip
WEB_FUNC_I Web::BackData(const char* Data){
	if (Data == NULL){
		return WEB_ERROR;
	}
	if (this->Web_AcceptSock == NULL){
		return WEB_ERROR;
	}
	send(this->Web_AcceptSock, Data, strlen(Data), 0);
	return WEB_SUCCESS;
}
//发送数据,阻塞函数
WEB_FUNC_I Web::SendData(const char* Ip, int Port, const char* Data, int CometType, int IPParage, int SockType){
	if (Port <= 0){
		return WEB_ERROR;
	}
	//设置连接方式
	int IPPTYPE = 0;//默认tcp
	switch (CometType){
	case WEB_TCP:
#if(_WIN32i_)
		IPPTYPE = IPPROTO_TCP;
#endif
		break;
	case WEB_UDP:
#if(_WIN32i_)
		IPPTYPE = IPPROTO_UDP;
		break;
#endif
		IPPTYPE = 1;
		break;
	default://若都没有指定则使用TCP
#if(_WIN32i_)
		IPPTYPE = IPPROTO_TCP;
		break;
#endif
		IPPTYPE = 0;
		break;
	}
	//设置连接协议
	int Iarge = 0;
	switch (IPParage){
	case WEB_IP4:
		Iarge = AF_INET;
		break;
	case WEB_IP6:
		Iarge = AF_INET6;
		break;
	case WEB_NOT:
		Iarge = AF_UNSPEC;
		break;
	case WEB_IPUNIX:
		Iarge = AF_UNIX;
		break;
	default:	//默认使用ip4
		Iarge = AF_INET;
		break;
	}
	//设置连接类型
	int Cole = 0;
	switch (SockType){
	case WEB_SOCKTYPE_RELIABLE:
		Cole = SOCK_STREAM;
		break;
	case WEB_SOCKTYPE_NORELIABLE:
		Cole = SOCK_DGRAM;
		break;
	case WEB_SOCKTYPE_IP:
		Cole = SOCK_RAW;
		break;
	case WEB_SOCKTYPE_MESSAGE:
		Cole = SOCK_SEQPACKET;
		break;
	default:	//默认使用可靠的字节流连接
		Cole = SOCK_STREAM;
		break;
	}
	int sockfd = socket(Iarge, Cole, IPPTYPE);
	struct sockaddr_in saddr;
	//初始化服务器套接字数据结构
	saddr.sin_family = Iarge;
	saddr.sin_port = htons(Port);
	if (Ip == WEB_IP_THIS){
		saddr.sin_addr.s_addr = htonl(INADDR_ANY);	//回访地址 127.0.0.1 转化为网络字节序
	}
	else{
		saddr.sin_addr.s_addr = inet_addr(Ip);
	}
	if (this->Send_Data == NULL){
		return WEB_ERROR;
	}
	if (this->Send_Window_Size <= 0){
		return WEB_ERROR;
	}
	if (connect(sockfd, (struct sockaddr*)&saddr, sizeof(saddr))<0)
	{
		return WEB_ERROR;
	}
	char* str;
	if (Data == WEB_SEND_DATA){
		if (this->Send_Data == NULL){
			return WEB_ERROR;
		}
		if (send(sockfd, this->Send_Data, this->Send_Window_Size, 0) < 0){
			return WEB_ERROR;
		}
		return WEB_SUCCESS;
	}
	if (this->Send_Data != NULL){
		free(this->Send_Data);
		this->Send_Data == NULL;
	}
	this->Send_Data = (char*)malloc(strlen(Data) + 1);
	if (this->Send_Data == NULL){
		return WEB_ERROR;
	}
	this->Send_Window_Size = strlen(Data) + 1;
	memset(this->Send_Data, 0, this->Send_Window_Size);
	strcpy(this->Send_Data, Data);
	if (send(sockfd, this->Send_Data,this->Send_Window_Size, 0) < 0){
		return WEB_ERROR;
	}
	this->Web_AcceptSock = sockfd;
	return WEB_SUCCESS;
}
//关闭最近一次连接句柄
WEB_FUNC_I Web::Close(){
	if (this->Web_AcceptSock != NULL){
		return WEB_ERROR;
	}
#if(_WIN32i_)
	closesocket(this->Web_AcceptSock);
#else
	close(this->Web_AcceptSock);
#endif
	return WEB_SUCCESS;
}
//获取Socket
WEB_SOCKET Web::GetSocketHwnd(){
	return this->Web_Socket;
}
//获取最近一次的连接句柄
WEB_SOCKET Web::GetNowAcceptSock(){
	return this->Web_AcceptSock;
}
//设置当前socket句柄
WEB_FUNC_V Web::SetSocketHwnd(WEB_SOCKET Sock){
	this->Web_Socket = Sock;
}
//设置当前连接句柄
WEB_FUNC_V Web::SetNowAcceptSock(WEB_SOCKET AcceptSock){
	this->Web_AcceptSock = AcceptSock;
}
//释放Socket
WEB_FUNC_V Web::Relete(){
	if (this->Web_Socket != 0){
#if(_WIN32i_)
		closesocket(this->Web_Socket);
#else
		close(this->Web_Socket);
#endif

	}
	if (this->Data != NULL){
		free(this->Data);
		this->Data = NULL;
	}
	this->Window_Size = 0;
}
//post提交
WEB_FUNC_CP Web::Post(char* ComName, const char* Data, bool Hand, int Port, bool HttpEdition1_1){
	if (ComName == NULL){
		return WEB_ERROR;
	}
	if (Data == NULL){
		return WEB_ERROR;
	}
	//windows
	unsigned long IPUL = 0;
	char *IP = NULL;
	//linux
	struct hostent *he;
	char destIP[128] = { 0 };
	//char **phe = NULL;
	bool Win = false;
	//去掉请求页面
	DeleteStr(ComName, "http://");
	int forsize = 0;
	for (int i = 0; i <= strlen(ComName) - 1; ++i){
		forsize++;
	}
	char* Ipname = (char*)malloc(forsize + 1);
	if (Ipname == NULL){
		return WEB_ERROR;
	}
	memset(Ipname, 0, forsize + 1);
	for (int i = 0; i <= strlen(ComName) - 1; ++i){
		if (ComName[i] == '/'){
			break;
		}
		Ipname[i] = ComName[i];
	}
#if(_WIN32i_)
	hostent *phst = gethostbyname(Ipname);//传递域名/主机名

	in_addr * iddr = (in_addr*)phst->h_addr;//h_addr = h_addr_list[0],获取地址列表第一个地址IP

	IPUL = iddr->s_addr;//获取无符号的网络字节序，该符号通常以大端形式存储

	IP = inet_ntoa(*iddr);//将十进制的大端存储的网络字节讯转化为以.分割的字符IP_4地址，并以小端形式存储
	Win = true;
#else
	//	for (phe = he->h_addr_list; NULL != *phe; ++phe){
	he = gethostbyname(Ipname);
	inet_ntop(he->h_addrtype, *phe, destIP, sizeof(destIP));
	//	printf("%s\n", destIP);
	//	}
#endif
	//组合报文
	char HttpHand[1024] = { 0 };
	int Fuhao = 0;
	int FuhaoSize = 0;
	bool qingqiu = false;
	//获取请求头
	for (int i = strlen(ComName) - 1; i != 0; --i){
		++FuhaoSize;
		if (ComName[i] == '/'){
			Fuhao = i;
			qingqiu = true;
		}
	}
	char *Str = (char*)malloc(FuhaoSize + 1);
	if (Str == NULL){
		return WEB_ERROR;
	}
	memset(Str, 0, FuhaoSize + 1);
	if (qingqiu){
		int j = 0;
		for (int i = Fuhao; i <= FuhaoSize + Fuhao; ++i){
			Str[j++] = ComName[i];
		}
	}
	strcat(HttpHand, "POST");
	strcat(HttpHand, " ");
	strcat(HttpHand, Str);
	strcat(HttpHand, " ");
	if (HttpEdition1_1){
		strcat(HttpHand, "HTTP/1.1\r\n");
	}
	else{
		strcat(HttpHand, "HTTP/1.0\r\n");
	}
	strcat(HttpHand, "Accept: */*\r\n");
	strcat(HttpHand, "Referer: ");
	strcat(HttpHand, ComName);
	strcat(HttpHand, "\r\n");
	strcat(HttpHand, "Accept-Language: zh-cn\r\n");
	strcat(HttpHand, "Host: ");
	strcat(HttpHand, Ipname);
	strcat(HttpHand, "\r\n");
	strcat(HttpHand, "Cache - Control: no - cache\r\n");
	strcat(HttpHand, "Content - Type: application / x - www - form - urlencoded\r\n");
	strcat(HttpHand, "\r\n");
	//报文
	strcat(HttpHand, Data);
	strcat(HttpHand, "\r\n");
	if (Win == true){
		//如果发送成功，则返回发送成功的字节数
		if (SendData(IP, Port, HttpHand) == WEB_ERROR)
		{
			return WEB_ERROR;
		}
	}
	else{
		if (WEB_ERROR == SendData(destIP, Port, HttpHand)){
			return WEB_ERROR;
		}
	}
	char buffer[2] = { 0 };
	memset(buffer, '\0', sizeof(buffer));
	int l = 0;
	//读取响应头
	char pre1 = 0;
	char pre2 = 0;
	char pre3 = 0;
	char pre4 = 0;
	char GetHandData[1024] = { 0 };
	int size = WEB_MALLOC_SIZE;
	char* HandData = (char*)malloc(size);
	while (true){
		/*
		每次对buffer解引用都会获取首字节的字符，当pre1指向2和1指向3，这是后递增的
		比如有一个字符 hello word
		最开始pre123都是0
		所以一开始，pre1= pre2 为0
		pre2 = pre3 为0
		ore3 =buffer 为h
		当第二次循环时
		pre1 = pre2 依旧为0
		pre2 = pre3 为h
		pre3 = buffer 为 e
		那么当第三次循环时
		pre1 = pre2 为 h
		pre2 = pre3 为e
		pre 为 l
		这样的方式就可以在每次读取一个字节的情况下同时保存前两个字节的方法，这样就可以判断前两个字节是否为\r\n
		这些都是保存的旧值
		*/
		pre1 = pre2;
		pre2 = pre3;
		pre3 = *buffer;
		l = recv(Web_AcceptSock, buffer, 1, 0);
		pre4 = *buffer;	//保存新值
		strcat(GetHandData, buffer);
		if ((pre1 == '\r'&&pre2 == '\n'&& pre3 == '\r' && pre4 == '\n') || l <= 0){
			break;
		}
	}
	if (HandData == NULL){
		return WEB_ERROR;
	}
	memset(HandData, 0, size);
	char bu[2] = { 0 };
	int uy = 0;
	while (true){
		l = recv(Web_AcceptSock, bu, 1, 0);
		if (l <= 0){
			break;
		}
		strcat(HandData, bu);
		++uy;
		if (uy == size - 1){
			size = size + WEB_MALLOC_SIZE;
			char* str = (char*)malloc(size);
			if (str == NULL){
				return WEB_ERROR;
			}
			memset(str, 0, size);
			strcpy(str, HandData);
			free(HandData);
			HandData = NULL;
			HandData = (char*)malloc(size);
			if (HandData == NULL){
				return WEB_ERROR;
			}
			memset(HandData, 0, size);
			strcpy(HandData, str);
			free(str);
			str = NULL;
		}
	}
	//写到接收缓冲区里
	if (this->Data != NULL){
		free(this->Data);
		this->Data = NULL;
	}
	this->Data = (char*)malloc(size + (strlen(GetHandData) + 1));
	if (this->Data == NULL){
		return WEB_ERROR;
	}
	memset(this->Data, 0, size + (strlen(GetHandData) + 1));
	strcpy(this->Data, GetHandData);
	strcat(this->Data, HandData);
	if (Hand){
		return GetHandData;
	}
	return HandData;

}
//get提交
WEB_FUNC_CP Web::Get(char* ComName, bool Hand, int Port, bool HttpEdition1_1){
	if (ComName == NULL){
		return WEB_ERROR;
	}
	//windows
	unsigned long IPUL = 0;
	char *IP = NULL;
	//linux
	struct hostent *he;
	char destIP[128] = { 0 };
	//char **phe = NULL;
	bool Win = false;
	//去掉请求页面
	DeleteStr(ComName, "http://");
	int forsize = 0;
	for (int i = 0; i <= strlen(ComName) - 1; ++i){
		forsize++;
	}
	char* Ipname = (char*)malloc(forsize + 1);
	if (Ipname == NULL){
		return WEB_ERROR;
	}
	memset(Ipname, 0, forsize + 1);
	for (int i = 0; i <= strlen(ComName) - 1; ++i){
		if (ComName[i] == '/'){
			break;
		}
		Ipname[i] = ComName[i];
	}

#if(_WIN32i_)
	hostent *phst = gethostbyname(Ipname);//传递域名/主机名

	in_addr * iddr = (in_addr*)phst->h_addr;//h_addr = h_addr_list[0],获取地址列表第一个地址IP

	IPUL = iddr->s_addr;//获取无符号的网络字节序，该符号通常以大端形式存储

	IP = inet_ntoa(*iddr);//将十进制的大端存储的网络字节讯转化为以.分割的字符IP_4地址，并以小端形式存储
	Win = true;
#else
	//	for (phe = he->h_addr_list; NULL != *phe; ++phe){
	he = gethostbyname(Ipname);
	inet_ntop(he->h_addrtype, *phe, destIP, sizeof(destIP));
	//	printf("%s\n", destIP);
	//	}
#endif
	//组合报文
	char HttpHand[1024] = { 0 };
	int Fuhao = 0;
	int FuhaoSize = 0;
	bool qingqiu = false;
	//获取请求头
	for (int i = strlen(ComName) - 1; i != 0; --i){
		++FuhaoSize;
		if (ComName[i] == '/'){
			Fuhao = i;
			qingqiu = true;
		}
	}
	char *Str = (char*)malloc(FuhaoSize + 1);
	if (Str == NULL){
		return WEB_ERROR;
	}
	memset(Str, 0, FuhaoSize + 1);
	if (qingqiu){
		int j = 0;
		for (int i = Fuhao; i <= FuhaoSize + Fuhao; ++i){
			Str[j++] = ComName[i];
		}
	}
	strcat(HttpHand, "GET");
	strcat(HttpHand, " ");
	strcat(HttpHand, Str);
	strcat(HttpHand, " ");
	if (HttpEdition1_1){
		strcat(HttpHand, "HTTP/1.1\r\n");
	}
	else{
		strcat(HttpHand, "HTTP/1.0\r\n");
	}
	strcat(HttpHand, "Accept: */*\r\n");
	strcat(HttpHand, "Referer: ");
	strcat(HttpHand, ComName);
	strcat(HttpHand, "\r\n");
	strcat(HttpHand, "Accept-Language: zh-cn\r\n");
	strcat(HttpHand, "Host: ");
	strcat(HttpHand, Ipname);
	strcat(HttpHand, "\r\n");
	strcat(HttpHand, "Cache - Control: no - cache\r\n");
	strcat(HttpHand, "Content - Type: application / x - www - form - urlencoded\r\n");
	strcat(HttpHand, "\r\n");
	//报文
	strcat(HttpHand, " ");
	strcat(HttpHand, "\r\n");
	if (Win == true){
		//如果发送成功，则返回发送成功的字节数
		if (SendData(IP, Port, HttpHand) == WEB_ERROR)
		{
			return WEB_ERROR;
		}
	}
	else{
		if (WEB_ERROR == SendData(destIP, Port, HttpHand)){
			return WEB_ERROR;
		}
	}
	char buffer[2] = { 0 };
	memset(buffer, '\0', sizeof(buffer));
	int l = 0;
	//读取响应头
	char pre1 = 0;
	char pre2 = 0;
	char pre3 = 0;
	char pre4 = 0;
	char GetHandData[1024] = { 0 };
	int size = WEB_MALLOC_SIZE;
	char* HandData = (char*)malloc(size);
	while (true){
		/*
		每次对buffer解引用都会获取首字节的字符，当pre1指向2和1指向3，这是后递增的
		比如有一个字符 hello word
		最开始pre123都是0
		所以一开始，pre1= pre2 为0
		pre2 = pre3 为0
		ore3 =buffer 为h
		当第二次循环时
		pre1 = pre2 依旧为0
		pre2 = pre3 为h
		pre3 = buffer 为 e
		那么当第三次循环时
		pre1 = pre2 为 h
		pre2 = pre3 为e
		pre 为 l
		这样的方式就可以在每次读取一个字节的情况下同时保存前两个字节的方法，这样就可以判断前两个字节是否为\r\n
		这些都是保存的旧值
		*/
		pre1 = pre2;
		pre2 = pre3;
		pre3 = *buffer;
		l = recv(Web_AcceptSock, buffer, 1, 0);
		pre4 = *buffer;	//保存新值
		strcat(GetHandData, buffer);
		if ((pre1 == '\r'&&pre2 == '\n'&& pre3 == '\r' && pre4 == '\n') || l <= 0){
			break;
		}
	}
	if (HandData == NULL){
		return WEB_ERROR;
	}
	memset(HandData, 0, size);
	char bu[2] = { 0 };
	int uy = 0;
	while (true){
		l = recv(Web_AcceptSock, bu, 1, 0);
		if (l <= 0){
			break;
		}
		strcat(HandData, bu);
		++uy;
		if (uy == size - 1){
			size = size + WEB_MALLOC_SIZE;
			char* str = (char*)malloc(size);
			if (str == NULL){
				return WEB_ERROR;
			}
			memset(str, 0, size);
			strcpy(str, HandData);
			free(HandData);
			HandData = NULL;
			HandData = (char*)malloc(size);
			if (HandData == NULL){
				return WEB_ERROR;
			}
			memset(HandData, 0, size);
			strcpy(HandData, str);
			free(str);
			str = NULL;
		}
	}
	//写到接收缓冲区里
	if (this->Data != NULL){
		free(this->Data);
		this->Data = NULL;
	}
	this->Data = (char*)malloc(size + (strlen(GetHandData) + 1));
	if (this->Data == NULL){
		return WEB_ERROR;
	}
	memset(this->Data, 0, size + (strlen(GetHandData) + 1));
	strcpy(this->Data, GetHandData);
	strcat(this->Data, HandData);
	if (Hand){
		return GetHandData;
	}
	return HandData;

}


void Web::DeleteStr(char* DeleteStr, const char* Str){
	int yun = 0;
	int yIndex = 0;
	int you = (strlen(DeleteStr) - strlen(Str)) + 1;
	char *m_u = (char*)malloc(you);
	if (m_u == NULL){
		return;
	}
	memset(m_u, 0, (strlen(DeleteStr) - strlen(Str)) + 1);
	for (int i = 0; i <= strlen(DeleteStr); ++i){
		yun = i;
		for (int j = 0; j <= strlen(Str) - 1; ++j, ++yun){
			if (Str[j] != DeleteStr[yun]){
				break;
			}
			if (j == strlen(Str) - 1){
				for (int u = 0; u <= i - 1; ++u){
					m_u[u] = DeleteStr[u];
				}
				int c = i + strlen(Str);
				for (int u = i; u <= strlen(DeleteStr) - 2; ++u, ++c){
					m_u[u] = DeleteStr[c];
				}
				free(DeleteStr);
				DeleteStr = NULL;
				DeleteStr = (char*)malloc(you);
				if (DeleteStr == NULL){
					return;
				}
				memset(DeleteStr, 0, you);
				strcpy(DeleteStr, m_u);
				free(m_u);
				m_u = NULL;
				return;

			}
		}
	}
}
