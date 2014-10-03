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
	void OnInit(cD2DRenderer&);
	void Update(float);
	void Render(cD2DRenderer&);

	//setter
	void setPlayer(mIObject* in){ m_pplayer = in; }
private:
	void drawStatbar(cD2DRenderer& renderer);
	mIObject* m_pplayer;
};

