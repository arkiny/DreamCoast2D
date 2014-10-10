#pragma once

#include "IInventoryHandler.h"
#include "IGObject.h"

// 일단 일반 포션류를 상정하고 짜되
// 차후 확장해서 장비류까지 확장
class mItem : public IItem
{
public:
	mItem();
	mItem(int, Effect);
	~mItem();
	// 타입 수정시
	virtual void setType(int type);
	virtual int getType();
	
	virtual void setEffect(EFFECT);
	virtual void setEffect(float, float, float, float, float, float);

	// 버튼처럼 선택시와 액티베잇시로 나눔
	// virtual void setActivate();
	// virtual void setSelected();

	// 사용시
	virtual void itemOnEffect(ICharacter*);

private:
	int m_nType;
	EFFECT m_sEffect;
};

