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
		printf("클라이언트 IP  : %s\n", inet_ntoa(caddr.sin_addr));
		printf("클라이언트 port: %d\n", ntohs(caddr.sin_port));
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
				std::cout << "클라 접속 끊어짐" << std::endl;
				printf("클라이언트와의 접속이 끊어졌습니다.\n");
			}
			else{
				//받은 데이터 출력
				printf("%d 바이트 수신 :%s\n", nRecv, buf);
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
	함수  : int WSAStartup(WORD wVersionRezuested, LPWSADATA lpWSAData);
	기능  : WS2_32.DLL의 사용을 초기화 한다.
	인수  : 버전, WSADATA 구조체 번지.
	셜명  : 보통 winsock 2.2를 사용, 설정을 위하여 MAKEWORD(2,2)를 사용
	반환  : 성공 시 0, 실패 시 에러 코드
	주의  : 이 함수는 특별한 경우가 아니면, 한 프로그램에 한 번만 호출 된다.
	*/

	ret = WSAStartup(MAKEWORD(2, 2), &wsa);
	if (ret != 0){
		ErrorDisplay(L"WSAStartup");
	}
	/*
	함수  : SOCKET socket(lnt af,int type,int protocol);
	기능  : 소켓을 생성
	인수  : 1. AF_INET ==> TCP/IP,UDP일 경우 사용,
	2. SOCK_STREAM(TCP/IP) 또는 SOCK_DGRAM(UDP)
	3. IPPROTO_TCP(TCP/IP) 또는 IPPROTO_UDP(UDP),일반적으로 0사용
	설명  :소켓 디스크립터를 생성하고 , 필요 자원을 할당한다.
	반환  : 성공 시 소켓 디스크립터, 실패시 INVALID_SOCKET
	*/
	s = socket(AF_INET, SOCK_STREAM, 0);
	if (s == INVALID_SOCKET){
		ErrorDisplay(L"socket()");
	}

	/*
	함수  : int bind(SOCKET s, const struct sockaddr FAR* name,int namelen);
	기능  : 생성된 소켓 s에 네트워크 주소와 포트 번호를 연결한다.
	인수  : 1. socket 함수에 의해 생성된 소켓 디스크립터(s)
	2. SOCKADDR_IN 구조체.(SOCKADDR* 또는 struct sockaddr FAR*)
	구조체는 주소체계(AF_INET),port,네트워크 주소로 채워져야 함.
	3. SOCKADDR_IN 구조체의 크기
	설명  : 생성된 소켓 s 디스크립터에 포트번호와 네트워크 주소를 설정.
	반환  : 성공 시 0, 실패시 SOCKET_ERROR
	보충  : htons, htonl은 호스트의 바이트 순서를 네트워크 바이트 순서로 바꿔주는
	함수.  inet_addr()함수는 네트워크 주소를 4바이트의 IN_ADDR구조로 바꿔준다.
	*/
	ZeroMemory(&saddr, sizeof(saddr));
	saddr.sin_family = AF_INET;       // 주소체계
	saddr.sin_port = htons(5000);      // 포트 번호
	saddr.sin_addr.s_addr = htonl(INADDR_ANY);   // 네트워크 카드 설정
	//saddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	ret = bind(s, (SOCKADDR *)&saddr, sizeof(saddr));
	if (ret == SOCKET_ERROR){
		ErrorDisplay(L"bind()");
	}

	/*
	함수  : int listen(SOCKET s,int backing);
	기능  : 클라이언트 접속을 받을 수 있는 대기 상태로 진입한다.
	인수  : 1. socket 함수에 의해 생성된 소켓 디스크립터
	2. 동시에 접근 가능한 최대 클라이언트수.
	설명  : 이 함수를 호출 하면 클라이언트가 접속 할 수 있다.
	반환  : 성공 시 0, 실패시 SOCKET_ERROR
	주의  :backog 값이 5이면 , 동시 접속자 수는 5이기 때문에 경우에 따라
	사용자가 많은 서버 에서는 접속 실패가 빈번하게 일어남.
	윈도우 환경에서 이값은 SOMAXCONN이 권장,
	UNIX나 Linux에서는 해당 시스템에 맞게 값을 적절히 조정해야함.
	*/
	ret = listen(s, SOMAXCONN);
	if (ret == SOCKET_ERROR){
		ErrorDisplay(L"listen()");
	}
	while (TRUE){

		/*
		함수 : SOCKET accept(SOCKET s, struct sockaddr FAR* addr,int FAR* addrlen);
		기능 : 접속된 클라이언트를 받아 들인다.
		인수 : 1. socket 함수에 의해 생성된 소켓 디스크립터
		2. SOCKADDR_IN 구조체.구조체는 주소체계(AF_INET),port,네트워크 주소로 채워진다.
		3.SOCKADDR_IN 구조체의 크기
		설명 : listen 함수에 의해 클라이언트의 접속이 허용되면, 클라이언트가 접속해온다.
		accept 삼수는 클라이언트가 접속할 경우 ,그와 연관된 소켓을 생성하여 반환한다.
		반환 : 성공 시 새로 생성된 SOCKET 디스크립터, 실패 시 INVAID_SOCKET
		주의 : accept 함수는 블로킹 함수이다. 블로킹이란 함수 호출 시 더 이상 진행하지 않고
		함수 내에서 멈춰져 있다는 것.
		*/

		/*caddrlen = sizeof(caddr);
		cs = accept(s, (SOCKADDR*)&caddr, &caddrlen);
		if (cs == INVALID_SOCKET){
			ErrorPrint("accept()");
			continue;
		}*/
		
		ChatSuppoter  a(s);

		/************************************************************************/
		/* 클라이언트 정보 표시
		inet_ntoa() 함수는 IN_ADDR 구조체의 값을 문자열로 변환 해준다.
		ntohs()     함수는 네트워크 바이트 오더의 포터 번호를 호스트에
		맞게 변환 해준다.             */
		/************************************************************************/
		/*printf("클라이언트 IP  : %s\n", inet_ntoa(caddr.sin_addr));
		printf("클라이언트 port: %d\n", ntohs(caddr.sin_port));*/

		//클라이언트의 데이터 수신 및 재송신(Echo Server)
		while (TRUE){
			/*char buf[1024];
			int nRecv;
			memset(buf, 0, sizeof(buf));*/

			/************************************************************************/
			/* 함수 :int recv(SOCKET s, char FAR* buf,int len,int flags);
			기능 : TCP/IP를 통해 데이터를 수신한다.
			인수 : 1.accept 함수에 의해 생성된 소켓 디스크립터
			2.데이터를 수신할 버퍼
			3.수신할 바이트의 최대값
			4.일반적으로는 0,MSG_REEK또는 MSG_OOB사용 가능.
			MSG_PEEK는 데이터를 읽어오고 수신 버퍼를 비우지 않는다.
			일반적으로는 수신 버퍼는 데이터를 읽어온 후 비어진다.
			설명 : 데이터를 수신한다.
			반환 : 성공 시 수신된 바이트 수(항상 0보다 크다),실패 시 SOCKET_ERROR.
			클라이언트와 접속이 단절 시 0.
			주의 : recv 함수는 블로킹 함수          */
			/************************************************************************/
			
			a.Receive();
			//nRecv = recv(cs, buf, sizeof(buf), 0);
			//if (nRecv == SOCKET_ERROR){
			//	ErrorPrint("recv()");
			//	break;
			//}
			//else if (nRecv == 0){
			//	std::cout << "클라 접속 끊어짐" << std::endl;
			//	printf("클라이언트와의 접속이 끊어졌습니다.\n");
			//}
			//else{
			//	//받은 데이터 출력
			//	printf("%d 바이트 수신 :%s\n", nRecv, buf);

			//	/************************************************************************/
			//	/* 함수 : int send(SOCKET s,const char FAR *buf,int len,int flags);
			//	기능 : TCP/IP를 통해 데이터를 전송한다.
			//	인수 : 1. accept 함수에 의해 생성된 소켓 디스크립터
			//	2. 데이터를 전송할 버퍼.
			//	3. 전송할 바이트 수
			//	4. 일반적으로는 0,MSG_DONTROUTE 또는 MSG_OOB 사용가능
			//	MSG_DONTROUTE는 로클 라우팅 테이블을 참조 하지 않도록 설정.
			//	MSG_OOB는 긴급 데이터를 보낼 때 사용, 잘사용하지 않는다.
			//	설명 : 데이터를 전송한다.
			//	반환 : 성공 시 전송된 바이트 수, 실패 시 SOCKET_ERROR.
			//	주의 : send 함수는 블로킹 함수 이다.                                */
			//	/************************************************************************/
			//	nSend = send(cs, buf, nRecv, 0);
			//	if (nSend == SOCKET_ERROR){
			//		ErrorPrint("send()");
			//		break;
			//	}

			//}
		}
		/************************************************************************/
		/*      함수 : int closesocket( SOCKET s );
		기능 : 소켓을 닫고, 자원을 해제한다.
		인수 : 1. 닫을 소켓 디스크립터(s 또는 cs)
		설명 : 소켓을 닫는다.
		반환 : 성공 시 0, 실패 시 SOCKET_ERROR.
		주의 : closesocket 함수 사용 시 SO_LINGER 옵션과
		SO_DONTLINGER 옵션의 영향을 받기 때문에 주의하자.
		아래의 표에 보면,
		SO_LINGER의 설정 값이 l_onoff는 0이고, l_linger도 0일 때에는
		즉시 닫힘(hard close)이 발생하여 소켓은 즉시 제거되고,
		대기 중인 송수신 데이터는 모두 잃게 된다.
		안전한 데이터 송수신의 종료를 위해서는 shutdown 함수를 사용하는 것이 좋다.

		----------------------------------------------------------------------------------
		옵션           | 타임아웃간격  |  닫힘유형  |  닫힘대기여부 |       비   고
		----------------------------------------------------------------------------------
		SO_DONTLINGER  |  상관 없음    |    정상    |   블록 안됨   | 데이터 안전 전송
		SO_LINGER      |     0         |    hard    |   블록 안됨   | 데이터 손실 가능
		SO_LINGER      |    >0         |    정상    |   블록 됨     | 일정시간 데이터 전송
		----------------------------------------------------------------------------------
		SO_LINGER 옵션은 다음과 같이 설정할 수 있다. 이렇게 설정하면 closesocket 함수
		사용 시 60초간 대기하면서 큐에 있는 데이터를 전송한다. 만약 전송이 완료되면,
		60초가 되기 전에 블록이 해제된다. 중요한 데이터를 송신 중일 때는 이 방법을
		사용하는 것이 좋다. 물론 closesocket 함수는 기본적으로 SO_DONTLINGER 옵션이
		있기 때문에 이 방법을 사용하지 않아도 된다.

		LINGER linger = { 1, 60 };    // 1(기능 사용), 종료 시 60 초간 대기 설정
		if( setsockopt( s, SOL_SOCKET, SO_LINGER, (char*)&linger, sizeof(linger) ) != 0 )
		{
		printf( "종료 설정 실패, 에러코드 = %d \n", WSAGetLastError() );
		closesocket( s );    // 소켓 제거
		WSACleanup();        // WS2_32.DLL 사용 종료
		return;
		}                                                        */
		/************************************************************************/
		a.CloseConnection();
	}

	// 서버 접속용 소켓을 해제한다.

	closesocket(s);
	/************************************************************************/
	/*  함수 : int  WSACleanup( void );
	기능 : WS2_32.DLL의 사용을 종료한다.
	인수 : 1. 닫을 소켓 디스크립터(s 또는 cs)
	설명 : WS2_32.DLL의 사용을 종료한다.
	반환 : 성공 시 0, 실패 시 SOCKET_ERROR.
	주의 : 프로그램이 닫혀지기 전에 한 번만 호출하면 된다.
	만약 프로그램이 실행 중에 이 함수를 호출한다면 모든 소켓은 종료된다. */
	/************************************************************************/
	WSACleanup();
}
/************************************************************************/
/*
함수 : void ErrorDisplay( char *szError )
기능 : 메시지 박스에 에러를 표시하고, 프로그램을 종료(exit)한다.
인수 : WSAGetLastError()-가장 최근에 발생한 소켓 에러의 번호를 리턴함
설명 : FormatMessage 함수는 내부적으로 버퍼를 할당하고, 가장 최근에 발생한
에러에 대한 메시지를 생성한다. 생성된 메시지의 버퍼는 포인터 변수인
lpBuff가 받아 온다.
주의 : FormatMessage 함수는 내부적으로 메모리를 할당하기 때문에 LocalFree
함수를 호출하여 메모리를 해제하여야 한다.                    */
/************************************************************************/
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
/************************************************************************/
/*
함수 : void ErrorPrint( char *szError )
기능 : 메시지 박스에 에러를 표시하고, 프로그램을 종료(exit)한다.
인수 : WSAGetLastError()-가장 최근에 발생한 소켓 에러의 번호를 리턴함
설명 : FormatMessage 함수는 내부적으로 버퍼를 할당하고, 가장 최근에 발생한
에러에 대한 메시지를 생성한다. 생성된 메시지의 버퍼는 포인터 변수인
lpBuff가 받아 온다.
주의 : FormatMessage 함수는 내부적으로 메모리를 할당하기 때문에 LocalFree
함수를 호출하여 메모리를 해제하여야 한다.                        */
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

