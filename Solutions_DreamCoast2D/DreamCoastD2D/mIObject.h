#pragma once
#include <d2d1.h>

class cD2DRenderer;
class VECTOR2D;
class uSprite;
class wTileMap;
class uCamera;

// up to first entering
enum DIRECTION{ LEFT, RIGHT, UP, DOWN, RIGHTDOWN, LEFTUP, LEFTDOWN, RIGHTUP };
enum OBJECTSTATE{ ONMOVE, ONATTACK, ONHIT, ONDEAD };

class mIObject
{
public:
	virtual ~mIObject();

	virtual void onInit(cD2DRenderer& renderer) = 0;
	virtual void onUpdate(float fdeltatime) = 0;

	// object는 기본적으로 렌더링을 할것을 가지고 있기 때문에
	// 적절한 관리가 이루어지면 굳이 상속받아 오버라이딩 할 필요 없이
	// 가장 상위 클래스에서 실시 가능
	virtual void onRender(cD2DRenderer& renderer);
	virtual void onRender(cD2DRenderer& renderer, bool alpha);
	
	VECTOR2D* getDrawPos(){ return _drawVector; }
	VECTOR2D* getRealPos(){ return _realVector; }
	void setPos(float x, float y);
	void setTileMap(wTileMap* in);
	void setCam(uCamera* in){ m_Cam = in; }

protected:
	// 기본적으로 오브젝드들이 가지고 있을 정보들
	// POINT를 쓸 경우 LONG 값에서 변환이 일어나기 때문에 가감연산에 문제가 생긴다.
	VECTOR2D* _drawVector;			// 그림 위치
	VECTOR2D* _realVector;			// 실제 위치

	// Communicate Pointer with control and tileMap
	wTileMap *m_pTileMap;
	uCamera *m_Cam;

	// Player의 움직임을 가지고 있는 빗맵
	// 차후 uSprite클래스내로 옮길지 고민
	// 그렇게 되면 렌더에 관한 처리는
	// 대부분 uSprite가 처리하게 되므로
	// player클래스는 업데이트 관련 모듈에
	// 집중가능
	uSprite* m_spriteAtlas;			// 스프라이트 정보
	ID2D1Bitmap* m_ipD2DBitmap;		// 스프라이트 파일

	float m_hp;
};

