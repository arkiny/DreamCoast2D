#pragma once
#define _AFXDLL
#include <Afxwin.h>
#include <stdio.h>
#include <winsock2.h>
#include <conio.h> 

#include <iostream>
#include "Singleton.h"
#include "movePacket.h"
using namespace std;


class CharCIPMessage : public Singleton<CharCIPMessage>
{
public:
	CharCIPMessage();
	~CharCIPMessage();
	void Init(string sIpAddress, int iPort);
	int SendMessagePort(movePacket sMessage);
	int RecMessagePort();
	bool IsConnected(){ return m_bIsConnected; }

	movePacket getPacket(){ return m_mPacket; }
	void setPacket(movePacket in){ m_mPacket = in; }

private:
	bool m_bIsConnected; // true - connected false - not connected
	bool m_bFirstConnect = true;
	string m_sServerIPAddress;
	int m_iServerPort = 8085;
	SOCKET conn; // socket connected to server
	movePacket m_mPacket;
};