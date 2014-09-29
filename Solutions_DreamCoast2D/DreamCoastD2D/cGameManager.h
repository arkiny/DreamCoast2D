#pragma once
#include "cD2DRenderer.h"
#include "cIGameMgr.h"

class coControl;
class wWorld;
class sIScreen;

class cGameManager :
	public cIGameMgr
{
public:
	cGameManager(void);
	virtual ~cGameManager(void);
	virtual void Render(cD2DRenderer&);
	virtual void Update(float deltaTime);
	virtual void MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	virtual void OnInit(cD2DRenderer&);

	// ��ũ�� ����, �� ��ũ���� �ݹ����� �޾ƿͼ�, �������� �Ѵ�?
	void changeScreen(sIScreen* in);
private:
	coControl* m_pControl;
	
	// ��ũ�� ������, ��ũ�� ����
	sIScreen* m_pCurrentScreen;
};

