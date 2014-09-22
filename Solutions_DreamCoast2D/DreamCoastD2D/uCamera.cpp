#include "stdafx.h"
#include "uCamera.h"
#include "VECTOR2D.h"

uCamera::uCamera(float sw, float sh, VECTOR2D* obj)
	:screen_w(sw), screen_h(sh), object(obj)
{
}

uCamera::~uCamera()
{
}

float uCamera::getX() const{
	return  object->x - (screen_w / 2);
}

float uCamera::getY() const{
	return  object->y - (screen_h / 2);
}

VECTOR2D uCamera::translasteToScreen(VECTOR2D* obj) const{
	VECTOR2D ret = VECTOR2D(obj->x - getX(), obj->y - getY());
	return ret;
}