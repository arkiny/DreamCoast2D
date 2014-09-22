#pragma once
#include "mIObject.h"

class MOBSTATE;

class mMonster :
	public mIObject
{
public:
	mMonster();
	~mMonster();
	void onInit(cD2DRenderer& renderer);
	void onUpdate(float fdeltatime);

	void changeState(MOBSTATE* pnew);

private:
	DIRECTION m_SeeDir; // ���� �ִ� ����
	OBJECTSTATE m_State;


	MOBSTATE* m_pState;

	// �⺻ ����
	float m_health = 100.0f;
	bool m_aggro = false;
};

