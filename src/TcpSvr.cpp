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
	SOCKET sockSrv=socket(AF_INET,SOCK_STREAM,0);
	// TCP:SOCK_STREAM
	// UDP:SOCK_DGRAM
	//===========================================创建 socket

	//===========================================绑定 socket
	SOCKADDR_IN addrSrv;
	addrSrv.sin_family=AF_INET;
	addrSrv.sin_port=htons(6000);//hton = host to network
	addrSrv.sin_addr.S_un.S_addr=htonl(INADDR_ANY);//hton = host to network	
	//The htonl function converts a u_long from host to TCP/IP network byte order (which is big endian)
	//The htons function converts a u_short from host to TCP/IP network byte order (which is big-endian)

	bind(sockSrv,(SOCKADDR *)&addrSrv,sizeof(SOCKADDR));
	//===========================================绑定 socket

	//===========================================监听 socket
	listen(sockSrv,SOMAXCONN);
	//===========================================监听 socket

	//===========================================等待客户端请求 与客户端通信
	SOCKADDR_IN addrClient;
	int len=sizeof(SOCKADDR_IN);

	while(1)
	{
		SOCKET sockConn=accept(sockSrv,(SOCKADDR *)&addrClient,&len);
		//此处返回新连接的socket用于和客户端通信
		//先前的socket仍用于监听客户端的连接请求

		//发送信息
		char sendBuf[100];
		sprintf(sendBuf,"Server send to Client : %s",inet_ntoa(addrClient.sin_addr));
		send(sockConn,sendBuf,strlen(sendBuf)+1,0);// +1是为了客户端有 '\0'

		//接收信息
		char recvBuf[100];
		recv(sockConn,recvBuf,strlen(recvBuf)+1,0);
		printf("Server receive from Client : %s\n",recvBuf);

		closesocket(sockConn);
	}
	//===========================================等待客户端请求 与客户端通信

	return 0;
}