#pragma once

class cD2DRenderer;

class mIObject
{
public:
	virtual ~mIObject();

	virtual void onInit(cD2DRenderer& renderer) = 0;
	virtual void onUpdate(float fdeltatime) = 0;
	virtual void onRender(cD2DRenderer& renderer) = 0;

protected:
	POINT _pos;
};

