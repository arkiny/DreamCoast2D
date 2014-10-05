#pragma once
#include "uiInterface.h"
#include <vector>

// 10062014
// type shift menu
// 병신같지만 머 갠찮아.. 했잖아...
// 오늘 컨디션은 좀 별로다...
class sIScreen;
class cD2DRenderer;
class uiButton;

class uiMenu :
	public uiInterface
{
public:
	uiMenu();
	uiMenu(int type, sIScreen* callback);
	~uiMenu();
	void OnInit(cD2DRenderer&);
	void Update(float);
	void Render(cD2DRenderer&);

	void setType(int type) { m_type = type; }
	int getType() { return m_type; }

private:
	void draw(cD2DRenderer&, int);
	void changeMenuType();

	int m_nSelectedMenu = 0;
	uiButton* m_btnSelect;

	cD2DRenderer* m_renderer;
	sIScreen* m_pCallbackScreen;
	std::vector<uiInterface*> m_vButtons;
		
	int m_type = 5;
	bool m_bMenuActivated = false;
	const float m_fKeydelay = 0.2f;
	float m_fdelaytime = m_fKeydelay;
	float m_fmovedelaytime = m_fKeydelay;
};

