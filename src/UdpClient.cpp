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
	SOCKET sockClient=socket(AF_INET,SOCK_DGRAM,0);
	// TCP:SOCK_STREAM
	// UDP:SOCK_DGRAM
	//===========================================���� socket

	//===========================================��������˷�������
	SOCKADDR_IN addrSrv;//ע��======�����Ƿ������ĵ�ַ��Ϣ
	addrSrv.sin_family=AF_INET;
	addrSrv.sin_port=htons(6000);//�˿ں���������˱���һ��
	addrSrv.sin_addr.S_un.S_addr=inet_addr("127.0.0.1");//�˴���ʾ������ַ

	char sendBuf[100];
	sprintf(sendBuf,"Client send to Server : %s",inet_ntoa(addrSrv.sin_addr));
	sendto(sockClient,sendBuf,strlen(sendBuf)+1,0,(SOCKADDR *)&addrSrv,sizeof(SOCKADDR));
	//===========================================��������˷�������

	//===========================================�ر�socket ��ֹsocket���ʹ��
	closesocket(sockClient);
	WSACleanup();
	//===========================================�ر�socket ��ֹsocket���ʹ��


	return 0;
}