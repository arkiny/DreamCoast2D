#pragma once

class cD2DRenderer;
class VECTOR2D;
class uSprite;

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
	
	VECTOR2D* getPos(){ return _posVector; }
protected:
	// 기본적으로 오브젝드들이 가지고 있을 정보들
	// POINT를 쓸 경우 LONG 값에서 변환이 일어나기 때문에 가감연산에 문제가 생긴다.
	VECTOR2D* _posVector;			// 위치
	uSprite* m_spriteAtlas;			// 스프라이트 정보
	ID2D1Bitmap* m_ipD2DBitmap;		// 스프라이트 파일
};

