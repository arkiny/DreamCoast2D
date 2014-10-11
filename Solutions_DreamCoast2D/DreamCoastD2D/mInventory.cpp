#include "stdafx.h"
#include "mInventory.h"
#include "mItem.h"


mInventory::mInventory()
{
}


mInventory::~mInventory()
{
}



std::map<int, mItem*> mInventory::getInventory(){
	return m_vInventory;
}

void mInventory::addToInventory(mItem* item){
	if (m_vInventory.count(item->getID()) >= 1){
		mItem* ptr = m_vInventory.at(item->getID());
		ptr->setAmount(item->getAmount() + ptr->getAmount());
		ptr = nullptr;
	}
	else {
		m_vInventory.insert(std::pair<int, mItem*>(item->getID(), item));
	}
}

void mInventory::removeFromInventory(int ID){
	if (m_vInventory.count(ID) >= 1){
		// 해당 아이디의 아이템이 존재하고 1번이상 사용 가능하다면
		mItem* ptr = m_vInventory.at(ID);
		if (ptr->getAmount() > 2){
			ptr->setAmount(ptr->getAmount() - 1);
		}
		else {
			// 1번 사용할양만 남았거나, 안남았다면
			// 하지만 equipment는 사용되었다는 체킹만하고 사라지지 않게 처리...
			mItem* ptr = m_vInventory.at(ID);
			m_vInventory.erase(ID);
			delete ptr;
		}
	}
}