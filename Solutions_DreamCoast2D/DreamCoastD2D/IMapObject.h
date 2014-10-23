#pragma once
#include <d2d1.h>

class uCamera;

__interface IMapObject {
	virtual void update(float);
	virtual void render();
	virtual bool isEnd();
	virtual POINTFLOAT getPos();
	virtual void setCam(uCamera* in);
	virtual int getType();
};

