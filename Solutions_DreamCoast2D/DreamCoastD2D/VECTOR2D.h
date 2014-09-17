#pragma once

typedef class VECTOR2D
{
public:
	float x;
	float y;

	VECTOR2D();
	VECTOR2D(float _x, float _y);
	VECTOR2D operator+(const VECTOR2D& vec) const;
	VECTOR2D operator-(const VECTOR2D& vec) const;
	float Length();
	void Normalize();
	VECTOR2D operator*(float scalar) const;
	void DrawVector(HDC hdc, int x, int y, COLORREF color);
}*LPVECTOR2D;

const VECTOR2D vRight(1, 0);
const VECTOR2D vLeft(-1, 0);
const VECTOR2D vUp(0, -1);
const VECTOR2D vDown(0, 1);