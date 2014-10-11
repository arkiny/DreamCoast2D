#pragma once
#include "IInventory.h"

class mInventory : public IInventory
{
public:
	mInventory();
	virtual ~mInventory();
	virtual std::map<int, mItem*> getInventory();
	virtual void addToInventory(mItem*);
	virtual void removeFromInventory(int ID);


	// weapon (����, ���ݷ�)
	// �����ϰ� �ִ� ���⸦ ����� ������ ���⸦ �����.
	virtual void equipWeapon(mItem*){}
	virtual mItem* getCurrentWeapon(){ return 0; }
	// armor (����)
	// �����ϰ� �ִ� ������ ����� ������ ���ʸ� �����.
	virtual void equipArmor(mItem*){}
	virtual mItem* getCurrentArmor(){ return 0; }
	// shoes (�̵��ӵ�)
	// �����ϰ� �ִ� �Ź��� ����� ������ �Ź��� �Ŵ´�.
	virtual void equipShoes(mItem*){}
	virtual mItem* getCurrentShoes(){ return 0; }

private:
	std::map<int, mItem*> m_vInventory;
};

