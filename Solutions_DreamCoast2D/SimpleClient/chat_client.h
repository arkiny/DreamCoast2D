#include <Afxwin.h>
#include <stdio.h>
#include <winsock2.h>
#include <conio.h> 

#include <iostream>

using namespace std;

class CIPMessage
{
public:
	CIPMessage();
	~CIPMessage();
	void Init(string sIpAddress, int iPort);
	int SendMessagePort(string sMessage);
	int RecMessagePort();
	bool IsConnected(){ return m_bIsConnected; }
private:
	bool m_bIsConnected; // true - connected false - not connected
	string m_sServerIPAddress;
	int m_iServerPort;
	SOCKET conn; // socket connected to server
};