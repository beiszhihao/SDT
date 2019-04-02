/*
WEB��
*/
#ifndef _WEB_
#define _WEB_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//ͷ�ļ�
#define _WIN32i_ 0x1234	//�˺������ж�Linux����Windows
#if(_WIN32i_)//Windows
//ʹ��socket2.2�汾
#include <winsock2.h>  
#pragma comment(lib,"ws2_32.lib") 
#else//Linux
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>	//getcomname
#endif
//���ͱ���
typedef int WEB_SOCKET;
typedef int WEB_FUNC_I;
typedef void WEB_FUNC_V;
typedef char* WEB_FUNC_CP;
//�궨��
#define WEB_UDP 0	//udp����
#define WEB_TCP 1	//tcp����
//ip duan
#define WEB_IP4 0	//ip4
#define WEB_IP6 1	//ip6
#define WEB_IPUNIX 2	//unxi��
#define WEB_NOT 3	//��ָ��
//er
#define WEB_ERROR 0
#define WEB_SUCCESS 1
//��������
#define WEB_SOCKTYPE_RELIABLE	0	//�ɿ������ֽ���
#define WEB_SOCKTYPE_NORELIABLE 1	//���ɿ������ֽ���
#define WEB_SOCKTYPE_IP 2	//ipЭ�������ֽ���
#define WEB_SOCKTYPE_MESSAGE 3	//�̶����ȣ���������
//ip����
#define WEB_IP_THIS 0	//ʹ�ûطõ�ַ
//Ĭ�Ͻ��մ��ڻ�������С
#define WEB_WINDOW_SIZE 1024
//Ĭ�Ϸ��ʹ��ڻ�������С
#define WEB_SEND_WINDOW_SIZE 1024
//ʹ��Ĭ�ϻ�����
#define WEB_RECV_WINDOW 0
//Ĭ�ϼ������д�С
#define WEB_LISTEN_SIZE 5
//Ĭ�Ϸ�������
#define WEB_SEND_DATA 0
//Ĭ�϶�̬�����ڴ�ֵ
#define WEB_MALLOC_SIZE 256
//����
#define STR_CLASS_DLL_PORT _declspec(dllexport) //�����ӿ�
class STR_CLASS_DLL_PORT Web{
public:
	Web();
	Web(int Len);
	~Web();
	//����Socket
	WEB_FUNC_I CreateSocket(const char* Ip, int Post, int CometType = WEB_TCP, int IPParage = WEB_IP4, int SockType = WEB_SOCKTYPE_RELIABLE);
	//��̬�޸Ľ��մ��ڻ�������С
	WEB_FUNC_I SetRecvWindowSize(int Size);
	//��̬�޸ķ��ʹ��ڻ�������С
	WEB_FUNC_I SetSendWindowSize(int Size);
	//�������ݣ���������
	WEB_FUNC_I RecvData(int RecvSize = WEB_RECV_WINDOW);
	//�������ݣ����һ�εĽ�������
	WEB_FUNC_I RecvNowData(int RecvSize = WEB_RECV_WINDOW);
	//��ȡ���ͻ���������
	WEB_FUNC_CP GetSendData();
	//��ȡ���ջ���������
	WEB_FUNC_CP GetRecvData();
	//���÷��ͻ���������
	WEB_FUNC_I SetSendData(char* Data);
	//���ý��ջ���������
	WEB_FUNC_I SetRecvData(char* Data);
	//�������һ���������ӵ�ip
	WEB_FUNC_I BackData(const char* Data);
	//��������,��������
	WEB_FUNC_I SendData(const char* Ip, int Port, const char* Data = WEB_SEND_DATA, int CometType = WEB_TCP, int IPParage = WEB_IP4, int SockType = WEB_SOCKTYPE_RELIABLE);
	//�ر����һ�����Ӿ��
	WEB_FUNC_I Close();
	//��ȡSocket
	WEB_SOCKET GetSocketHwnd();
	//��ȡ���һ�ε����Ӿ��
	WEB_SOCKET GetNowAcceptSock();
	//���õ�ǰsocket���
	WEB_FUNC_V SetSocketHwnd(WEB_SOCKET Sock);
	//���õ�ǰ���Ӿ��
	WEB_FUNC_V SetNowAcceptSock(WEB_SOCKET AcceptSock);
	//�ͷ�Socket
	WEB_FUNC_V Relete();
	//post�ύ
	WEB_FUNC_CP Post(char* ComName, const char* Data, bool Hand = false, int Port = 80, bool HttpEdition1_1 = true);
	//get�ύ
	WEB_FUNC_CP Get(char* ComName, bool Hand = false, int Port = 80, bool HttpEdition1_1 = true);
private:
	WEB_SOCKET Web_Socket;	//sock
	WEB_SOCKET Web_AcceptSock;	//����sock
	char* Data;
	int Window_Size;
	char* Send_Data;
	int Send_Window_Size;
	void DeleteStr(char* DeleteStr, const char* Str);
	
};

#endif //--_WEB_