#pragma once
#include "mCharacter.h"
#include <queue>

#define SKILLCOMMAND_MAX 16

class uSprite;

// Statemachine을 이용하지 않은 채로 실행하는
// player object
// 차후 상황에 따라서 statemachine형으로 변화
class mPlayer : public mCharacter, public IPlayable
{
public:
	mPlayer();
	~mPlayer();
	void onInit();
	void onUpdate(float fdeltatime);
	void onRender();
	void onRender(bool);
	
	// StatController
	void getHit(float dmg);

	// graphic control
	void setAlpha(float in){ m_alpha = in; }
	float getAlpha(){ return m_alpha; }

	// StateInitializer
	// void onIdle();

	bool isDeadComplete() { return m_deadcomp; }
	
private:
	// 키보드 입력에 따른 움직임
	// Helper methods -> 몬스터에게도 필요할경우 object로 이동
	void onMove(float deltaTime);
	void onAttack(float deltaTime);
	void onHit(float fdeltatime);
	void onDead(float);
	// skill 은 스킬 커맨드에 따라서 statemachine으로 처리?
	void onCasting(float);
		
	DIRECTION m_SeeDir; // 보고 있는 방향
	DIRECTION m_MoveDir;
	OBJECTSTATE m_State;	

	// rendering alpha parameter control
	float m_alpha = 1.0f;
	
	// 공속 변수, 차후 아이템 추가, 캐릭터 추가시 동적 변화
	float m_attackSpeed = 2.0f;
	float m_attackaccumtime = 0.0f;

	// onhit delay time
	float m_onhitMaxtime = 0.5f;
	float m_onhitAccumtime = 0.0f;

	// fade out time
	float m_deadFadeOutTime = 0.0f;

	bool m_deadcomp = false;


	/// Skill관련 헬퍼
	// 스킬 캐스팅 변수
	int m_naSkill[SKILLCOMMAND_MAX];
	float m_castaccumtime = 0.0f;
	
	std::queue<int> m_qKeyInput;
	void putKeyIntoQueue();

	// 스킬 캐스팅시에 Update체크를 위한 변수
	int m_castingSkill = 99;
	
	// 재귀함수로, 스킬이 같은지 비교하기 위한 함수
	bool skillCompare(std::queue<int> &keyinput, int* skillArray, int index);
	
	// 스킬에 따라 다른 효과를 얻기위한 함수
	void skillEffect(int skilltype);	
};

