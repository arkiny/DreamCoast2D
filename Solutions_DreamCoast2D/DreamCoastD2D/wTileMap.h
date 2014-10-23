#pragma once
#include <vector>
#include "IGObject.h"
#include "IMapObject.h"
class VECTOR2D;
class uSprite;
class uCamera;
class uTile;
class cResourceManager;
//

//
class wTileMap
{
public:
	wTileMap();
	~wTileMap();
	void onInit();
	void onUpdate(float fdeltatime);
	void onRender();

	// player와 커뮤니케이션 포인터 연결, init단계에서 설정해줘야한다.
	void setPlayer(ICharacter* p);

	// setSize, wWorld init단계에 설정해줘야 한다.
	void setSize(float horizontal, float vertical);

	// 받은 벡터를 기반으로 isometric 타일의 위치를 잡는 함수
	VECTOR2D getTileCoordinates(VECTOR2D in);
	void setTile(float x, float y, int type);
	int getMapinfo(int x, int y);
	bool sightScan(float sight, VECTOR2D monsterpos);
	

	VECTOR2D getMapLimit();
	// 타일에 오브젝트를 주입
	void addRenderObjectToTile(float x, float y, ICharacter* in);
	void addRenderMapObjectToTile(float x, float y, IMapObject* in);
	uTile* getTile(float x, float y);
	// 2D좌표를 ISO좌표로 변환하는 함수인데 먼가 이상하게 됬다 ㅡㅡ
	VECTOR2D twoDtoISO(VECTOR2D in);
	VECTOR2D getPlayerTilePos();
	
	void playerGetHit(float dmg);

	float getRectTileWidth(){ return _RectTileWidth; }
	float getRectTileHeight(){	return _RectTileHeight;	}

	void addMonsterTotile(float x, float y);
	void addMonsterTotile(float x, float y, int type);

	std::vector<ICharacter*>* getMobList() { return &m_mobs; }
	uCamera* getCamera(){ return m_Cam; }
	
	void addMapObjectTotile(float x, float y);
	void removeMapObjectFromTile(float x, float y);

private:
	// 포인트 정보 저장, 제어는 world에서 하더라도, 해당 포인터를 받아와서
	// 전투, 충돌 처리 실시 혹은 맵(이 아니라 이제 자체적으로 월드인듯)
	// 에서 단체로 초기화하는 방법도 좋을듯. (이미 오브젝트를 상속받은 클래스가 아니므로,
	// 월드 작업을 이 위에서 하는 것도 좋은 방법일듯하다.)
	// 하지만 스테이지가 맵단위로 바뀌면 어떻게 될까?... 아마 생각좀 해봐야할듯 하다.
	ICharacter* m_player;
	std::vector<ICharacter*> m_mobs;
	std::vector<IMapObject*> m_mapObjects;
	
	uSprite* m_spriteAtlas;			// 맵 스프라이트 정보
	ID2D1Bitmap* m_ipD2DBitmap;		// 맵 스프라이트 파일
	
	//mObjManager* m_MapObjects;

	//std::vector<int> m_vMapinfo;	// 동적으로 저장된 맵 데이타
	std::vector<uTile*> m_vMapObjectHandler; // uTile형식으로 핸들러, 맵오브젝트도 여기로 뿌려서 랜더

	uCamera* m_Cam;
	// debug	

	// tile의 갯수
	float _vertical;
	float _horizontal;

	// ?? 타일맵 가로세로를 재는건데 지금 계산과정이 이상해졌다.
	float _RectTileWidth;
	float _RectTileHeight;
	//

	// 차후 스크린과 HUD에 따른 동적 변경
	//(카메라는 맵의 첫 타일의 좌표를 변경하면서 조정하는 걸로... 실시)
	// 차후에 offset을 통한 타일 좌표의 변화도 적용해야 할것 같다.
	float _offsetX;
	float _offsetY;
	::D2D1_RECT_F mapSize; // 맵의 외곽선을 저장할 함수
	
	//// 타일 위치를 받아서 피봇을 타일을 통해서 실시, 실질적으로 렌더링되는 헬퍼메소드
	//void hRender(cD2DRenderer& renderer, VECTOR2D tilePos);
	//// 타일 개개를 렌더하는 함수, x축, y축, 타입을 받아서 타일 하나를 렌더한다.
	//void renderTile(float x, float y, int type, cD2DRenderer& renderer);
	// 모든 타일을 렌더하는 함수
	void renderMap();		
	
	// 나중에 옵션에 따라서 헬스바 키고 끄고 결정 -> UI
	void drawHealthBar(ICharacter* obj);

	// monster의 시야 스캐닝
	void scanVision(float sight, VECTOR2D monsterpos, VECTOR2D playerPos, bool* ret);


};

// IsoMetrictile의 기본 크기는 가로90 세로45로 설정했음 (sprite타일의 크기)
// 0번 0,0,45,90