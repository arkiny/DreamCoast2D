#pragma once
#include "IGObject.h"

// up to first entering
class mCharacter : public ICharacter
{
public:
	virtual ~mCharacter();

	virtual void onInit() = 0;
	virtual void onUpdate(float fdeltatime) = 0;

	// object는 기본적으로 렌더링을 할것을 가지고 있기 때문에
	// 적절한 관리가 이루어지면 굳이 상속받아 오버라이딩 할 필요 없이
	// 가장 상위 클래스에서 실시 가능
	virtual void onRender();
	virtual void onRender(bool alpha);

	// position control
	VECTOR2D* getDrawPos(){ return _drawVector; }
	VECTOR2D* getRealPos(){ return _realVector; }
	virtual void setRealPos(float x, float y);
	virtual void setDrawPos(float x, float y);

	uSprite* getSprite() { return m_spriteAtlas; }
	wTileMap* getTileMap(){ return m_pTileMap; }
	void setBitMap(ID2D1Bitmap* input) { m_ipD2DBitmap = input; }

	// Set point connection with other class
	void setTileMap(wTileMap* in);
	void setCam(uCamera* in){ m_Cam = in; }
	uCamera* getCam(){ return m_Cam; }

	// health control
	float getHealth(){ return m_HP; }
	float getMAXHealth() { return m_MAXHP; }
	void setMAXHealth(float in) { m_MAXHP = in; }

	virtual void setHealth(float in){ m_HP = in; }
	virtual void getHit(float dmg);

	void setMP(float in){ m_MP = in; }
	float getMP(){ return m_MP; }
	void setMaxMp(float in) { m_MAXMP = in;	}
	float getMaxMp(){ return m_MAXMP; }

	void setMoveSpeed(float in){ m_moveSpeed = in; }
	float getMoveSpeed() { return m_moveSpeed; }

	void setDefense(float in){ m_defense = in; }
	float getDefense(){ return m_defense; }
	//
	VECTOR2D vectorMove(float fdeltatime, DIRECTION dir);

	void setDmg(float in){ m_fDmg = in; }
	float getDmg() const { return m_fDmg; }

protected:
	// 기본적으로 오브젝드들이 가지고 있을 정보들
	// POINT를 쓸 경우 LONG 값에서 변환이 일어나기 때문에 가감연산에 문제가 생긴다.
	VECTOR2D* _drawVector;			// 그림 위치(pivot)
	VECTOR2D* _realVector;			// 실제 위치(position)

	// Communicate Pointer with control and tileMap
	wTileMap *m_pTileMap;
	uCamera *m_Cam;

	// object의 sprites을 가지고 있는 빗맵
	// 차후 uSprite클래스내로 옮길지 고민
	// 그렇게 되면 렌더에 관한 처리는
	// 대부분 uSprite가 처리하게 되므로
	// player클래스는 업데이트 관련 모듈에
	// 집중가능
	uSprite* m_spriteAtlas;			// 스프라이트 정보
	ID2D1Bitmap* m_ipD2DBitmap;		// 스프라이트 메모리 주소

	// 체력 변수, 차후 아이템 추가, 캐릭터 추가시 동적 변화
	float m_MAXHP = 100.0f;
	float m_MAXMP = 100.0f;
	float m_HP = 100.0f;
	float m_MP = 100.0f;
	float m_moveSpeed = 100.0f;
	float m_defense = 0.0f;

	float m_fDmg = 0.0f;
	
};

