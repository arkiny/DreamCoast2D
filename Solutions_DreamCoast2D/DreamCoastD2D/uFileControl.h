#pragma once

class wWorld;

class uFileControl
{
public:
	uFileControl(wWorld* worldMap);
	~uFileControl();
public:
	void SaveToFile(int num);
	void LoadFromFile(int num, wWorld* to);
private:
	wWorld* m_pWorld;
};

