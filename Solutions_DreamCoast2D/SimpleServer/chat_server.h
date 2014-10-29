#include <Afxwin.h>
#include <stdio.h>
#include <winsock2.h>
#include <conio.h> 
#include <list>
#include <iostream>

using namespace std;

class CChatServer
{
public:
	CChatServer();
	~CChatServer();
	bool IsConnected(){ return m_bIsConnected; } // returns connection status
	void StartListenClient(); // Listen to client
	int SendMessagePort(string sMessage); // Send message to sll clients.
	int RecClient(SOCKET sRecSocket); // receive message for a particulat socket
private:
	bool m_bIsConnected; // true - connected false - not connected
	int m_iServerPort;

	list<SOCKET> m_vClientList; // All socket connected to client
	SOCKET m_SClient;
	SOCKET m_SListenClient; // socket listening for client calls
};
