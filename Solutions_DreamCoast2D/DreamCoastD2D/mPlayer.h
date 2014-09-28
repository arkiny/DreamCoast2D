#pragma once
#include "mIObject.h"

class coControl;
class uSprite;

// Statemachine�� �̿����� ���� ä�� �����ϴ�
// player object
// ���� ��Ȳ�� ���� statemachine������ ��ȭ
class mPlayer : public mIObject
{
public:
	mPlayer();
	~mPlayer();
	void onInit(cD2DRenderer& renderer);
	void onUpdate(float fdeltatime);
	void onRender(cD2DRenderer& renderer);
	void onRender(cD2DRenderer&, bool);

	// set Communication Pointer
	void setKeyControl(coControl* in);	

	// StatController
	void getHit(float dmg);

	// graphic control
	void setAlpha(float in){ m_alpha = in; }
	float getAlpha(){ return m_alpha; }

	// StateInitializer
	// void onIdle();
	
private:
	// Ű���� �Է¿� ���� ������
	// Helper methods -> ���Ϳ��Ե� �ʿ��Ұ�� object�� �̵�
	void onMove(float deltaTime);
	void onAttack(float deltaTime);
	void onHit(float fdeltatime);
	void onDead(float);
	// skill �� ��ų Ŀ�ǵ忡 ���� statemachine���� ó��?
	void onSkill(float);
	//VECTOR2D vectorMove(float fdeltatime, DIRECTION dir);

	DIRECTION m_SeeDir; // ���� �ִ� ����
	OBJECTSTATE m_State;	

	// Communicate Pointer with control and tileMap
	coControl *m_pControl;

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
};

