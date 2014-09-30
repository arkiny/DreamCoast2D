#pragma once
#include <d2d1.h>

class cD2DRenderer;
class VECTOR2D;
class uSprite;
class wTileMap;
class uCamera;

// up to first entering
enum DIRECTION{ LEFT, RIGHT, UP, DOWN, RIGHTDOWN, LEFTUP, LEFTDOWN, RIGHTUP };
enum OBJECTSTATE{ ONIDLE, ONMOVE, ONATTACK, ONHIT, ONDEAD };

class mIObject
{
public:
	virtual ~mIObject();

	virtual void onInit(ID2D1Bitmap* resource) = 0;
	virtual void onUpdate(float fdeltatime) = 0;

	// object는 기본적으로 렌더링을 할것을 가지고 있기 때문에
	// 적절한 관리가 이루어지면 굳이 상속받아 오버라이딩 할 필요 없이
	// 가장 상위 클래스에서 실시 가능
	virtual void onRender(cD2DRenderer& renderer);
	virtual void onRender(cD2DRenderer& renderer, bool alpha);
	
	// position control
	VECTOR2D* getDrawPos(){ return _drawVector; }
	VECTOR2D* getRealPos(){ return _realVector; }
	void setRealPos(float x, float y);
	void setDrawPos(float x, float y);

	// Set point connection with other class
	void setTileMap(wTileMap* in);
	void setCam(uCamera* in){ m_Cam = in; }

	// health control
	float getHealth(){ return m_HP; }
	float getMAXHealth() { return m_MAXHP; }
	void setMAXHealth(float in) { m_MAXHP = in; }
	
	virtual void setHealth(float in){ m_HP = in; }	
	virtual void getHit(float dmg);

	//
	uSprite* getSprite() { return m_spriteAtlas; }
	wTileMap* getTileMap(){ return m_pTileMap; }
	void setBitMap(ID2D1Bitmap* input) { m_ipD2DBitmap = input; }

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

	VECTOR2D vectorMove(float fdeltatime, DIRECTION dir);
};

