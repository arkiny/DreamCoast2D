#pragma once
#include "IItem.h"

// �ϴ� �Ϲ� ���Ƿ��� �����ϰ� ¥��
// ���� Ȯ���ؼ� �������� Ȯ��
class mItem : public IItem
{
public:
	mItem();
	mItem(int, int, Effect);
	~mItem();
	// Ÿ�� ������
	virtual void Init();
	virtual void Render();
	virtual void Update(float);
	virtual void setType(int type, int id);
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

	virtual int getID(){ return m_nID; }
	virtual void setID(int in) { m_nID = in; }
private:
	int m_nID;
	int m_nType;
	EFFECT m_sEffect;
	int m_nAmount;
};

