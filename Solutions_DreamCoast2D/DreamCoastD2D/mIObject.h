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
	// POINT�� �� ��� LONG ������ ��ȯ�� �Ͼ�� ������ �������꿡 ������ �����.
	//float _posX;
	//float _posY;
	
	VECTOR2D* _posVector;
};

