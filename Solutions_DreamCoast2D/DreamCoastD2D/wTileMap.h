#pragma once
#include <vector>
#include "IGObject.h"

class VECTOR2D;
class uSprite;
class uCamera;
class uTile;
class cResourceManager;

class wTileMap
{
public:
	wTileMap();
	~wTileMap();
	void onInit();
	void onUpdate(float fdeltatime);
	void onRender();

	// player�� Ŀ�´����̼� ������ ����, init�ܰ迡�� ����������Ѵ�.
	void setPlayer(ICharacter* p);

	// setSize, wWorld init�ܰ迡 ��������� �Ѵ�.
	void setSize(float horizontal, float vertical);

	// ���� ���͸� ������� isometric Ÿ���� ��ġ�� ��� �Լ�
	VECTOR2D getTileCoordinates(VECTOR2D in);
	void setTile(float x, float y, int type);
	int getMapinfo(int x, int y);
	bool sightScan(float sight, VECTOR2D monsterpos);
	

	VECTOR2D getMapLimit();
	// Ÿ�Ͽ� ������Ʈ�� ����
	void addRenderObjectToTile(float x, float y, ICharacter* in);
	uTile* getTile(float x, float y);
	// 2D��ǥ�� ISO��ǥ�� ��ȯ�ϴ� �Լ��ε� �հ� �̻��ϰ� ��� �Ѥ�
	VECTOR2D twoDtoISO(VECTOR2D in);
	VECTOR2D getPlayerTilePos();
	
	void playerGetHit(float dmg);

	float getRectTileWidth(){ return _RectTileWidth; }
	float getRectTileHeight(){	return _RectTileHeight;	}

	std::vector<ICharacter*>* getMobList() { return &m_mobs; }
private:
	// ����Ʈ ���� ����, ����� world���� �ϴ���, �ش� �����͸� �޾ƿͼ�
	// ����, �浹 ó�� �ǽ� Ȥ�� ��(�� �ƴ϶� ���� ��ü������ �����ε�)
	// ���� ��ü�� �ʱ�ȭ�ϴ� ����� ������. (�̹� ������Ʈ�� ��ӹ��� Ŭ������ �ƴϹǷ�,
	// ���� �۾��� �� ������ �ϴ� �͵� ���� ����ϵ��ϴ�.)
	// ������ ���������� �ʴ����� �ٲ�� ��� �ɱ�?... �Ƹ� ������ �غ����ҵ� �ϴ�.
	ICharacter* m_player;
	std::vector<ICharacter*> m_mobs;
	
	uSprite* m_spriteAtlas;			// �� ��������Ʈ ����
	ID2D1Bitmap* m_ipD2DBitmap;		// �� ��������Ʈ ����
	
	std::vector<int> m_vMapinfo;	// �������� ����� �� ����Ÿ
	std::vector<uTile*> m_vMapObjectHandler; // uTile�������� �ڵ鷯

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
	
	//// Ÿ�� ��ġ�� �޾Ƽ� �Ǻ��� Ÿ���� ���ؼ� �ǽ�, ���������� �������Ǵ� ���۸޼ҵ�
	//void hRender(cD2DRenderer& renderer, VECTOR2D tilePos);
	//// Ÿ�� ������ �����ϴ� �Լ�, x��, y��, Ÿ���� �޾Ƽ� Ÿ�� �ϳ��� �����Ѵ�.
	//void renderTile(float x, float y, int type, cD2DRenderer& renderer);
	// ��� Ÿ���� �����ϴ� �Լ�
	void renderMap();		
	
	// ���߿� �ɼǿ� ���� �ｺ�� Ű�� ���� ���� -> UI
	void drawHealthBar(ICharacter* obj);

	// monster�� �þ� ��ĳ��
	void scanVision(float sight, VECTOR2D monsterpos, VECTOR2D playerPos, bool* ret);
};

// IsoMetrictile�� �⺻ ũ��� ����90 ����45�� �������� (spriteŸ���� ũ��)
// 0�� 0,0,45,90