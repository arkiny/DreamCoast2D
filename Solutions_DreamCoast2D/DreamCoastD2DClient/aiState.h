#pragma once

class mMonster;
class uSprite;

// aiState가 괜찮게 설정되면, 플레이어 오브젝트도 스테이트 머신으로 치환
class aiState
{
public:
	aiState(){}
	virtual ~aiState(){}
public:
	//상태진입
	virtual void enter(mMonster* pmon) = 0;
	//상태진행
	virtual void execute(mMonster* pmon) = 0;
	//상태 이탈
	virtual void exit(mMonster* pmon) = 0;
protected:
	uSprite* m_sprite;
	float accumtime = 0.0f;
};


