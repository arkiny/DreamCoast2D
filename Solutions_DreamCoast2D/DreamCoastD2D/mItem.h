#pragma once
#include "IItem.h"

class VECTOR2D;

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

	virtual void setPos(float, float);
	virtual VECTOR2D* getPos();

	virtual bool isSelected() { return m_bSelected; }
	virtual bool isActivated() { return m_bActivated; }
	virtual void setSelected(bool in){ m_bSelected = in; }
	virtual void setActivated(bool in) { m_bActivated = in; }

	virtual bool isMoving() { return m_bIsMoving; }
	virtual void setMoving(bool in){ m_bIsMoving = in; }

	virtual void saveOldPos(float x, float y);
	virtual POINTFLOAT getOldcur() { return m_fMB_cache_old; }
	virtual POINTFLOAT getGap() { return m_fMB_cache_gap; }
	virtual void moveTo(float x, float y);

	virtual bool isInside(float x, float y);

private:
	int m_nID;
	int m_nType;
	float m_fWidth;
	float m_fHeight;
	EFFECT m_sEffect;
	int m_nAmount;
	VECTOR2D* m_vPos;
	bool m_bSelected = false;
	bool m_bActivated = false;
	
	bool m_bIsMoving = false;
	POINTFLOAT m_fMB_cache_old;
	POINTFLOAT m_fMB_cache_gap;
};

