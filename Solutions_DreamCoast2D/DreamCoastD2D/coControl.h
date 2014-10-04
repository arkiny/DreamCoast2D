#pragma once
#include "Singleton.h"

class coControl : public Singleton<coControl>
{
public:
	coControl();
	~coControl();
	// Key Control
	void onKeyDown(WPARAM wParam);
	void onKeyUp(WPARAM wParam);

	//// Mouse Control
	//void onLMBDown(LPARAM lParam); 
	//void onLMBUp(LPARAM lParam);
	void onMouseMove(LPARAM lParam);

	// Getter
	bool* getKeyControlInfo();
	POINTFLOAT getMousePosition();

private:
	bool m_bKeyCodeArray[256];
	POINTFLOAT m_MousePos;
};

