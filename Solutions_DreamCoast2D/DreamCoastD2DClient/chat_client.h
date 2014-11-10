#pragma once

#include <winsock2.h>
#include <iostream>
#define _WINSOCK_DEPRECATED_NO_WARNINGS

using namespace std;

class CIPMessage
{
public:
	CIPMessage();
	~CIPMessage();
	void Init(string sIpAddress, int iPort);
	int SendMessagePort(string sMessage);
	int RecMessagePort(HWND hw, int ID_EDIT);
	bool IsConnected(){ return m_bIsConnected; }
	//void Puts(HWND hW, int ID_EDIT, char *str);

private:
	bool m_bIsConnected; // true - connected false - not connected
	string m_sServerIPAddress;
	int m_iServerPort;
	SOCKET conn; // socket connected to server
};