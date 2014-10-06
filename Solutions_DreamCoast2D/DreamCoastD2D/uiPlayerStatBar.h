#pragma once
#include "uiInterface.h"

class mIObject;

class uiPlayerStatBar :
	public uiInterface
{
public:
	uiPlayerStatBar();
	uiPlayerStatBar(mIObject*);
	~uiPlayerStatBar();
public:
	void OnInit();
	void Update(float);
	void Render();

	//setter
	void setPlayer(mIObject* in){ m_pplayer = in; }
private:
	void drawStatbar();
	mIObject* m_pplayer;
};

