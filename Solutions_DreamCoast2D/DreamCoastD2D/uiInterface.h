#pragma once
#include "IGObject.h"

class VECTOR2D;

class uiInterface
{
public:
	uiInterface();
	uiInterface(float x, float y);
	virtual ~uiInterface();
public:
	virtual void OnInit() = 0;
	virtual void Update(float) = 0;
	virtual void Render() = 0;	

	VECTOR2D* getPos(){ return m_vpos; }
	void setPos(VECTOR2D* in);
	void setPos(float x, float y);
	void setMoveRectangle(D2D1_RECT_F in){ m_MoveWindowRect = in; }
	virtual bool isActivated() { return m_bActivated; }
	virtual void setActivated(bool in) { m_bActivated = in; }

	virtual bool isSelected() { return m_bSelected; }
	virtual void setSelected(bool in){ m_bSelected = in; }
	
	virtual bool isMoving() { return m_bIsMoving; }
	virtual void setMoving(bool in){ m_bIsMoving = in; }
	virtual POINTFLOAT getOldcur() { return m_fMB_cache_old; }
	virtual POINTFLOAT getGap() { return m_fMB_cache_gap; }

	virtual void moveTo(float x, float y);
	virtual void saveOldPos(float x, float y);
	virtual bool isInside(float x, float y);
	virtual D2D1_RECT_F getMoveWindowRect(){ return m_MoveWindowRect; }

//todo: 차후 마우스를 이용해서 유저인터페이스를 옮기기 위해 주석추가
private:
	VECTOR2D* m_vpos;


	bool m_bActivated = true;
	// 창 움직임
	bool m_bSelected = false;
	//bool m_bActivated = false;
	bool m_bIsMoving = false;

	POINTFLOAT m_fMB_cache_old;
	POINTFLOAT m_fMB_cache_gap;
	D2D1_RECT_F m_MoveWindowRect;
};

