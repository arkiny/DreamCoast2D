#include "stdafx.h"
#include <winsock2.h>
#include <stdio.h>
#include <Windows.h>
#include <iostream>
#pragma comment(lib, "ws2_32.lib")

#define MAX_BUFFER_SIZE 1024

void ErrorDisplay(wchar_t *szError);
void ErrorPrint(char *szError);

void main()
{
	int ret;
	WSADATA wsa;
	SOCKET s;
	SOCKADDR_IN saddr;

	ret = WSAStartup(MAKEWORD(2, 2), &wsa);
	if (ret != 0){
		ErrorDisplay(L"WSAStartup");
	}
	s = socket(AF_INET, SOCK_STREAM, 0);
	if (s == INVALID_SOCKET){
		ErrorDisplay(L"socket()");
	}
	/************************************************************************/
	/*  �Լ� : int connect( SOCKET s, const struct sockaddr FAR*  name, int namelen );
	��� : ������ �����Ѵ�.
	�μ� : 1. socket �Լ��� ���� ������ ���� ��ũ����(s)
	2. SOCKADDR_IN ����ü. (SOCKADDR*�� struct sockaddr FAR*)
	����ü�� �ּ�ü��(AF_INET), Port, ��Ʈ��ũ �ּҷ� ä������.
	3. SOCKADDR_IN ����ü�� ũ��
	���� : ��� ���� ������ �����Ѵ�. ���� IP�� 127.0.0.1�� �Ѵ�.
	��ȯ : ���� �� 0, ���� �� SOCKET_ERROR
	���� : connect �Լ��� ���ŷ �Լ��̴�. ������ �Ϸ�Ǿ��� �� �Ǵ� ���� �Ǿ��� ����
	�Լ��� �����Ѵ�.                                             */
	/************************************************************************/
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(5000);
	saddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	ret = connect(s, (SOCKADDR*)&saddr, sizeof(saddr));
	if (ret != 0){
		ErrorDisplay(L"connect()");
	}
	while (TRUE){
		char buf[MAX_BUFFER_SIZE+1];
		int nSend;
		int nRecv;

		memset(buf, 0, sizeof buf);
		//gets_s(buf);
		fgets(buf, MAX_BUFFER_SIZE+1, stdin);

		// '\n'���� ���� : 
		int len = strlen(buf);
		
		if (buf[len - 1] == '\n')
		{
			buf[len - 1] = '\0';
		}

		//  scanf("%s",buf);  //���� ������ ����..!!
		nSend = send(s, buf, strlen(buf), 0);
		if (nSend == SOCKET_ERROR){
			ErrorPrint("send()");
			break;
		}
		nRecv = recv(s, buf, sizeof(buf), 0);
		if (nRecv == SOCKET_ERROR){
			ErrorPrint("recv()");
			break;
		}
		else if (nRecv == 0){
			printf("Ŭ���̾�Ʈ�� ������ ���������ϴ�.\n");
			break;
		}
		else{
			//printf("%d ����Ʈ ���� : %s \n", nRecv, buf);
			std::cout << nRecv << " ����Ʈ ���� : " << buf << std::endl;
		}
	}
	closesocket(s);
	WSACleanup();
}

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
	//printf("%s : %s\n", szError, lpBuff);
	
	std::cout << szError << " " << lpBuff << std::endl;
	LocalFree(lpBuff);
}

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

