#pragma once

class mNetworkMob;
class uSprite;

class niMobState
{
public:
	niMobState(){};
	virtual ~niMobState(){};
public:
	//��������
	virtual void enter(mNetworkMob* pobj) = 0;
	//��������
	virtual void execute(mNetworkMob* pobj) = 0;
	//���� ��Ż
	virtual void exit(mNetworkMob* pobj) = 0;
protected:
	uSprite* m_sprite;
	float accumtime = 0.0f;
};

