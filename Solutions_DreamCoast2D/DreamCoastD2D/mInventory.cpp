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
		// �ش� ���̵��� �������� �����ϰ� 1���̻� ��� �����ϴٸ�
		mItem* ptr = m_vInventory.at(ID);
		if (ptr->getAmount() > 2){
			ptr->setAmount(ptr->getAmount() - 1);
		}
		else {
			// 1�� ����Ҿ縸 ���Ұų�, �ȳ��Ҵٸ�
			// ������ equipment�� ���Ǿ��ٴ� üŷ���ϰ� ������� �ʰ� ó��...
			mItem* ptr = m_vInventory.at(ID);
			m_vInventory.erase(ID);
			delete ptr;
		}
	}
}