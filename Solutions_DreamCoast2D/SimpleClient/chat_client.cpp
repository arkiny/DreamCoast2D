#include "stdafx.h"
#include "chat_client.h"

//Global Message object
CIPMessage MyMessObj;

CIPMessage::CIPMessage()
{
	m_bIsConnected = false;
}

void CIPMessage::Init(string sIpAddress, int iPort)
{

	m_sServerIPAddress = sIpAddress;
	m_iServerPort = iPort;
	struct hostent *hp;
	unsigned int addr;
	struct sockaddr_in server;


	WSADATA wsaData;

	int wsaret = WSAStartup(0x101, &wsaData);


	if (wsaret != 0)
	{
		return;
	}

	conn = socket(AF_INET, SOCK_STREAM, 0);
	if (conn == INVALID_SOCKET)
		return;

	addr = inet_addr(m_sServerIPAddress.c_str());
	hp = gethostbyaddr((char*)&addr, sizeof(addr), AF_INET);

	if (hp == NULL)
	{
		closesocket(conn);
		return;
	}

	server.sin_addr.s_addr = *((unsigned long*)hp->h_addr);
	server.sin_family = AF_INET;
	server.sin_port = htons(m_iServerPort);
	if (connect(conn, (struct sockaddr*)&server, sizeof(server)))
	{
		closesocket(conn);
		return;
	}
	m_bIsConnected = true;
	return;
}

CIPMessage::~CIPMessage()
{
	if (m_bIsConnected)
		closesocket(conn);
}

int CIPMessage::SendMessagePort(string sMessage)
{
	int iStat = 0;

	iStat = send(conn, sMessage.c_str(), sMessage.size() + 1, 0);
	if (iStat == -1)
		return 1;

	return 0;

}

int CIPMessage::RecMessagePort()
{

	char acRetData[4096];
	int iStat = 0;

	iStat = recv(conn, acRetData, 4096, 0);
	if (iStat == -1)
		return 1;
	cout << "-->" << acRetData << "\n";

	return 0;

}



UINT  MessageRecThread(LPVOID pParam)
{
	while (1)
	{
		if (MyMessObj.RecMessagePort())
			break;
	}
	return 0;
}



int main(int argc, char* argv[])
{
	char buf[4096];
	cout << "TCP/IP 클라이언트 포트: 8084\n";
	cout << "\n엔터만 누르면 나가짐";
	cout << "\n===============================================\n";

	FILE *fp = fopen("server.ini", "r");
	if (fp == NULL)
	{
		cout << "\nUnable to open server.ini. Please specify server IPsddress in server.ini";
		return 1; // main failed
	}
	string sServerAddress;
	while ((fgets(buf, 4096, fp)) != NULL)
	{
		if (buf[0] == '#')
			continue;
		sServerAddress = buf;

	}
	fclose(fp);

	if (sServerAddress.size() == 0)
	{
		cout << "\nUnable to find server IPaddress in server.ini";
		cout << "\nPlease set server IPaddress";
		getch();
		return 0;
	}

	MyMessObj.Init(sServerAddress.c_str(), 8084);
	if (!MyMessObj.IsConnected())
	{
		cout << "\nUnable to connect to the IPaddress specified in server.ini";
		cout << "\nPlease check server IPaddress";
		getch();
		return 0;
	}

	AfxBeginThread(MessageRecThread, 0);
	while (gets(buf))
	{
		if (strlen(buf) == 0)
			break;
		if (MyMessObj.SendMessagePort(buf))
		{
			cout << "Problem in connecting to server. Check whether server is running\n";
			break;
		}
	}

	cout << "\nExit application:";
	getch();
	return 0;
}