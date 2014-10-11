#pragma once

#include <map>

class mItem;
__interface IEquippedInven{
	// weapon (공속, 공격력)
	// 장착하고 있는 무기를 벗기고 인자의 무기를 끼운다.
	virtual void equipWeapon(mItem*);
	virtual mItem* getCurrentWeapon();
	// armor (방어력)
	// 장착하고 있는 갑옷을 벗기고 인자의 갑옷를 끼운다.
	virtual void equipArmor(mItem*);
	virtual mItem* getCurrentArmor();
	// shoes (이동속도)
	// 장착하고 있는 신발을 벗기고 인자의 신발은 신는다.
	virtual void equipShoes(mItem*);
	virtual mItem* getCurrentShoes();
};

__interface IInventory : public IEquippedInven{
	virtual std::map<int, mItem*> getInventory();
	virtual void addToInventory(mItem*);
	virtual void removeFromInventory(int ID);
};