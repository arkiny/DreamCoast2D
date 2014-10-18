#pragma once
// GFX 레이어
// 좌표와 이벤트를 받아서
// 해당 좌표에 그래픽 이펙트를 뿌려준다
// 해당 이벤트들은 queue로 관리하며
// 뽑아서 처리하고, 해당 이벤트 종료시에
// 푸쉬하지 않고 그대로 삭제한다.
// mGFX 레이어는 GameUI가 아닌, World에 존재하며
// 해당 이벤트 발생시, 각 캐릭터가 콜백해와서 해당 이벤트를 add한다.
#include <queue>
#include "Singleton.h"
#include "IEffect.h"

class mGFX : public Singleton<mGFX>
{
public:
	mGFX();
	~mGFX();
	void update(float);
	void render();
	void pushToEventQueue(IEffect* effect);
private:
	std::queue<IEffect*> m_qEffects;
};

