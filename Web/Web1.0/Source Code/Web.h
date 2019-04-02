/*
WEB类
*/
#ifndef _WEB_
#define _WEB_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//头文件
#define _WIN32i_ 0x1234	//此宏用于判断Linux还是Windows
#if(_WIN32i_)//Windows
//使用socket2.2版本
#include <winsock2.h>  
#pragma comment(lib,"ws2_32.lib") 
#else//Linux
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>	//getcomname
#endif
//类型别名
typedef int WEB_SOCKET;
typedef int WEB_FUNC_I;
typedef void WEB_FUNC_V;
typedef char* WEB_FUNC_CP;
//宏定义
#define WEB_UDP 0	//udp连接
#define WEB_TCP 1	//tcp连接
//ip duan
#define WEB_IP4 0	//ip4
#define WEB_IP6 1	//ip6
#define WEB_IPUNIX 2	//unxi段
#define WEB_NOT 3	//不指定
//er
#define WEB_ERROR 0
#define WEB_SUCCESS 1
//连接类型
#define WEB_SOCKTYPE_RELIABLE	0	//可靠连接字节流
#define WEB_SOCKTYPE_NORELIABLE 1	//不可靠连接字节流
#define WEB_SOCKTYPE_IP 2	//ip协议连接字节流
#define WEB_SOCKTYPE_MESSAGE 3	//固定长度，报文连接
//ip类型
#define WEB_IP_THIS 0	//使用回访地址
//默认接收窗口缓冲区大小
#define WEB_WINDOW_SIZE 1024
//默认发送窗口缓冲区大小
#define WEB_SEND_WINDOW_SIZE 1024
//使用默认缓冲区
#define WEB_RECV_WINDOW 0
//默认监听队列大小
#define WEB_LISTEN_SIZE 5
//默认发送数据
#define WEB_SEND_DATA 0
//默认动态分配内存值
#define WEB_MALLOC_SIZE 256
//导出
#define STR_CLASS_DLL_PORT _declspec(dllexport) //导出接口
class STR_CLASS_DLL_PORT Web{
public:
	Web();
	Web(int Len);
	~Web();
	//创建Socket
	WEB_FUNC_I CreateSocket(const char* Ip, int Post, int CometType = WEB_TCP, int IPParage = WEB_IP4, int SockType = WEB_SOCKTYPE_RELIABLE);
	//动态修改接收窗口缓冲区大小
	WEB_FUNC_I SetRecvWindowSize(int Size);
	//动态修改发送窗口缓冲区大小
	WEB_FUNC_I SetSendWindowSize(int Size);
	//接收数据，阻塞函数
	WEB_FUNC_I RecvData(int RecvSize = WEB_RECV_WINDOW);
	//接收数据，最近一次的接收连接
	WEB_FUNC_I RecvNowData(int RecvSize = WEB_RECV_WINDOW);
	//获取发送缓冲区数据
	WEB_FUNC_CP GetSendData();
	//获取接收缓冲区数据
	WEB_FUNC_CP GetRecvData();
	//设置发送缓冲区内容
	WEB_FUNC_I SetSendData(char* Data);
	//设置接收缓冲区内容
	WEB_FUNC_I SetRecvData(char* Data);
	//返回最近一次正在连接的ip
	WEB_FUNC_I BackData(const char* Data);
	//发送数据,阻塞函数
	WEB_FUNC_I SendData(const char* Ip, int Port, const char* Data = WEB_SEND_DATA, int CometType = WEB_TCP, int IPParage = WEB_IP4, int SockType = WEB_SOCKTYPE_RELIABLE);
	//关闭最近一次连接句柄
	WEB_FUNC_I Close();
	//获取Socket
	WEB_SOCKET GetSocketHwnd();
	//获取最近一次的连接句柄
	WEB_SOCKET GetNowAcceptSock();
	//设置当前socket句柄
	WEB_FUNC_V SetSocketHwnd(WEB_SOCKET Sock);
	//设置当前连接句柄
	WEB_FUNC_V SetNowAcceptSock(WEB_SOCKET AcceptSock);
	//释放Socket
	WEB_FUNC_V Relete();
	//post提交
	WEB_FUNC_CP Post(char* ComName, const char* Data, bool Hand = false, int Port = 80, bool HttpEdition1_1 = true);
	//get提交
	WEB_FUNC_CP Get(char* ComName, bool Hand = false, int Port = 80, bool HttpEdition1_1 = true);
private:
	WEB_SOCKET Web_Socket;	//sock
	WEB_SOCKET Web_AcceptSock;	//连接sock
	char* Data;
	int Window_Size;
	char* Send_Data;
	int Send_Window_Size;
	void DeleteStr(char* DeleteStr, const char* Str);
	
};

#endif //--_WEB_