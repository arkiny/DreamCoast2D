#include "stdafx.h"
#include "char_client.h"
#include "netWorkCharManager.h"

//Global Message object
//CharCIPMessage MyMessObj;

template<> CharCIPMessage* Singleton<CharCIPMessage>::_instance = 0;

CharCIPMessage::CharCIPMessage()
{
	m_bIsConnected = false;
}

void CharCIPMessage::Init(string sIpAddress, int iPort)
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

CharCIPMessage::~CharCIPMessage()
{
	if (m_bIsConnected)
		closesocket(conn);
}

int CharCIPMessage::SendMessagePort(movePacket sMessage)
{
	int iStat = 0;
	char buf[sizeof(movePacket)];
	memcpy(&buf, &sMessage, sizeof(movePacket));

	iStat = send(conn, buf, sizeof(movePacket), 0);
	if (iStat == -1)
		return 1;

	return 0;

}

int CharCIPMessage::RecMessagePort()
{
	char acRetData[sizeof(movePacket)];
	movePacket m_mPacket;
	int iStat = 0;

	iStat = recv(conn, acRetData, sizeof(movePacket), 0);
	memcpy(&m_mPacket, &acRetData, sizeof(movePacket));

	

	// 만약 해당 id를 캐릭터 매니저가 가지고 있지 않으면 해당 아이디를 추가
	// 만약 해당 id를 캐릭터 매니저가 가지고 있으면 해당 아이디 업데이트
	if (m_bFirstConnect == true){
		netWorkCharManager::GetInstance().setMyId(m_mPacket.id);
		m_bFirstConnect = false;
	}
	else {
		if (netWorkCharManager::GetInstance().getMyId() != m_mPacket.id){
			// check if exist
			if (netWorkCharManager::GetInstance().hasCharacter(m_mPacket.id)){
				// update the move packet
			}
			else {
				netWorkCharManager::GetInstance().addToCharList(m_mPacket);
				// add the id and its movepacket
			}
		}
		else {
			// ignore
		}
	}
	//cout << "-->" << m_mPacket.id << "\n";
	if (iStat == -1)
		return 1;
	return 0;
}




//int main(int argc, char* argv[])
//{
//	char buf[4096];
//	cout << "TCP/IP 캐릭터 클라이언트 포트: 8085\n";
//	cout << "\n엔터만 누르면 나가짐";
//	cout << "\n===============================================\n";
//
//	//FILE *fp = fopen("server.ini", "r");
//	//if (fp == NULL)
//	//{
//	//	cout << "\nUnable to open server.ini. Please specify server IPsddress in server.ini";
//	//	return 1; // main failed
//	//}
//	string sServerAddress;
//	/*while ((fgets(buf, 4096, fp)) != NULL)
//	{
//	if (buf[0] == '#')
//	continue;
//	sServerAddress = buf;
//
//	}
//	fclose(fp);
//
//	if (sServerAddress.size() == 0)
//	{
//	cout << "\nUnable to find server IPaddress in server.ini";
//	cout << "\nPlease set server IPaddress";
//	getch();
//	return 0;
//	}*/
//
//	MyMessObj.Init("127.0.0.1", 8085);
//	if (!MyMessObj.IsConnected())
//	{
//		cout << "\nUnable to connect to the IPaddress specified in server.ini";
//		cout << "\nPlease check server IPaddress";
//		getch();
//		return 0;
//	}
//
//	AfxBeginThread(MessageRecThread, 0);
//	movePacket input;
//	input.id = 1;
//	input.state = 1;
//	input.direction = 1;
//	input.seedir = 1;
//	input.px = 1.0f;
//	input.py = 1.0f;
//	input.speed = 1.0f;
//
//	MyMessObj.setPacket(input);
//
//	while (gets(buf))
//	{
//		if (strlen(buf) == 0)
//			break;
//		if (MyMessObj.SendMessagePort(MyMessObj.getPacket()))
//		{
//			cout << "Problem in connecting to server. Check whether server is running\n";
//			break;
//		}
//	}
//
//	cout << "\nExit application:";
//	getch();
//	return 0;
//}