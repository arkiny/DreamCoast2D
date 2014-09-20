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

	// debug 카메라 및 플레이어 테스트용
	void setPlayer(mIObject* p);

private:
	// 포인트 정보 저장, 제어는 world에서 하더라도, 해당 포인터를 받아와서
	// 전투, 충돌 처리 실시 혹은 맵(이 아니라 이제 자체적으로 월드인듯)
	// 에서 단체로 초기화하는 방법도 좋을듯. (이미 오브젝트를 상속받은 클래스가 아니므로,
	// 월드 작업을 이 위에서 하는 것도 좋은 방법일듯하다.)
	// 하지만 스테이지가 맵단위로 바뀌면 어떻게 될까?... 아마 생각좀 해봐야할듯 하다.
	mIObject* m_player;
	std::vector<mIObject*> m_mobs;
	
	uSprite* m_spriteAtlas;			// 맵 스프라이트 정보
	ID2D1Bitmap* m_ipD2DBitmap;		// 맵 스프라이트 파일

	// debug
	std::vector<int> m_vMapinfo;	// 동적으로 저장할 데이타
	int m_mapinfo[14][14];			// 차후 동적으로 데이타 저장

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
	float _cameraX;
	float _cameraY;
	::D2D1_RECT_F mapSize; // 맵의 외곽선을 저장할 함수
	
	// 모든 타일을 렌더하는 함수
	void renderMap(cD2DRenderer& renderer);
	// 타일 개개를 렌더하는 함수, x축, y축, 타입을 받아서 타일 하나를 렌더한다.
	void renderTile(float x, float y, int type, cD2DRenderer& renderer);
	// 타일 위치를 받아서 피봇을 타일을 통해서 실시, 실질적으로 렌더링되는 헬퍼메소드
	void hRender(cD2DRenderer& renderer, VECTOR2D tilePos);
	
	// 2D좌표를 ISO좌표로 변환하는 함수인데 먼가 이상하게 됬다 ㅡㅡ
	VECTOR2D twoDtoISO(VECTOR2D in);
	// 받은 벡터를 기반으로 isometric 타일의 위치를 잡는 함수
	VECTOR2D getTileCoordinates(VECTOR2D in);	
};

// IsoMetrictile의 기본 크기는 가로90 세로45로 설정했음 (sprite타일의 크기)
// 0번 0,0,45,90