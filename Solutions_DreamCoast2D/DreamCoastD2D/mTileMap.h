#pragma once

#include "mIObject.h"

class mTileMap : public mIObject
{
public:
	mTileMap();
	~mTileMap();
	void onInit(cD2DRenderer& renderer);
	void onUpdate(float fdeltatime);
	void onRender(cD2DRenderer& renderer);
private:
	// tile�� ����
	float _vertical;
	float _horizontal;

	// ?? Ÿ�ϸ� ���μ��θ� ��°ǵ� ���� �������� �̻�������.
	float _RectTileWidth;
	float _RectTileHeight;
	//

	// ���� ��ũ���� HUD�� ���� ���� ����
	float _cameraX;
	float _cameraY;
	//

	// ��� Ÿ���� �����ϴ� �Լ�
	void renderMap(cD2DRenderer& renderer);

	// Ÿ�� ������ �����ϴ� �Լ�
	void renderTile(float x, float y, int type, cD2DRenderer& renderer);

	// 2D��ǥ�� ISO��ǥ�� ��ȯ�ϴ� �Լ��ε� �հ� �̻��ϰ� ��� �Ѥ�
	VECTOR2D twoDtoISO(VECTOR2D in);	
};

// IsoMetrictile�� �⺻ ũ��� ����90 ����45�� ��������

// 0�� 0,0,45,90