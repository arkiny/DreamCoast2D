#pragma once
#include "cD2DRenderer.h"

class coControl;
class mPlayer;
class wTileMap;

class wWorld
{
public:
	wWorld();
	~wWorld();

	void Render(cD2DRenderer&);
	void Update(float deltaTime);
	void OnInit(cD2DRenderer&, coControl*);

private:
	// player init은 world에서 하지만, 그 관리는 m_Map에서 포인터를 받아서 실시
	mPlayer* m_Player;
	wTileMap* m_Map;

	// World에서 스테이지를 관리해주고, 플레이어 클래스의 포인터만 뽑아서 끼워넣기로 관리하는 걸로
	// FSM을 이용하면, 스테이지 관리도 이용할수 있을거 같다. World에 아래와 같이 포인터를 넣고
	// 필요한것마다 갈아쓰는 것으로 맵관리
	// vector<wTileMap*> MapList;
};

