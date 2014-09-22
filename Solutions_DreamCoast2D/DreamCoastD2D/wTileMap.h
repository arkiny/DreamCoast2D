#pragma once
#include <vector>

class cD2DRenderer;
class VECTOR2D;
class uSprite;
class mIObject;
class uCamera;

class wTileMap
{
public:
	wTileMap();
	~wTileMap();
	void onInit(cD2DRenderer& renderer);
	void onUpdate(float fdeltatime);
	void onRender(cD2DRenderer& renderer);

	// player�� Ŀ�´����̼� ������ ����, init�ܰ迡�� ����������Ѵ�.
	void setPlayer(mIObject* p);

	// setSize, wWorld init�ܰ迡 ��������� �Ѵ�.
	void setSize(float horizontal, float vertical);

	// ���� ���͸� ������� isometric Ÿ���� ��ġ�� ��� �Լ�
	VECTOR2D getTileCoordinates(VECTOR2D in);
	void setTile(float x, float y, int type);
	int getMapinfo(int x, int y){ return m_vMapinfo[x + y*static_cast<int>(_vertical)]; }

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
	std::vector<int> m_vMapinfo;	// �������� ����� �� ����Ÿ

	uCamera* m_Cam;
	// debug	

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
	float _offsetX;
	float _offsetY;
	::D2D1_RECT_F mapSize; // ���� �ܰ����� ������ �Լ�
	
	// Ÿ�� ��ġ�� �޾Ƽ� �Ǻ��� Ÿ���� ���ؼ� �ǽ�, ���������� �������Ǵ� ���۸޼ҵ�
	void hRender(cD2DRenderer& renderer, VECTOR2D tilePos);
	// Ÿ�� ������ �����ϴ� �Լ�, x��, y��, Ÿ���� �޾Ƽ� Ÿ�� �ϳ��� �����Ѵ�.
	void renderTile(float x, float y, int type, cD2DRenderer& renderer);
	// ��� Ÿ���� �����ϴ� �Լ�
	void renderMap(cD2DRenderer& renderer);		
	
	// 2D��ǥ�� ISO��ǥ�� ��ȯ�ϴ� �Լ��ε� �հ� �̻��ϰ� ��� �Ѥ�
	VECTOR2D twoDtoISO(VECTOR2D in);	
};

// IsoMetrictile�� �⺻ ũ��� ����90 ����45�� �������� (spriteŸ���� ũ��)
// 0�� 0,0,45,90