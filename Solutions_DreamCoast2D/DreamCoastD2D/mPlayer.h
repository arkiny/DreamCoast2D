#pragma once
#include "mIObject.h"
#include <queue>

class uSprite;

// Statemachine�� �̿����� ���� ä�� �����ϴ�
// player object
// ���� ��Ȳ�� ���� statemachine������ ��ȭ
class mPlayer : public mIObject
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
	// Ű���� �Է¿� ���� ������
	// Helper methods -> ���Ϳ��Ե� �ʿ��Ұ�� object�� �̵�
	void onMove(float deltaTime);
	void onAttack(float deltaTime);
	void onHit(float fdeltatime);
	void onDead(float);
	// skill �� ��ų Ŀ�ǵ忡 ���� statemachine���� ó��?
	void onCasting(float);
	//VECTOR2D vectorMove(float fdeltatime, DIRECTION dir);

	std::queue<int> m_qKeyInput;

	DIRECTION m_SeeDir; // ���� �ִ� ����
	DIRECTION m_MoveDir;
	OBJECTSTATE m_State;	

	// rendering alpha parameter control
	float m_alpha = 1.0f;
	
	// ���� ����, ���� ������ �߰�, ĳ���� �߰��� ���� ��ȭ
	float m_attackSpeed = 2.0f;
	float m_attackaccumtime = 0.0f;

	// onhit delay time
	float m_onhitMaxtime = 0.5f;
	float m_onhitAccumtime = 0.0f;

	// fade out time
	float m_deadFadeOutTime = 0.0f;

	bool m_deadcomp = false;

	// ��ų ĳ���� ����
	float m_castaccumtime = 0.0f;
};

