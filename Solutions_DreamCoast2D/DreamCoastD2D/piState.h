#pragma once

class mPlayer;
class uSprite;

class piState
{
public:
	piState();
	virtual ~piState();
public:
	//��������
	virtual void enter(mPlayer* pmon) = 0;
	//��������
	virtual void execute(mPlayer* pmon) = 0;
	//���� ��Ż
	virtual void exit(mPlayer* pmon) = 0;
protected:
	uSprite* m_sprite;
	float accumtime = 0.0f;
};

