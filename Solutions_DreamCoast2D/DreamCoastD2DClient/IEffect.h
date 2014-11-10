#pragma once
#include <d2d1.h>

__interface IEffect {
	virtual void update(float);
	virtual void render();
	virtual bool isEnd();
};

__interface IFontEffect : public IEffect{
	virtual void update(float);
	virtual void render();
};

__interface IBitMapEffect : public IEffect{
	virtual void update(float);
	virtual void render();
};