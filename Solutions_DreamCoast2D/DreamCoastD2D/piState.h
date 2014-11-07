#pragma once

class mPlayer;
class uSprite;

class piState
{
public:
	piState(){};
	virtual ~piState(){};
public:
	//상태진입
	virtual void enter(mPlayer* pmon) = 0;
	//상태진행
	virtual void execute(mPlayer* pmon) = 0;
	//상태 이탈
	virtual void exit(mPlayer* pmon) = 0;
protected:
	uSprite* m_sprite;
	float accumtime = 0.0f;
};

