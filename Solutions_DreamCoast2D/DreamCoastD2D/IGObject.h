#pragma once
#include <d2d1.h>


// up to first entering
enum DIRECTION{ LEFT, RIGHT, UP, DOWN, RIGHTDOWN, LEFTUP, LEFTDOWN, RIGHTUP, NOMOVE };
enum OBJECTSTATE{ ONIDLE, ONMOVE, ONATTACK, ONHIT, ONDEAD, ONCASTING };


class VECTOR2D;
class uSprite;
class wTileMap;
class uCamera;
class aiState;

__interface IGOBJECT {
	virtual void onInit() = 0;
	virtual void onUpdate(float fdeltatime) = 0;
	virtual void onRender() = 0;
	virtual void onRender(bool alpha) = 0;
	virtual VECTOR2D* getDrawPos() = 0;
	virtual VECTOR2D* getRealPos() = 0;
	virtual void setRealPos(float x, float y) = 0;
	virtual void setDrawPos(float x, float y) = 0;
	virtual uSprite* getSprite() = 0;
	virtual wTileMap* getTileMap() = 0;
	virtual void setBitMap(ID2D1Bitmap* input) = 0;
};

__interface ICharacter : public IGOBJECT {
	// Set point connection with other class
	// Set point connection with other class
	virtual void setTileMap(wTileMap* in);
	virtual void setCam(uCamera* in);

	// health control
	virtual float getHealth();
	virtual float getMAXHealth();
	virtual void setMAXHealth(float in);

	virtual void setHealth(float in);
	virtual void getHit(float dmg);

	virtual void setMP(float in);
	virtual float getMP();
	virtual void setMaxMp(float in);
	virtual float getMaxMp();

	virtual void setMoveSpeed(float in);
	virtual float getMoveSpeed();

	virtual void setDefense(float in);
	virtual float getDefense();
	// helper
	virtual VECTOR2D vectorMove(float fdeltatime, DIRECTION dir);
	//
};


__interface IPlayable{
	// StatController
	virtual void getHit(float dmg);

	// graphic control
	virtual void setAlpha(float in);
	virtual float getAlpha();

	// StateInitializer
	// void onIdle();

	virtual bool isDeadComplete();
};


__interface IMonster{
	// state control
	virtual OBJECTSTATE getState();
	virtual void setState(OBJECTSTATE in);

	// state machine control
	virtual void changeState(aiState* pnew);

	//void getHit(float in);

	// graphic control
	virtual void setAlpha(float in);
	virtual float getAlpha();

	// Sprite initializing
	virtual void onIdle();
	virtual void onAttack();
	virtual void onHit();
	virtual void onDeath();
	virtual void onMove();

	// move control
	virtual void moveRandom();
	virtual void moveToDest(float deltatime);

	// stat control(getter setter)
	virtual void getHit(float in);

	virtual float getdeltaTime();
	virtual void setDir(DIRECTION dir);
	virtual DIRECTION getDir();
	virtual void setDest(float x, float y);
	virtual void setDestinTile(float x, float y);
	virtual VECTOR2D* getDest();
	virtual float getMaxAggroLevel();
	virtual void setMaxAggroLevel(float in);
	virtual float getCurrentAggroLevel();
	virtual void setCurrentAggroLevel(float in);
	virtual float getVisionRange();
	virtual float getAttackRange();
	virtual float getSight();
	virtual float getAttackPower();
};