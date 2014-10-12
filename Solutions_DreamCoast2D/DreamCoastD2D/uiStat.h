#pragma once
#include "uiInterface.h"
#include "IGObject.h"
class uiStat :
	public uiInterface
{
public:
	uiStat();
	uiStat(ICharacter*);
	~uiStat();
	virtual void OnInit();
	virtual void Update(float);
	virtual void Render();
private:
	ICharacter* m_player;
	bool m_bActivated;
	const float m_fKeydelay = 0.2f;
	float m_fdelaytime = m_fKeydelay;
};

