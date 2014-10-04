#pragma once
#include "cResourceID.h"
// resource�� �ִ� enum�� �����Ұ�

class coControl;
class cD2DRenderer;
class cGameManager;
class cResourceManager;

class sIScreen
{
public:
	sIScreen();
	sIScreen(cGameManager*);
	virtual ~sIScreen();
	
	virtual void OnInit(cD2DRenderer&) = 0;
	virtual void Update(float) = 0;
	virtual void Render(cD2DRenderer&) = 0;
	virtual void OnExit() = 0;

protected:
	// ���� ��ũ�� ��ȯ�� ���� �ݹ��� ������
	cGameManager* m_pGameManager;
};