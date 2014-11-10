#pragma once
#define _AFXDLL
#include <Afxwin.h>
#include <stdio.h>
#include <winsock2.h>
#include <conio.h> 

#include <iostream>

using namespace std;

#pragma once

enum MESSAGETYPE_ID{
	PLAYER_ID_ENTRY,
	PLAYER_ID_UPDATE,
	PLAYER_ID_LOGOUT,
	MOB_ID_ENTRY,
	MOB_ID_UPDATE,
	MOB_ID_LOGOUT
};

enum MESSAGE_MOB_TYPE{
	NMOB_NOT_MOB,
	NMOB_PASSIVE_PORING,
	NMOB_ACTIVE_PORING,
	NMOB_BAPO
};

struct movePacket{
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
};

class CharCIPMessage
{
public:
	CharCIPMessage();
	~CharCIPMessage();
	void Init(string sIpAddress, int iPort);
	int SendMessagePort(movePacket sMessage);
	int RecMessagePort();
	bool IsConnected(){ return m_bIsConnected; }
	movePacket getPacket(){ return m_mPacket;}
	void setPacket(movePacket in){ m_mPacket = in; }
private:
	bool m_bIsConnected; // true - connected false - not connected
	string m_sServerIPAddress;
	int m_iServerPort = 8085;
	SOCKET conn; // socket connected to server
	movePacket m_mPacket;
	int mobid = 0;
};