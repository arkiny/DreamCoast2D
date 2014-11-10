#include "char_server.h"

CCharServer CServerObj;

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

CCharServer::CCharServer()
{
	cout << "Starting up TCP Char server\n";
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
	local.sin_port = htons((u_short)8085);

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

CCharServer::~CCharServer()
{
	closesocket(m_SListenClient);
	WSACleanup();
}

void CCharServer::StartListenClient()
{

	sockaddr_in from;
	int fromlen = sizeof(from);

	m_SClient = accept(m_SListenClient,
		(struct sockaddr*)&from, &fromlen);

	if (m_SClient != INVALID_SOCKET){
		//m_vInventory.insert(std::pair<int, mItem*>(item->getID(), item));
		//.push_back(m_SClient);

		m_vClientList.insert(std::pair<SOCKET, int>(m_SClient, m_vClientList.size() + 1));

		// 여기서 리스트에 add후에 아이디를 각 클라이언트에 쏴줌
		/*char in[10] = "";
		sprintf(in, "%d", m_vClientList.size());
		string b = in;
		string a = "Your ID is " + b;*/
		movePacket idsend;
		idsend.id = m_vClientList.size();
		char buf[sizeof(movePacket)];
		memcpy(&buf, &idsend, sizeof(movePacket));

		//send(m_SClient, buf, sizeof(movePacket), 0);
		std::map<SOCKET, int>::iterator itr;
		for (itr = m_vClientList.begin(); itr != m_vClientList.end(); itr++){
			send(itr->first, buf, sizeof(movePacket), 0);
		}

		cout << "Current Num Player" << m_vClientList.size() << endl;
		cout << idsend.id << " sended" << endl;
	}
	AfxBeginThread(ServerRecThread, (void *)m_SClient);

}



int CCharServer::SendMessagePort(movePacket sMessage)
{
	std::map<SOCKET, int>::iterator itr;
	char buf[sizeof(movePacket)];
	memcpy(&buf, &sMessage, sizeof(movePacket));

	int iStat = 0;
	if (m_vClientList.size() == 0)
		return 0;

	for (itr = m_vClientList.begin(); itr != m_vClientList.end(); itr++){
		/*char in[10] = "";
		sprintf(in, "%d", itr->first);
		string sending = in + sMessage;*/
		iStat = send(itr->first, buf, sizeof(movePacket), 0);
		/*if (iStat == -1){
			cout << itr->second << " out" << "\n";
			m_vClientList.erase(itr);			
		}*/
	}

	int msgtype;
	int id;
	int mob_uniq_id;
	int mob_type;
	int state;
	int direction;
	int seedir;
	float px;
	float py;
	float speed;

	cout << "MSGTYPE: " << sMessage.msgtype 
		<< ", sender id: "<<sMessage.id
		<< ", mobid: " << sMessage.mob_uniq_id
		<< ", mobtype: " << sMessage.mob_type << endl
		<< ", state: " << sMessage.state 
		<< ", dir: " << sMessage.direction
		<< ", seedir: " << sMessage.seedir
		<< ", position: (" << sMessage.px << ", " << sMessage.py << ")"
		<< ", Speed: " << sMessage.speed 
		<< endl;
	/*for (itl = m_vClientList.begin(); itl != m_vClientList.end(); itl++)
	{
		iStat = send(*itl, sMessage.c_str(), sMessage.size() + 1, 0);
		if (iStat == -1)
			m_vClientList.remove(*itl);
	}*/

	if (iStat == -1)
		return 1;

	return 0;

}

int CCharServer::RecClient(SOCKET sRecSocket)
{
	char temp[sizeof(movePacket)]; 
	movePacket buf;

	int iStat;

	//cout <<inet_ntoa(from.sin_addr) <<":"<<temp<<"\r\n";
	iStat = recv(sRecSocket, temp, sizeof(movePacket), 0);
	memcpy(&buf, &temp, sizeof(movePacket));

	// 새로운 몹 추가시 id 지정
	//if (buf.msgtype == MOB_ID_ENTRY){
	//	buf.mob_uniq_id = m_mobid;
	//	m_mobid++;
	//}
	//

	if (iStat == -1)
	{
		
		cout << m_vClientList.at(sRecSocket) << " out" << "\n";
		m_vClientList.erase(sRecSocket);		
		//m_vClientList.remove(sRecSocket);
		return 1;
	}
	else
	{		
		cout << "from: " << buf.id << "Recieved\n";

		SendMessagePort(buf);
		return 0;
	}
	return 0;

}




int main(int argc, char* argv[])
{
	int nRetCode = 0;
	char buf[sizeof(movePacket)];
	movePacket packetbuf;

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
		char buf[sizeof(movePacket)];
		memcpy(&buf, &packetbuf, sizeof(movePacket));
		if (CServerObj.SendMessagePort(packetbuf))
		{
			cout << "Problem in connecting to server. Check whether server is running\n";
			break;
		}
	}

	cout << "signing off.";
	getch();

	return nRetCode;
}
