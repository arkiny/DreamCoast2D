#pragma once
#include "cResourceID.h"
// resource에 있는 enum과 통일할것

class coControl;
class cGameManager;
class cResourceManager;

class sIScreen
{
public:
	sIScreen();
	sIScreen(cGameManager*);
	virtual ~sIScreen();
	
	virtual void OnInit() = 0;
	virtual void Update(float) = 0;
	virtual void Render() = 0;
	virtual void OnExit() = 0;

protected:
	// 차후 스크린 전환를 위한 콜백대기 포인터
	cGameManager* m_pGameManager;
};