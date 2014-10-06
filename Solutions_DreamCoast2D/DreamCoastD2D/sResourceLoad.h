#pragma once
#include "sIScreen.h"
class sResourceLoad :
	public sIScreen
{
public:
	sResourceLoad();
	sResourceLoad(cGameManager* cg, int type);
	~sResourceLoad();

	void OnInit(cD2DRenderer&);
	void Update(float);
	void Render(cD2DRenderer&);
	void OnExit();

private:
	//sIScreen* m_pNextScreen;
	int m_nNextScreenType;
	cD2DRenderer* m_pRenderer;
};

