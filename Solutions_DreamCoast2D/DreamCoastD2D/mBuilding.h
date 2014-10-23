#pragma once
#include "IMapObject.h"

class uSprite;
class uCamera;
class VECTOR2D;

class mBuilding :
	public IMapObject
{
public:
	mBuilding();
	mBuilding(int buildingtype, VECTOR2D* cpos, uCamera* cam);
	~mBuilding();

	virtual void update(float);
	virtual void render();
	virtual bool isEnd(){ return m_endEffect; }
	virtual POINTFLOAT getPos();

private:
	uSprite* m_sprite;
	uCamera* m_cam;
	bool m_endEffect = false;
	float m_fAlpha = 1.0f;
	int m_nBuildingType = 0;
	VECTOR2D* m_cpos;
};

