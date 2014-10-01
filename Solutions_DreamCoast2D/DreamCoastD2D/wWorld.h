#pragma once
#include "cD2DRenderer.h"

class coControl;
class mPlayer;
class wTileMap;
class cResourceManager;

class wWorld
{
public:
	wWorld();
	~wWorld();

	void Render(cD2DRenderer&);
	void Update(float deltaTime);
	void OnInit(cD2DRenderer&);

	mPlayer* getPlayer(){ return m_Player; }
	wTileMap* getMap() { return m_Map; }
	bool isGameOver(); 
private:
	// player init은 world에서 하지만, 그 관리는 m_Map에서 포인터를 받아서 실시
	mPlayer* m_Player;
	wTileMap* m_Map;

	// getter와 setter설정을 하면 player class와 map의 상호작용을 여기서 끝낼수 있을 것 같은데..
	// 지금은 좀 꼬여있는 상태, 몬스터 상호 작용을 어떻게 해야할지 의문
	// 몬스터와 플레이어 위치를 받아와서 여기서 처리를 할수 있는게 좋은거 같은데
	// 몬스터 구현후에 대대적인 구조 정립이 필요할듯.
	// player와 m_Map내의 player 포인터를 삭제하고, getter와 setter를 이용해서
	// world클래스에서 처리하는 걸로..? 아니면 애당초 wTileMap 자체가 worldmap이나 다름없으므로
	// 그 안에서 모두 처리하는 걸로? 그럼 컨트롤 인자를 계속 받아와야 하는건가?

	// World에서 스테이지를 관리해주고, 플레이어 클래스의 포인터만 뽑아서 끼워넣기로 관리하는 걸로
	// FSM을 이용하면, 스테이지 관리도 이용할수 있을거 같다. World에 아래와 같이 포인터를 넣고
	// 필요한것마다 갈아쓰는 것으로 맵관리
	// vector<wTileMap*> MapList;
};

