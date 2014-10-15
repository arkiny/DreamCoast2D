#pragma once
#include "uiInterface.h"
#include "IGObject.h"
class uiInventory :
	public uiInterface
{
public:
	uiInventory();
	uiInventory(ICharacter*, uiInterface*);
	~uiInventory();
	virtual void OnInit();
	virtual void Update(float);
	virtual void Render();

	virtual void moveTo(float x, float y);
	
private:
	ICharacter* m_player;
	uiInterface* m_belt;
	//bool m_bActivated;
	const float m_fKeydelay = 0.2f;
	float m_fdelaytime = m_fKeydelay;
	float m_fmovedelaytime = m_fKeydelay;

	int m_nCurrentPage = 0;

	int m_nInventorySize;
	int m_bMoving;

	// ���� �����ִ� �������� ���� �ѷ��ִ� (update/render)���ִ� ������ �޶�����.
	int m_nPage = 0; 
	const int m_nWidthMax = 5;
	const int m_nHeightMax = 2;
	const int m_nMaxNumforaPage = m_nHeightMax * m_nWidthMax;

	D2D1_RECT_F m_RectPrevButton;
	D2D1_RECT_F m_RectNextButton;
	D2D1_RECT_F m_RectPageOut;
};

