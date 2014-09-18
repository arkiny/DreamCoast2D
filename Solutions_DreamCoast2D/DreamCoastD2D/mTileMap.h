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
	// tile의 갯수
	float _vertical;
	float _horizontal;

	// ?? 타일맵 가로세로를 재는건데 지금 계산과정이 이상해졌다.
	float _RectTileWidth;
	float _RectTileHeight;
	//

	// 차후 스크린과 HUD에 따른 동적 변경
	float _cameraX;
	float _cameraY;
	//

	// 모든 타일을 렌더하는 함수
	void renderMap(cD2DRenderer& renderer);

	// 타일 개개를 렌더하는 함수
	void renderTile(float x, float y, int type, cD2DRenderer& renderer);

	// 2D좌표를 ISO좌표로 변환하는 함수인데 먼가 이상하게 됬다 ㅡㅡ
	VECTOR2D twoDtoISO(VECTOR2D in);	
};

// IsoMetrictile의 기본 크기는 가로90 세로45로 설정했음

// 0번 0,0,45,90