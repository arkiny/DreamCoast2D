#pragma once
#include <vector>

class uiInterface;
class sIScreen;

class iInScreenUI
{
public:
	iInScreenUI();
	virtual ~iInScreenUI();

	virtual void Render() = 0;
	virtual void Update(float) = 0;
	virtual void OnInit(sIScreen*) = 0;

protected:
	std::vector<uiInterface*> m_pInterface;
	sIScreen* m_callbackScreen;
};

