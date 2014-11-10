#pragma once

class mNetworkObject;
class uSprite;

class niState
{
public:
	niState(){};
	virtual ~niState(){};
public:
	//��������
	virtual void enter(mNetworkObject* pobj) = 0;
	//��������
	virtual void execute(mNetworkObject* pobj) = 0;
	//���� ��Ż
	virtual void exit(mNetworkObject* pobj) = 0;
protected:
	uSprite* m_sprite;
	float accumtime = 0.0f;
};

