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
	/*  함수 : int connect( SOCKET s, const struct sockaddr FAR*  name, int namelen );
	기능 : 서버에 접속한다.
	인수 : 1. socket 함수에 의해 생성된 소켓 디스크립터(s)
	2. SOCKADDR_IN 구조체. (SOCKADDR*는 struct sockaddr FAR*)
	구조체는 주소체계(AF_INET), Port, 네트워크 주소로 채워진다.
	3. SOCKADDR_IN 구조체의 크기
	설명 : 대기 중인 서버에 접속한다. 접속 IP는 127.0.0.1로 한다.
	반환 : 성공 시 0, 실패 시 SOCKET_ERROR
	주의 : connect 함수는 블로킹 함수이다. 접속이 완료되었을 때 또는 실패 되었을 때만
	함수는 리턴한다.                                             */
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

		// '\n'문자 제거 : 
		int len = strlen(buf);
		
		if (buf[len - 1] == '\n')
		{
			buf[len - 1] = '\0';
		}

		//  scanf("%s",buf);  //공백 포함을 안함..!!
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
			printf("클라이언트와 접속이 끊어졌습니다.\n");
			break;
		}
		else{
			//printf("%d 바이트 수신 : %s \n", nRecv, buf);
			std::cout << nRecv << " 바이트 수신 : " << buf << std::endl;
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
		WSAGetLastError(), // 에러 코드를 읽어 옴
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpBuff,
		0,
		NULL);
	MessageBox(NULL, (LPCTSTR)lpBuff, szError, MB_ICONSTOP);
	LocalFree(lpBuff);
	exit(0);    // 프로그램을 종료

}

