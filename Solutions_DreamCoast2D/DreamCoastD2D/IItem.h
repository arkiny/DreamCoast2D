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
	ITEM_POTION_MANA_SMALL,
	ITEM_POTION_MANA_BIG,
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
	{ 0, 100, 0, 0, 0, 0 }, //ITEM_POTION_MANA_SMALL,
	{ 0, 200, 0, 0, 0, 0 }  //ITEM_POTION_MANA_BIG,
};

// 아이템 하나하나가 버튼
// 아이템은 하나의 데이터로만 존재하고 렌더할 필요는 없다
// 렌더할 필요가 생길때는 UI로써 출력되었을때
__interface IItem {
	// 타입 수정시
	virtual void setType(int type, int id);
	virtual int getType();

	// 버튼처럼 선택시와 액티베잇시로 나눔
	//virtual void setActivate();
	//virtual void setSelected();

	virtual void Init();
	virtual void Render();
	virtual void Update(float);
	
	// 사용시
	virtual void itemOnEffect(ICharacter*);
	virtual void setEffect(EFFECT);
	virtual void setEffect(float, float, float, float, float, float);

	virtual void setAmount(int);
	virtual int getAmount();
	virtual int getID();
	virtual void setID(int in);
};


// 인벤토리 UI
__interface IItemInventory {
	// 마우스로 들어 옮길때
	virtual void update(float);
	virtual void render();
	
	// 추가된 순서대로 아이템 추가
	virtual void addToInventroy(IItem* item);
	virtual void removeFromInventory(int Iterator);
	
	// 차후 구현할 순서 변경
	virtual void changeOrder(int from, int to);

	// 키보드로 움직일때 이동용
	virtual void setCursor(int in);
	virtual int getCursor();

	// 활성화시 업데이트 받아와서 렌더
	virtual void setActivate();
	virtual void setSelected();
};

// UI_inventory 따로 출력