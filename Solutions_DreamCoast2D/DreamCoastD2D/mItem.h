#pragma once
#include "IItem.h"

// 일단 일반 포션류를 상정하고 짜되
// 차후 확장해서 장비류까지 확장
class mItem : public IItem
{
public:
	mItem();
	mItem(int, int, Effect);
	~mItem();
	// 타입 수정시
	virtual void Init();
	virtual void Render();
	virtual void Update(float);
	virtual void setType(int type, int id);
	virtual int getType();
	
	virtual void setEffect(EFFECT);
	virtual void setEffect(float, float, float, float, float, float);

	// 버튼처럼 선택시와 액티베잇시로 나눔
	// virtual void setActivate();
	// virtual void setSelected();
	
	// 사용시
	virtual void itemOnEffect(ICharacter*);

	virtual void setAmount(int in) { m_nAmount = in; }
	virtual int getAmount(){ return m_nAmount; }

	virtual int getID(){ return m_nID; }
	virtual void setID(int in) { m_nID = in; }
private:
	int m_nID;
	int m_nType;
	EFFECT m_sEffect;
	int m_nAmount;
};

