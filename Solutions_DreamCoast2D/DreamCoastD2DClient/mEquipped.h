#pragma once
#include "IInventory.h"
class mEquipped : public IEquippedInven
{
public:
	mEquipped();
	virtual ~mEquipped();
	// weapon (공속, 공격력)
	// 장착하고 있는 무기를 벗기고 인자의 무기를 끼운다.
	virtual void equipWeapon(mItem* in){
		m_currentWeapon = in;
	}
	virtual mItem* getCurrentWeapon(){
		return m_currentWeapon;
	};
	// armor (방어력)
	// 장착하고 있는 갑옷을 벗기고 인자의 갑옷를 끼운다.
	virtual void equipArmor(mItem* in){
		m_currentArmor = in;
	}
	virtual mItem* getCurrentArmor() {
		return m_currentArmor;
	}
	// shoes (이동속도)
	// 장착하고 있는 신발을 벗기고 인자의 신발은 신는다.
	virtual void equipShoes(mItem* in){
		m_currentShoes = in;
	}
	virtual mItem* getCurrentShoes(){
		return m_currentShoes;
	}
private:
	mItem* m_currentWeapon;
	mItem* m_currentArmor;
	mItem* m_currentShoes;
};

