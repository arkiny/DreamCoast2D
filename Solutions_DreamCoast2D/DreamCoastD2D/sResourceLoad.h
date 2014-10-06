#pragma once
#include "sIScreen.h"
class sResourceLoad :
	public sIScreen
{
public:
	sResourceLoad();
	sResourceLoad(cGameManager* cg, int type);
	~sResourceLoad();

	void OnInit();
	void Update(float);
	void Render();
	void OnExit();

private:
	//sIScreen* m_pNextScreen;
	int m_nNextScreenType;
	bool m_bLoadingRendered = false;
	int m_nLoadingphase = 0;
};

