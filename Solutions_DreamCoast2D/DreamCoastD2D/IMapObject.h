#pragma once
#include <d2d1.h>

__interface IMapObject {
	virtual void update(float);
	virtual void render();
	virtual bool isEnd();
	virtual POINTFLOAT getPos();
};

