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
	SOCKET sockSrv=socket(AF_INET,SOCK_DGRAM,0);
	// TCP:SOCK_STREAM
	// UDP:SOCK_DGRAM
	//===========================================创建 socket

	//===========================================绑定 socket
	SOCKADDR_IN addrSrv;
	addrSrv.sin_family=AF_INET;
	addrSrv.sin_port=htons(6000);//hton = host to network
	addrSrv.sin_addr.S_un.S_addr=htonl(INADDR_ANY);//hton = host to network	
	
	bind(sockSrv,(SOCKADDR *)&addrSrv,sizeof(SOCKADDR));
	//===========================================绑定 socket


	//===========================================接收客户端数据
	SOCKADDR_IN addrClient;
	int len=sizeof(SOCKADDR_IN);
	char recvBuf[100];

	recvfrom(sockSrv,recvBuf,100,0,(SOCKADDR *)&addrClient,&len);
	printf("Server receive from Client : %s\n",recvBuf);
	//===========================================接收客户端数据

	//===========================================关闭socket 终止socket库的使用
	closesocket(sockSrv);
	WSACleanup();
	//===========================================关闭socket 终止socket库的使用

	return 0;
}