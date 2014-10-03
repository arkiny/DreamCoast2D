#pragma once

class mIObject;
class VECTOR2D;

class uCamera
{
public:
	uCamera(float sw, float sh, VECTOR2D* obj);
	~uCamera();

	VECTOR2D translasteToScreen(VECTOR2D* obj) const;
	float getScreenW() { return screen_w; }
	float getScreenH() { return screen_h; }

private:
	float getX() const;
	float getY() const;

	float screen_w;
	float screen_h;

	VECTOR2D* object;
};

