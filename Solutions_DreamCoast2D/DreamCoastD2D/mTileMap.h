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

	// ī�޶� �׽�Ʈ��
	void setPlayer(mIObject* p);
private:
	mIObject* m_player;

	// tile�� ����
	float _vertical;
	float _horizontal;

	// ?? Ÿ�ϸ� ���μ��θ� ��°ǵ� ���� �������� �̻�������.
	float _RectTileWidth;
	float _RectTileHeight;
	//

	// ���� ��ũ���� HUD�� ���� ���� ����
	//(ī�޶�� ���� ù Ÿ���� ��ǥ�� �����ϸ鼭 �����ϴ� �ɷ�... �ǽ�)
	// ���Ŀ� offset�� ���� Ÿ�� ��ǥ�� ��ȭ�� �����ؾ� �Ұ� ����.

	float _cameraX;
	float _cameraY;
	//float _leftp;
	//float _topp;
	//

	void hRender(cD2DRenderer& renderer, VECTOR2D tilePos);
	// ��� Ÿ���� �����ϴ� �Լ�
	void renderMap(cD2DRenderer& renderer);

	// Ÿ�� ������ �����ϴ� �Լ�
	void renderTile(float x, float y, int type, cD2DRenderer& renderer);

	// 2D��ǥ�� ISO��ǥ�� ��ȯ�ϴ� �Լ��ε� �հ� �̻��ϰ� ��� �Ѥ�
	VECTOR2D twoDtoISO(VECTOR2D in);
	
	VECTOR2D getTileCoordinates(VECTOR2D in);

	::D2D1_RECT_F mapSize;

	// debug
	// ���� �������� ����Ÿ ����
	int m_mapinfo[14][14];
};

// IsoMetrictile�� �⺻ ũ��� ����90 ����45�� ��������

// 0�� 0,0,45,90