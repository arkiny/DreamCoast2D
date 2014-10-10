#pragma once
#include "IGObject.h"

enum ITEM_TYPE
{
	ITEM_EQUIPMENT,		// effect to static stat
	ITEM_CONSUME,		// effect to current stat
	ITEM_TYPE_MAX
};

enum ITEM_CONSUME_ID
{
	ITEM_POTION_HEALTH_SMALL,	// potion effect
	ITEM_POTION_HEALTH_BIG,		// potion effect
	ITEM_CONSUME_MAX
};

enum ITEM_EQUIP_ID
{
	ITEM_SWORD_ARMINGSWORD,
	ITEM_SWORD_BASTARDSWORD,
	ITEM_EQUIP_MAX
};

typedef struct Effect
{
	float HP;
	float MP;
	float Attack;
	float AttackSpeed;
	float Defense;
	float MoveSpeed;
}EFFECT, *LPEFFECT;

static EFFECT Item_Equip_DB[ITEM_EQUIP_MAX] = {
		{ 0, 0, 100.0f, 0, 0, 0 },
		{ 0, 0, 200.0f, 0, 0, 0 }
};

static EFFECT Item_Consume_DB[ITEM_CONSUME_MAX] =
{
	{ 100, 0, 0, 0, 0, 0 },	//ITEM_POTION_HEALTH_SMALL
	{ 200, 0, 0, 0, 0, 0 }	//ITEM_POTION_HEALTH_BIG
};

// ������ �ϳ��ϳ��� ��ư
// �������� �ϳ��� �����ͷθ� �����ϰ� ������ �ʿ�� ����
// ������ �ʿ䰡 ���涧�� UI�ν� ��µǾ�����
__interface IItem {
	// Ÿ�� ������
	virtual void setType(int type);
	virtual int getType();

	// ��ưó�� ���ýÿ� ��Ƽ���ս÷� ����
	//virtual void setActivate();
	//virtual void setSelected();
	
	// ����
	virtual void itemOnEffect(ICharacter*);
	virtual void setEffect(EFFECT);
	virtual void setEffect(float, float, float, float, float, float);

	virtual void setAmount(int);
	virtual int getAmount();
};


// �κ��丮 UI
__interface IItemInventory {
	// ���콺�� ��� �ű涧
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