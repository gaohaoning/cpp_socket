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
	SOCKET sockSrv=socket(AF_INET,SOCK_STREAM,0);
	// TCP:SOCK_STREAM
	// UDP:SOCK_DGRAM
	//===========================================���� socket

	//===========================================�� socket
	SOCKADDR_IN addrSrv;
	addrSrv.sin_family=AF_INET;
	addrSrv.sin_port=htons(6000);//hton = host to network
	addrSrv.sin_addr.S_un.S_addr=htonl(INADDR_ANY);//hton = host to network	
	//The htonl function converts a u_long from host to TCP/IP network byte order (which is big endian)
	//The htons function converts a u_short from host to TCP/IP network byte order (which is big-endian)

	bind(sockSrv,(SOCKADDR *)&addrSrv,sizeof(SOCKADDR));
	//===========================================�� socket

	//===========================================���� socket
	listen(sockSrv,SOMAXCONN);
	//===========================================���� socket

	//===========================================�ȴ��ͻ������� ��ͻ���ͨ��
	SOCKADDR_IN addrClient;
	int len=sizeof(SOCKADDR_IN);

	while(1)
	{
		SOCKET sockConn=accept(sockSrv,(SOCKADDR *)&addrClient,&len);
		//�˴����������ӵ�socket���ںͿͻ���ͨ��
		//��ǰ��socket�����ڼ����ͻ��˵���������

		//������Ϣ
		char sendBuf[100];
		sprintf(sendBuf,"Server send to Client : %s",inet_ntoa(addrClient.sin_addr));
		send(sockConn,sendBuf,strlen(sendBuf)+1,0);// +1��Ϊ�˿ͻ����� '\0'

		//������Ϣ
		char recvBuf[100];
		recv(sockConn,recvBuf,strlen(recvBuf)+1,0);
		printf("Server receive from Client : %s\n",recvBuf);

		closesocket(sockConn);
	}
	//===========================================�ȴ��ͻ������� ��ͻ���ͨ��

	return 0;
}