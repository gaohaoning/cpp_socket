#include <afx.h>
#include <Winsock2.h>
#include <stdio.h>
#include <iostream>
using namespace std;

int main()
{
	//===========================================�����׽��ֿ� V1.1
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
	//===========================================�����׽��ֿ� V1.1

	//===========================================���� socket
	SOCKET sockSrv=socket(AF_INET,SOCK_DGRAM,0);
	// TCP:SOCK_STREAM
	// UDP:SOCK_DGRAM
	//===========================================���� socket

	//===========================================�� socket
	SOCKADDR_IN addrSrv;
	addrSrv.sin_family=AF_INET;
	addrSrv.sin_port=htons(6000);//hton = host to network
	addrSrv.sin_addr.S_un.S_addr=htonl(INADDR_ANY);//hton = host to network	
	
	bind(sockSrv,(SOCKADDR *)&addrSrv,sizeof(SOCKADDR));
	//===========================================�� socket


	//===========================================���տͻ�������
	SOCKADDR_IN addrClient;
	int len=sizeof(SOCKADDR_IN);
	char recvBuf[100];

	recvfrom(sockSrv,recvBuf,100,0,(SOCKADDR *)&addrClient,&len);
	printf("Server receive from Client : %s\n",recvBuf);
	//===========================================���տͻ�������

	//===========================================�ر�socket ��ֹsocket���ʹ��
	closesocket(sockSrv);
	WSACleanup();
	//===========================================�ر�socket ��ֹsocket���ʹ��

	return 0;
}