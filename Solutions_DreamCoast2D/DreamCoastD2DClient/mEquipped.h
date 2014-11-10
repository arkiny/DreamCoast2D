#pragma once
#include "IInventory.h"
class mEquipped : public IEquippedInven
{
public:
	mEquipped();
	virtual ~mEquipped();
	// weapon (����, ���ݷ�)
	// �����ϰ� �ִ� ���⸦ ����� ������ ���⸦ �����.
	virtual void equipWeapon(mItem* in){
		m_currentWeapon = in;
	}
	virtual mItem* getCurrentWeapon(){
		return m_currentWeapon;
	};
	// armor (����)
	// �����ϰ� �ִ� ������ ����� ������ ���ʸ� �����.
	virtual void equipArmor(mItem* in){
		m_currentArmor = in;
	}
	virtual mItem* getCurrentArmor() {
		return m_currentArmor;
	}
	// shoes (�̵��ӵ�)
	// �����ϰ� �ִ� �Ź��� ����� ������ �Ź��� �Ŵ´�.
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

