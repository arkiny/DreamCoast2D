#pragma once
#include "cD2DRenderer.h"
#include "cIGameMgr.h"

class coControl;
class wWorld;
class sIScreen;
class cResourceManager;
class cSoundManager;

class cGameManager :
	public cIGameMgr
{
public:
	cGameManager(void);
	virtual ~cGameManager(void);
	virtual void Render();
	virtual void Update(float deltaTime);
	virtual void MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	virtual void OnInit();

	// ��ũ�� ����, �� ��ũ���� �ݹ����� �޾ƿͼ�, �������� �Ѵ�?
	void changeScreen(sIScreen* in);
private:
	coControl* m_pControl;	
	// ��ũ�� ������, ��ũ�� ����
	sIScreen* m_pCurrentScreen;
	// ���� �������� ��ũ�� �̴ϼȶ���¡�Ҷ� ���� �ֵ��� �޾Ƴ��� ������
	// ������ ���� �����ϸ鼭 ���ټ� �ֵ��� ����� �غ���.
	cResourceManager* m_pResourceMng;
	cSoundManager* m_pSoundMng;
};

