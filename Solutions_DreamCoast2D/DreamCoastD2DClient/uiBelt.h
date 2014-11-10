#pragma once
#include "uiInterface.h"
#include "IGObject.h"
class uiBelt :
	public uiInterface
{
public:
	uiBelt();
	uiBelt(ICharacter*);
	~uiBelt();
	virtual void OnInit();
	virtual void Update(float);
	virtual void Render();
	virtual D2D1_RECT_F getBeltRect(int i);
private:
	ICharacter* m_player;
	D2D1_RECT_F m_ARect;
	D2D1_RECT_F m_SRect;
	D2D1_RECT_F m_DRect;
};

