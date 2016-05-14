#include <afx.h>
#include <Winsock2.h>
#include <stdio.h>
#include <iostream>
using namespace std;

int main()
{
	//===========================================加载套接字库 V1.1
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	wVersionRequested = MAKEWORD( 1, 1 );
	err = WSAStartup( wVersionRequested, &wsaData );
	if ( err != 0 ) 
	{
		return 1;
	}
	if ( LOBYTE( wsaData.wVersion ) != 1 ||	HIBYTE( wsaData.wVersion ) != 1 ) 
	{
		WSACleanup( );
		return 1; 
	}
	/* The WinSock DLL is acceptable. Proceed. */
	//===========================================加载套接字库 V1.1

	//===========================================创建 socket
	SOCKET sockClient=socket(AF_INET,SOCK_DGRAM,0);
	// TCP:SOCK_STREAM
	// UDP:SOCK_DGRAM
	//===========================================创建 socket

	//===========================================向服务器端发送数据
	SOCKADDR_IN addrSrv;//注意======这里是服务器的地址信息
	addrSrv.sin_family=AF_INET;
	addrSrv.sin_port=htons(6000);//端口号与服务器端保持一致
	addrSrv.sin_addr.S_un.S_addr=inet_addr("127.0.0.1");//此处表示本机地址

	char sendBuf[100];
	sprintf(sendBuf,"Client send to Server : %s",inet_ntoa(addrSrv.sin_addr));
	sendto(sockClient,sendBuf,strlen(sendBuf)+1,0,(SOCKADDR *)&addrSrv,sizeof(SOCKADDR));
	//===========================================向服务器端发送数据

	//===========================================关闭socket 终止socket库的使用
	closesocket(sockClient);
	WSACleanup();
	//===========================================关闭socket 终止socket库的使用


	return 0;
}