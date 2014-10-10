#pragma once
#include "IInventoryHandler.h"

// �ϴ� �Ϲ� ���Ƿ��� �����ϰ� ¥��
// ���� Ȯ���ؼ� �������� Ȯ��
class mItem : public IItem
{
public:
	mItem();
	mItem(int, Effect);
	~mItem();
	// Ÿ�� ������
	virtual void setType(int type);
	virtual int getType();
	
	virtual void setEffect(EFFECT);
	virtual void setEffect(float, float, float, float, float, float);

	// ��ưó�� ���ýÿ� ��Ƽ���ս÷� ����
	// virtual void setActivate();
	// virtual void setSelected();

	// ����
	virtual void itemOnEffect(ICharacter*);

	virtual void setAmount(int in) { m_nAmount = in; }
	virtual int getAmount(){ return m_nAmount; }
private:
	int m_nType;
	EFFECT m_sEffect;
	int m_nAmount;
};

