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
private:
	ICharacter* m_player;
};

