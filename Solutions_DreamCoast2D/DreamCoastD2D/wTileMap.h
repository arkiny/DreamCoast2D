#pragma once
#include <vector>

class cD2DRenderer;
class VECTOR2D;
class uSprite;
class mIObject;

class wTileMap
{
public:
	wTileMap();
	~wTileMap();
	void onInit(cD2DRenderer& renderer);
	void onUpdate(float fdeltatime);
	void onRender(cD2DRenderer& renderer);

	// debug ī�޶� �� �÷��̾� �׽�Ʈ��
	void setPlayer(mIObject* p);

private:
	// ����Ʈ ���� ����, ����� world���� �ϴ���, �ش� �����͸� �޾ƿͼ�
	// ����, �浹 ó�� �ǽ� Ȥ�� ��(�� �ƴ϶� ���� ��ü������ �����ε�)
	// ���� ��ü�� �ʱ�ȭ�ϴ� ����� ������. (�̹� ������Ʈ�� ��ӹ��� Ŭ������ �ƴϹǷ�,
	// ���� �۾��� �� ������ �ϴ� �͵� ���� ����ϵ��ϴ�.)
	// ������ ���������� �ʴ����� �ٲ�� ��� �ɱ�?... �Ƹ� ������ �غ����ҵ� �ϴ�.
	mIObject* m_player;
	std::vector<mIObject*> m_mobs;
	
	uSprite* m_spriteAtlas;			// �� ��������Ʈ ����
	ID2D1Bitmap* m_ipD2DBitmap;		// �� ��������Ʈ ����

	// debug
	std::vector<int> m_vMapinfo;	// �������� ������ ����Ÿ
	int m_mapinfo[14][14];			// ���� �������� ����Ÿ ����

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
	::D2D1_RECT_F mapSize; // ���� �ܰ����� ������ �Լ�
	
	// ��� Ÿ���� �����ϴ� �Լ�
	void renderMap(cD2DRenderer& renderer);
	// Ÿ�� ������ �����ϴ� �Լ�, x��, y��, Ÿ���� �޾Ƽ� Ÿ�� �ϳ��� �����Ѵ�.
	void renderTile(float x, float y, int type, cD2DRenderer& renderer);
	// Ÿ�� ��ġ�� �޾Ƽ� �Ǻ��� Ÿ���� ���ؼ� �ǽ�, ���������� �������Ǵ� ���۸޼ҵ�
	void hRender(cD2DRenderer& renderer, VECTOR2D tilePos);
	
	// 2D��ǥ�� ISO��ǥ�� ��ȯ�ϴ� �Լ��ε� �հ� �̻��ϰ� ��� �Ѥ�
	VECTOR2D twoDtoISO(VECTOR2D in);
	// ���� ���͸� ������� isometric Ÿ���� ��ġ�� ��� �Լ�
	VECTOR2D getTileCoordinates(VECTOR2D in);	
};

// IsoMetrictile�� �⺻ ũ��� ����90 ����45�� �������� (spriteŸ���� ũ��)
// 0�� 0,0,45,90