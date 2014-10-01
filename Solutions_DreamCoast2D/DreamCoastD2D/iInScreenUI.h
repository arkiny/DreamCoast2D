#pragma once
#include <vector>

class cD2DRenderer;
class uiInterface;

class iInScreenUI
{
public:
	iInScreenUI();
	virtual ~iInScreenUI();

	virtual void Render(cD2DRenderer&) = 0;
	virtual void Update(float) = 0;
	virtual void OnInit(cD2DRenderer&) = 0;

protected:
	std::vector<uiInterface*> m_pInterface;
};

