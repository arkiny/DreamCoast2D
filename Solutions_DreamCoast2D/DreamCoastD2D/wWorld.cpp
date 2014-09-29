#include "stdafx.h"
#include "wWorld.h"
#include "mPlayer.h"
#include "wTileMap.h"

wWorld::wWorld()
{
	m_Player = nullptr;
	m_Map = nullptr;
}

wWorld::~wWorld()
{
	if (m_Player != NULL)
		delete m_Player;
	if (m_Map != NULL)
		delete m_Map;
}

void wWorld::OnInit(cD2DRenderer& renderer, coControl* in){
	m_Player = new mPlayer;
	m_Player->onInit(renderer);
	
	m_Map = new wTileMap;
	m_Map->setPlayer(m_Player);
	m_Map->onInit(renderer);

	// 데이터 통신용 포인터 연결
	// 컨트롤은 한번 정의해놓으면 고칠일이 없지만, 
	// 새로운 맵이나 새로운 캐릭터 같은 경우에는
	// 상호간 포인터 업데이트를 꼭 해줘야한다. 
	// 물론 이전 포인터 메모리 삭제하는 것도 필수
	m_Player->setTileMap(m_Map);
	m_Player->setKeyControl(in);	
	
	m_Map->setSize(25.0f, 25.0f);
}

void wWorld::Render(cD2DRenderer& renderer){
	// 맵에서 Player렌더까지 처리
	// 렌더 순서는 타일 -> 플레이어 -> 오브젝트 순으로 실시
	m_Map->onRender(renderer);
}

void wWorld::Update(float deltaTime){
	if (m_Player->isDeadComplete()){

	}
	m_Map->onUpdate(deltaTime);
}

bool wWorld::isGameOver() { return m_Player->isDeadComplete(); }