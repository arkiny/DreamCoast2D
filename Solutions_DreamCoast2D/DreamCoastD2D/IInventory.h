#pragma once

#include <map>

class mItem;
//class ICharacter;
__interface IEquippedInven{
	// weapon (����, ���ݷ�)
	// �����ϰ� �ִ� ���⸦ ����� ������ ���⸦ �����.
	virtual void equipWeapon(mItem*);
	virtual mItem* getCurrentWeapon();
	// armor (����)
	// �����ϰ� �ִ� ������ ����� ������ ���ʸ� �����.
	virtual void equipArmor(mItem*);
	virtual mItem* getCurrentArmor();
	// shoes (�̵��ӵ�)
	// �����ϰ� �ִ� �Ź��� ����� ������ �Ź��� �Ŵ´�.
	virtual void equipShoes(mItem*);
	virtual mItem* getCurrentShoes();
};

//__interface IBelt{
//	virtual void setBelt(int beltID, int itemID);
//	virtual void usingBelt(int beltID);
//	virtual void removeFromBelt(int beltID);
//};

__interface IInventory : public IEquippedInven{
	virtual std::map<int, mItem*>* getInventory();
	virtual void addToInventory(mItem*);
	virtual void removeFromInventory(int ID);
	virtual void removeFromInventory(int ID, int amount);
};