#include "stdafx.h"
#include "chat_server.h"


CChatServer CServerObj;

UINT  ServerRecThread(LPVOID pParam)
{
	SOCKET sRecSocket = (SOCKET)pParam;
	while (1)
	{
		if (CServerObj.RecClient(sRecSocket))
			break;
	}
	return 0;
}

UINT  ServerListenThread(LPVOID pParam)
{

	while (1)
		CServerObj.StartListenClient();
	return 0;
}



CChatServer::CChatServer()
{
	cout << "Starting up TCP Chat server\n";
	m_bIsConnected = false;

	WSADATA wsaData;

	sockaddr_in local;

	int wsaret = WSAStartup(0x101, &wsaData);

	if (wsaret != 0)
	{
		return;
	}

	local.sin_family = AF_INET;
	local.sin_addr.s_addr = INADDR_ANY;
	local.sin_port = htons((u_short)8084);

	m_SListenClient = socket(AF_INET, SOCK_STREAM, 0);


	if (m_SListenClient == INVALID_SOCKET)
	{
		return;
	}


	if (bind(m_SListenClient, (sockaddr*)&local, sizeof(local)) != 0)
	{
		return;
	}


	if (listen(m_SListenClient, 10) != 0)
	{
		return;
	}

	m_bIsConnected = true;
	return;
}

CChatServer::~CChatServer()
{
	closesocket(m_SListenClient);

	WSACleanup();
}

void CChatServer::StartListenClient()
{

	sockaddr_in from;
	int fromlen = sizeof(from);

	m_SClient = accept(m_SListenClient,
		(struct sockaddr*)&from, &fromlen);

	if (m_SClient != INVALID_SOCKET){
		m_vClientList.push_back(m_SClient);
		cout << "Current Num Player" << m_vClientList.size() << endl;
	}
	AfxBeginThread(ServerRecThread, (void *)m_SClient);

}



int CChatServer::SendMessagePort(string sMessage)
{
	int iStat = 0;
	list<SOCKET>::iterator itl;

	if (m_vClientList.size() == 0)
		return 0;

	for (itl = m_vClientList.begin(); itl != m_vClientList.end(); itl++)
	{
		iStat = send(*itl, sMessage.c_str(), sMessage.size() + 1, 0);
		if (iStat == -1)
			m_vClientList.remove(*itl);
	}

	if (iStat == -1)
		return 1;

	return 0;

}

int CChatServer::RecClient(SOCKET sRecSocket)
{
	char temp[4096];
	int iStat;

	//cout <<inet_ntoa(from.sin_addr) <<":"<<temp<<"\r\n";
	iStat = recv(sRecSocket, temp, 4096, 0);
	if (iStat == -1)
	{
		m_vClientList.remove(sRecSocket);
		return 1;
	}
	else
	{
		cout << ":" << temp << "\n";
		SendMessagePort(temp);
		return 0;
	}
	return 0;

}




int main(int argc, char* argv[])
{
	int nRetCode = 0;
	char buf[4096];

	cout << "서버시작\n";
	cout << "엔터키를 누를시 종료\n";
	cout << "=================================================\n";

	if (!CServerObj.IsConnected())
	{
		cout << "\nFailed to initialise server socket";
		getch();
		return 1;
	}
	AfxBeginThread(ServerListenThread, 0);


	while (gets(buf))
	{
		if (strlen(buf) == 0)
			break;
		if (CServerObj.SendMessagePort(buf))
		{
			cout << "Problem in connecting to server. Check whether server is running\n";
			break;
		}
	}

	cout << "signing off.";
	getch();

	return nRetCode;
}
