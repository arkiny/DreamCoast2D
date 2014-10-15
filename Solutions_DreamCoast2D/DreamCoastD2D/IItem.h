#pragma once
#include "IGObject.h"

#define NULLITEM 6553526

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
	ITEM_POTION_HEALTH_1,		// potion effect
	ITEM_POTION_HEALTH_2,		// potion effect
	ITEM_POTION_HEALTH_3,		// potion effect
	ITEM_POTION_HEALTH_4,		// potion effect
	ITEM_POTION_MANA_SMALL,
	ITEM_POTION_MANA_BIG,
	ITEM_POTION_MANA_1,
	ITEM_POTION_MANA_2,
	ITEM_POTION_MANA_3,
	ITEM_POTION_MANA_4,
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
	{ 200, 0, 0, 0, 0, 0 },	//ITEM_POTION_HEALTH_BIG
	{ 300, 0, 0, 0, 0, 0 }, //ITEM_POTION_HEALTH_1
	{ 400, 0, 0, 0, 0, 0 }, //ITEM_POTION_HEALTH_2
	{ 500, 0, 0, 0, 0, 0 }, //ITEM_POTION_HEALTH_3
	{ 600, 0, 0, 0, 0, 0 }, //ITEM_POTION_HEALTH_4
	{ 0, 10, 0, 0, 0, 0 }, //ITEM_POTION_MANA_SMALL,
	{ 0, 20, 0, 0, 0, 0 }, //ITEM_POTION_MANA_BIG,
	{ 0, 30, 0, 0, 0, 0 }, //ITEM_POTION_MANA_1,
	{ 0, 40, 0, 0, 0, 0 }, //ITEM_POTION_MANA_2,
	{ 0, 50, 0, 0, 0, 0 }, //ITEM_POTION_MANA_3,
	{ 0, 100, 0, 0, 0, 0 }, //ITEM_POTION_MANA_4,
};

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