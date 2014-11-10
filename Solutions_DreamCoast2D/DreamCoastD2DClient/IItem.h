#pragma once
#include "IGObject.h"
#include "cResourceID.h"

#define NULLITEM 6553526



__interface MovableItem{
	virtual bool isMoving();
	virtual void setMoving(bool in);

	virtual void saveOldPos(float x, float y);
	virtual POINTFLOAT getOldcur();
	virtual POINTFLOAT getGap();
	virtual void moveTo(float x, float y);

	virtual bool isInside(float x, float y);
};

// ������ �ϳ��ϳ��� ��ư
// �������� �ϳ��� �����ͷθ� �����ϰ� ������ �ʿ�� ����
// ������ �ʿ䰡 ���涧�� UI�ν� ��µǾ�����
__interface IItem : public MovableItem{
	// Ÿ�� ������
	virtual void setType(int type, int id);
	virtual int getType();

	// ��ưó�� ���ýÿ� ��Ƽ���ս÷� ����
	//virtual void setActivate();
	//virtual void setSelected();

	virtual void Init();
	virtual void Render();
	virtual void Update(float);
	
	// ����
	virtual void itemOnEffect(ICharacter*);
	virtual void setEffect(EFFECT);
	virtual void setEffect(float, float, float, float, float, float);

	virtual void setAmount(int);
	virtual int getAmount();
	virtual int getID();
	virtual void setID(int in);

	virtual void setPos(float, float);
	virtual VECTOR2D* getPos();

	virtual bool isSelected();
	virtual bool isActivated();
	virtual void setSelected(bool in);
	virtual void setActivated(bool in);
};


// �κ��丮 UI
__interface IItemInventory {
	// ���콺�� ��� �ű涧
	virtual void Init();
	virtual void update(float);
	virtual void render();
	
	// �߰��� ������� ������ �߰�
	virtual void addToInventroy(IItem* item);
	virtual void removeFromInventory(int Iterator);
	
	// ���� ������ ���� ����
	virtual void changeOrder(int from, int to);

	// Ű����� �����϶� �̵���
	virtual void setCursor(int in);
	virtual int getCursor();

	// Ȱ��ȭ�� ������Ʈ �޾ƿͼ� ����
	virtual void setActivate();
	virtual void setSelected();
};

// UI_inventory ���� ���