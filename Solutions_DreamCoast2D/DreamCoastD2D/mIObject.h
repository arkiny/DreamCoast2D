#pragma once

class cD2DRenderer;
class VECTOR2D;

class mIObject
{
public:
	virtual ~mIObject();

	virtual void onInit(cD2DRenderer& renderer) = 0;
	virtual void onUpdate(float fdeltatime) = 0;
	virtual void onRender(cD2DRenderer& renderer) = 0;

protected:
	// POINT를 쓸 경우 LONG 값에서 변환이 일어나기 때문에 가감연산에 문제가 생긴다.
	//float _posX;
	//float _posY;
	
	VECTOR2D* _posVector;
};

