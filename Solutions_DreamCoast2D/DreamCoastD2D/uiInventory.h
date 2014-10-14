#pragma once
#include "uiInterface.h"
#include "IGObject.h"
class uiInventory :
	public uiInterface
{
public:
	uiInventory();
	uiInventory(ICharacter*, uiInterface*);
	~uiInventory();
	virtual void OnInit();
	virtual void Update(float);
	virtual void Render();
private:
	ICharacter* m_player;
	uiInterface* m_belt;
	bool m_bActivated;
	const float m_fKeydelay = 0.2f;
	float m_fdelaytime = m_fKeydelay;
	float m_fmovedelaytime = m_fKeydelay;
};

