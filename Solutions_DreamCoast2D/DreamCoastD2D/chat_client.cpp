#include "stdafx.h"
#include "chat_client.h"

//Global Message object
//CIPMessage MyMessObj;

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

int CIPMessage::RecMessagePort(HWND hw, int id)
{

	char acRetData[4096];
	int iStat = 0;

	iStat = recv(conn, acRetData, 4096, 0);
	if (iStat == -1)
		return 1;
	//in = acRetData;
	// cout이 아니라 텍스박스 보낼 메세지
	//cout << "-->" << acRetData << "\n";
	Puts(hw, id, acRetData);
	return 0;

}

void CIPMessage::Puts(HWND hW, int ID_EDIT, char *str)
{
	int nLen = GetWindowTextLengthA(GetDlgItem(hW, ID_EDIT));
	SendMessageA(GetDlgItem(hW, ID_EDIT), EM_SETSEL, nLen, nLen);
	SendMessageA(GetDlgItem(hW, ID_EDIT), EM_REPLACESEL, TRUE, (long)(LPCTSTR)str);
	nLen = GetWindowTextLengthA(GetDlgItem(hW, ID_EDIT));
	SendMessageA(GetDlgItem(hW, ID_EDIT), EM_SETSEL, nLen, nLen);
	SendMessageA(GetDlgItem(hW, ID_EDIT), EM_REPLACESEL, TRUE, (long)(LPCTSTR)"\r\n");
}


//
//UINT  MessageRecThread(LPVOID pParam)
//{
//	while (1)
//	{
//		if (MyMessObj.RecMessagePort())
//			break;
//	}
//	return 0;
//}



