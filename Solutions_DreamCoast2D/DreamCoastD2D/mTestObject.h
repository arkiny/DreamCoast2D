#pragma once
#include "movePacket.h"
#include "IGObject.h"
class uCamera;

class mTestObject
{
public:
	mTestObject();
	mTestObject(movePacket in);
	~mTestObject();

	void init();
	void render(uCamera* cam);
	void update(float delta);

	movePacket getCurrentPacket(){ return m_CurrentPacket; }
	void setCurrentPacket(movePacket in) { m_CurrentPacket = in; }
	
private:
	VECTOR2D vectorMove(float fdeltatime, DIRECTION dir);
	movePacket m_CurrentPacket;
};

