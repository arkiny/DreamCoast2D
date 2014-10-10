#pragma once

#include "IInventoryHandler.h"
#include "IGObject.h"

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

private:
	int m_nType;
	EFFECT m_sEffect;
};

