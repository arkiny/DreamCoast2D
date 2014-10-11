#pragma once

#include <map>

class mItem;
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

__interface IInventory : public IEquippedInven{
	virtual std::map<int, mItem*> getInventory();
	virtual void addToInventory(mItem*);
	virtual void removeFromInventory(int ID);
};