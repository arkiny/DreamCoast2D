#pragma once
#define _AFXDLL
#include <Afxwin.h>
#include <stdio.h>
#include <winsock2.h>
#include <conio.h> 

#include <iostream>

using namespace std;

struct movePacket{
	int id;
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
};