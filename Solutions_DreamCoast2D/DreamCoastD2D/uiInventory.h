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

	virtual void moveTo(float x, float y);
private:
	ICharacter* m_player;
	uiInterface* m_belt;
	//bool m_bActivated;
	const float m_fKeydelay = 0.2f;
	float m_fdelaytime = m_fKeydelay;
	float m_fmovedelaytime = m_fKeydelay;
	int m_nInventorySize;
	int m_bMoving;

	// 현재 보여주는 페이지에 따라서 뿌려주는 (update/render)해주는 범위가 달라진다.
	int m_nPage; 
};

