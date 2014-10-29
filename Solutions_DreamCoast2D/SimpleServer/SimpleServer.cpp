#include "stdafx.h"
#include <winsock2.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <Windows.h>
#include <string.h>
#pragma comment(lib, "ws2_32.lib")

class ChatRoom;
void ErrorDisplay(wchar_t *szError);
void ErrorPrint(char *szError);

class ChatSuppoter{
public:
	ChatSuppoter(SOCKET socket){
		caddrlen = sizeof(caddr);
		cs = accept(socket, (SOCKADDR*)&caddr, &caddrlen);
		if (cs == INVALID_SOCKET){
			ErrorPrint("accept()");
		}
		printf("Ŭ���̾�Ʈ IP  : %s\n", inet_ntoa(caddr.sin_addr));
		printf("Ŭ���̾�Ʈ port: %d\n", ntohs(caddr.sin_port));
		memset(buf, 0, sizeof(buf));
	}

	void Receive(){
		while (!flag){
			nRecv = recv(cs, buf, sizeof(buf), 0);
			if (nRecv == SOCKET_ERROR){
				ErrorPrint("recv()");
				flag = true;
				break;
			}
			else if (nRecv == 0){
				std::cout << "Ŭ�� ���� ������" << std::endl;
				printf("Ŭ���̾�Ʈ���� ������ ���������ϴ�.\n");
			}
			else{
				//���� ������ ���
				printf("%d ����Ʈ ���� :%s\n", nRecv, buf);
				nSend = send(cs, buf, nRecv, 0);
				if (nSend == SOCKET_ERROR){
					ErrorPrint("send()");
					break;
				}
			}
		}
	}

	void Send(){
		while (!flag){
			nSend = send(cs, buf, nRecv, 0);
			if (nSend == SOCKET_ERROR){
				ErrorPrint("recv()");
				break;
			}
		}
	}

	void CloseConnection(){
		closesocket(cs);
	}

	std::string toString(){
		std::string ret = inet_ntoa(caddr.sin_addr);
		return ret;
	}
private:
	SOCKET cs;
	char buf[1024];
	bool flag = false;
	int nRecv;
	int nSend;
	SOCKADDR_IN caddr;
	int caddrlen;
};



void main()
{
	int ret;
	WSADATA wsa;
	SOCKET s;
	SOCKADDR_IN saddr;
	//SOCKADDR_IN caddr;
	//int caddrlen;
	//SOCKET cs;
	//int nSend;
	/*
	�Լ�  : int WSAStartup(WORD wVersionRezuested, LPWSADATA lpWSAData);
	���  : WS2_32.DLL�� ����� �ʱ�ȭ �Ѵ�.
	�μ�  : ����, WSADATA ����ü ����.
	�ȸ�  : ���� winsock 2.2�� ���, ������ ���Ͽ� MAKEWORD(2,2)�� ���
	��ȯ  : ���� �� 0, ���� �� ���� �ڵ�
	����  : �� �Լ��� Ư���� ��찡 �ƴϸ�, �� ���α׷��� �� ���� ȣ�� �ȴ�.
	*/

	ret = WSAStartup(MAKEWORD(2, 2), &wsa);
	if (ret != 0){
		ErrorDisplay(L"WSAStartup");
	}
	/*
	�Լ�  : SOCKET socket(lnt af,int type,int protocol);
	���  : ������ ����
	�μ�  : 1. AF_INET ==> TCP/IP,UDP�� ��� ���,
	2. SOCK_STREAM(TCP/IP) �Ǵ� SOCK_DGRAM(UDP)
	3. IPPROTO_TCP(TCP/IP) �Ǵ� IPPROTO_UDP(UDP),�Ϲ������� 0���
	����  :���� ��ũ���͸� �����ϰ� , �ʿ� �ڿ��� �Ҵ��Ѵ�.
	��ȯ  : ���� �� ���� ��ũ����, ���н� INVALID_SOCKET
	*/
	s = socket(AF_INET, SOCK_STREAM, 0);
	if (s == INVALID_SOCKET){
		ErrorDisplay(L"socket()");
	}

	/*
	�Լ�  : int bind(SOCKET s, const struct sockaddr FAR* name,int namelen);
	���  : ������ ���� s�� ��Ʈ��ũ �ּҿ� ��Ʈ ��ȣ�� �����Ѵ�.
	�μ�  : 1. socket �Լ��� ���� ������ ���� ��ũ����(s)
	2. SOCKADDR_IN ����ü.(SOCKADDR* �Ǵ� struct sockaddr FAR*)
	����ü�� �ּ�ü��(AF_INET),port,��Ʈ��ũ �ּҷ� ä������ ��.
	3. SOCKADDR_IN ����ü�� ũ��
	����  : ������ ���� s ��ũ���Ϳ� ��Ʈ��ȣ�� ��Ʈ��ũ �ּҸ� ����.
	��ȯ  : ���� �� 0, ���н� SOCKET_ERROR
	����  : htons, htonl�� ȣ��Ʈ�� ����Ʈ ������ ��Ʈ��ũ ����Ʈ ������ �ٲ��ִ�
	�Լ�.  inet_addr()�Լ��� ��Ʈ��ũ �ּҸ� 4����Ʈ�� IN_ADDR������ �ٲ��ش�.
	*/
	ZeroMemory(&saddr, sizeof(saddr));
	saddr.sin_family = AF_INET;       // �ּ�ü��
	saddr.sin_port = htons(5000);      // ��Ʈ ��ȣ
	saddr.sin_addr.s_addr = htonl(INADDR_ANY);   // ��Ʈ��ũ ī�� ����
	//saddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	ret = bind(s, (SOCKADDR *)&saddr, sizeof(saddr));
	if (ret == SOCKET_ERROR){
		ErrorDisplay(L"bind()");
	}

	/*
	�Լ�  : int listen(SOCKET s,int backing);
	���  : Ŭ���̾�Ʈ ������ ���� �� �ִ� ��� ���·� �����Ѵ�.
	�μ�  : 1. socket �Լ��� ���� ������ ���� ��ũ����
	2. ���ÿ� ���� ������ �ִ� Ŭ���̾�Ʈ��.
	����  : �� �Լ��� ȣ�� �ϸ� Ŭ���̾�Ʈ�� ���� �� �� �ִ�.
	��ȯ  : ���� �� 0, ���н� SOCKET_ERROR
	����  :backog ���� 5�̸� , ���� ������ ���� 5�̱� ������ ��쿡 ����
	����ڰ� ���� ���� ������ ���� ���а� ����ϰ� �Ͼ.
	������ ȯ�濡�� �̰��� SOMAXCONN�� ����,
	UNIX�� Linux������ �ش� �ý��ۿ� �°� ���� ������ �����ؾ���.
	*/
	ret = listen(s, SOMAXCONN);
	if (ret == SOCKET_ERROR){
		ErrorDisplay(L"listen()");
	}
	while (TRUE){

		/*
		�Լ� : SOCKET accept(SOCKET s, struct sockaddr FAR* addr,int FAR* addrlen);
		��� : ���ӵ� Ŭ���̾�Ʈ�� �޾� ���δ�.
		�μ� : 1. socket �Լ��� ���� ������ ���� ��ũ����
		2. SOCKADDR_IN ����ü.����ü�� �ּ�ü��(AF_INET),port,��Ʈ��ũ �ּҷ� ä������.
		3.SOCKADDR_IN ����ü�� ũ��
		���� : listen �Լ��� ���� Ŭ���̾�Ʈ�� ������ ���Ǹ�, Ŭ���̾�Ʈ�� �����ؿ´�.
		accept ����� Ŭ���̾�Ʈ�� ������ ��� ,�׿� ������ ������ �����Ͽ� ��ȯ�Ѵ�.
		��ȯ : ���� �� ���� ������ SOCKET ��ũ����, ���� �� INVAID_SOCKET
		���� : accept �Լ��� ���ŷ �Լ��̴�. ���ŷ�̶� �Լ� ȣ�� �� �� �̻� �������� �ʰ�
		�Լ� ������ ������ �ִٴ� ��.
		*/

		/*caddrlen = sizeof(caddr);
		cs = accept(s, (SOCKADDR*)&caddr, &caddrlen);
		if (cs == INVALID_SOCKET){
			ErrorPrint("accept()");
			continue;
		}*/
		
		ChatSuppoter  a(s);

		/************************************************************************/
		/* Ŭ���̾�Ʈ ���� ǥ��
		inet_ntoa() �Լ��� IN_ADDR ����ü�� ���� ���ڿ��� ��ȯ ���ش�.
		ntohs()     �Լ��� ��Ʈ��ũ ����Ʈ ������ ���� ��ȣ�� ȣ��Ʈ��
		�°� ��ȯ ���ش�.             */
		/************************************************************************/
		/*printf("Ŭ���̾�Ʈ IP  : %s\n", inet_ntoa(caddr.sin_addr));
		printf("Ŭ���̾�Ʈ port: %d\n", ntohs(caddr.sin_port));*/

		//Ŭ���̾�Ʈ�� ������ ���� �� ��۽�(Echo Server)
		while (TRUE){
			/*char buf[1024];
			int nRecv;
			memset(buf, 0, sizeof(buf));*/

			/************************************************************************/
			/* �Լ� :int recv(SOCKET s, char FAR* buf,int len,int flags);
			��� : TCP/IP�� ���� �����͸� �����Ѵ�.
			�μ� : 1.accept �Լ��� ���� ������ ���� ��ũ����
			2.�����͸� ������ ����
			3.������ ����Ʈ�� �ִ밪
			4.�Ϲ������δ� 0,MSG_REEK�Ǵ� MSG_OOB��� ����.
			MSG_PEEK�� �����͸� �о���� ���� ���۸� ����� �ʴ´�.
			�Ϲ������δ� ���� ���۴� �����͸� �о�� �� �������.
			���� : �����͸� �����Ѵ�.
			��ȯ : ���� �� ���ŵ� ����Ʈ ��(�׻� 0���� ũ��),���� �� SOCKET_ERROR.
			Ŭ���̾�Ʈ�� ������ ���� �� 0.
			���� : recv �Լ��� ���ŷ �Լ�          */
			/************************************************************************/
			
			a.Receive();
			//nRecv = recv(cs, buf, sizeof(buf), 0);
			//if (nRecv == SOCKET_ERROR){
			//	ErrorPrint("recv()");
			//	break;
			//}
			//else if (nRecv == 0){
			//	std::cout << "Ŭ�� ���� ������" << std::endl;
			//	printf("Ŭ���̾�Ʈ���� ������ ���������ϴ�.\n");
			//}
			//else{
			//	//���� ������ ���
			//	printf("%d ����Ʈ ���� :%s\n", nRecv, buf);

			//	/************************************************************************/
			//	/* �Լ� : int send(SOCKET s,const char FAR *buf,int len,int flags);
			//	��� : TCP/IP�� ���� �����͸� �����Ѵ�.
			//	�μ� : 1. accept �Լ��� ���� ������ ���� ��ũ����
			//	2. �����͸� ������ ����.
			//	3. ������ ����Ʈ ��
			//	4. �Ϲ������δ� 0,MSG_DONTROUTE �Ǵ� MSG_OOB ��밡��
			//	MSG_DONTROUTE�� ��Ŭ ����� ���̺��� ���� ���� �ʵ��� ����.
			//	MSG_OOB�� ��� �����͸� ���� �� ���, �߻������ �ʴ´�.
			//	���� : �����͸� �����Ѵ�.
			//	��ȯ : ���� �� ���۵� ����Ʈ ��, ���� �� SOCKET_ERROR.
			//	���� : send �Լ��� ���ŷ �Լ� �̴�.                                */
			//	/************************************************************************/
			//	nSend = send(cs, buf, nRecv, 0);
			//	if (nSend == SOCKET_ERROR){
			//		ErrorPrint("send()");
			//		break;
			//	}

			//}
		}
		/************************************************************************/
		/*      �Լ� : int closesocket( SOCKET s );
		��� : ������ �ݰ�, �ڿ��� �����Ѵ�.
		�μ� : 1. ���� ���� ��ũ����(s �Ǵ� cs)
		���� : ������ �ݴ´�.
		��ȯ : ���� �� 0, ���� �� SOCKET_ERROR.
		���� : closesocket �Լ� ��� �� SO_LINGER �ɼǰ�
		SO_DONTLINGER �ɼ��� ������ �ޱ� ������ ��������.
		�Ʒ��� ǥ�� ����,
		SO_LINGER�� ���� ���� l_onoff�� 0�̰�, l_linger�� 0�� ������
		��� ����(hard close)�� �߻��Ͽ� ������ ��� ���ŵǰ�,
		��� ���� �ۼ��� �����ʹ� ��� �Ұ� �ȴ�.
		������ ������ �ۼ����� ���Ḧ ���ؼ��� shutdown �Լ��� ����ϴ� ���� ����.

		----------------------------------------------------------------------------------
		�ɼ�           | Ÿ�Ӿƿ�����  |  ��������  |  ������⿩�� |       ��   ��
		----------------------------------------------------------------------------------
		SO_DONTLINGER  |  ��� ����    |    ����    |   ��� �ȵ�   | ������ ���� ����
		SO_LINGER      |     0         |    hard    |   ��� �ȵ�   | ������ �ս� ����
		SO_LINGER      |    >0         |    ����    |   ��� ��     | �����ð� ������ ����
		----------------------------------------------------------------------------------
		SO_LINGER �ɼ��� ������ ���� ������ �� �ִ�. �̷��� �����ϸ� closesocket �Լ�
		��� �� 60�ʰ� ����ϸ鼭 ť�� �ִ� �����͸� �����Ѵ�. ���� ������ �Ϸ�Ǹ�,
		60�ʰ� �Ǳ� ���� ����� �����ȴ�. �߿��� �����͸� �۽� ���� ���� �� �����
		����ϴ� ���� ����. ���� closesocket �Լ��� �⺻������ SO_DONTLINGER �ɼ���
		�ֱ� ������ �� ����� ������� �ʾƵ� �ȴ�.

		LINGER linger = { 1, 60 };    // 1(��� ���), ���� �� 60 �ʰ� ��� ����
		if( setsockopt( s, SOL_SOCKET, SO_LINGER, (char*)&linger, sizeof(linger) ) != 0 )
		{
		printf( "���� ���� ����, �����ڵ� = %d \n", WSAGetLastError() );
		closesocket( s );    // ���� ����
		WSACleanup();        // WS2_32.DLL ��� ����
		return;
		}                                                        */
		/************************************************************************/
		a.CloseConnection();
	}

	// ���� ���ӿ� ������ �����Ѵ�.

	closesocket(s);
	/************************************************************************/
	/*  �Լ� : int  WSACleanup( void );
	��� : WS2_32.DLL�� ����� �����Ѵ�.
	�μ� : 1. ���� ���� ��ũ����(s �Ǵ� cs)
	���� : WS2_32.DLL�� ����� �����Ѵ�.
	��ȯ : ���� �� 0, ���� �� SOCKET_ERROR.
	���� : ���α׷��� �������� ���� �� ���� ȣ���ϸ� �ȴ�.
	���� ���α׷��� ���� �߿� �� �Լ��� ȣ���Ѵٸ� ��� ������ ����ȴ�. */
	/************************************************************************/
	WSACleanup();
}
/************************************************************************/
/*
�Լ� : void ErrorDisplay( char *szError )
��� : �޽��� �ڽ��� ������ ǥ���ϰ�, ���α׷��� ����(exit)�Ѵ�.
�μ� : WSAGetLastError()-���� �ֱٿ� �߻��� ���� ������ ��ȣ�� ������
���� : FormatMessage �Լ��� ���������� ���۸� �Ҵ��ϰ�, ���� �ֱٿ� �߻���
������ ���� �޽����� �����Ѵ�. ������ �޽����� ���۴� ������ ������
lpBuff�� �޾� �´�.
���� : FormatMessage �Լ��� ���������� �޸𸮸� �Ҵ��ϱ� ������ LocalFree
�Լ��� ȣ���Ͽ� �޸𸮸� �����Ͽ��� �Ѵ�.                    */
/************************************************************************/
void ErrorDisplay(wchar_t *szError)
{
	LPVOID lpBuff;
	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM,
		NULL,
		WSAGetLastError(), // ���� �ڵ带 �о� ��
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpBuff,
		0,
		NULL);
	MessageBox(NULL, (LPCTSTR)lpBuff, szError, MB_ICONSTOP);
	LocalFree(lpBuff);
	exit(0);    // ���α׷��� ����

}
/************************************************************************/
/*
�Լ� : void ErrorPrint( char *szError )
��� : �޽��� �ڽ��� ������ ǥ���ϰ�, ���α׷��� ����(exit)�Ѵ�.
�μ� : WSAGetLastError()-���� �ֱٿ� �߻��� ���� ������ ��ȣ�� ������
���� : FormatMessage �Լ��� ���������� ���۸� �Ҵ��ϰ�, ���� �ֱٿ� �߻���
������ ���� �޽����� �����Ѵ�. ������ �޽����� ���۴� ������ ������
lpBuff�� �޾� �´�.
���� : FormatMessage �Լ��� ���������� �޸𸮸� �Ҵ��ϱ� ������ LocalFree
�Լ��� ȣ���Ͽ� �޸𸮸� �����Ͽ��� �Ѵ�.                        */
/************************************************************************/
void ErrorPrint(char *szError)
{
	LPVOID lpBuff;
	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM,
		NULL,
		WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpBuff,
		0,
		NULL);
	std::cout << szError << " " << lpBuff << std::endl;
	//printf("%s : %s\n", szError, lpBuff);
	LocalFree(lpBuff);
}

class ChatRoom{
public:

private:

};

