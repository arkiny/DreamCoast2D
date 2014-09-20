#pragma once
#include "cD2DRenderer.h"
#include "cIGameMgr.h"
//class cD2DRenderer;
//class mPlayer;

//class mPlayer;
class coControl;
class wWorld;
//class wTileMap;

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
private:
	coControl* m_pControl;
	
	//�ϴ� ���ӿ��带 �ٷ� �־������
	//���� �Ʒ� �����Ϳ��� �� ��ũ��(�޴���ũ��, ���� ��ũ��)�� ���� �˴ϴ�.
	wWorld* m_pWorld;
};

