#pragma once


#define _AFXDLL
#include <Afxwin.h>
#include <stdio.h>
#include <winsock2.h>
#include <conio.h> 
#include <map>
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

class CCharServer
{
public:
	CCharServer();
	~CCharServer();
	bool IsConnected(){ return m_bIsConnected; } // returns connection status
	void StartListenClient(); // Listen to client
	int SendMessagePort(movePacket sMessage); // Send message to all clients.
	int RecClient(SOCKET sRecSocket); // receive message for a particulat socket

private:
	bool m_bIsConnected; // true - connected false - not connected
	int m_iServerPort;

	// socket, id
	map<SOCKET, int> m_vClientList; // All socket connected to client with ID/ClientSocket

	SOCKET m_SClient;
	SOCKET m_SListenClient; // socket listening for client calls
};