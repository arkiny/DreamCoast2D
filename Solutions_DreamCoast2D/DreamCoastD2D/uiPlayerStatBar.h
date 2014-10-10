#pragma once
#include "uiInterface.h"
#include "IGObject.h"

class uiPlayerStatBar :
	public uiInterface
{
public:
	uiPlayerStatBar();
	uiPlayerStatBar(ICharacter*);
	~uiPlayerStatBar();
public:
	void OnInit();
	void Update(float);
	void Render();

	//setter
	void setPlayer(ICharacter* in){ m_pplayer = in; }
private:
	void drawStatbar();
	ICharacter* m_pplayer;
};

