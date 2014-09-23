#pragma once
#include "mIObject.h"

class coControl;
class uSprite;


class mPlayer : public mIObject
{
public:
	mPlayer();
	~mPlayer();
	void onInit(cD2DRenderer& renderer);
	void onUpdate(float fdeltatime);
	void onRender(cD2DRenderer& renderer);

	// set Communication Pointer
	void setKeyControl(coControl* in);	
	
private:
	// Ű���� �Է¿� ���� ������
	// Helper methods -> ���Ϳ��Ե� �ʿ��Ұ�� object�� �̵�
	void onMove(float deltaTime);
	void onAttack(float deltaTime);
	VECTOR2D vectorMove(float fdeltatime, DIRECTION dir);

	DIRECTION m_SeeDir; // ���� �ִ� ����
	OBJECTSTATE m_State;	

	// Communicate Pointer with control and tileMap
	coControl *m_pControl;		
	
	// ���� ����, ���� ������ �߰�, ĳ���� �߰��� ���� ��ȭ
	float m_attackSpeed = 2.0f;
	float m_attackaccumtime = 0.0f;
};

