#include "stdafx.h"
#include "mItem.h"

mItem::mItem()
{
	m_nType = 0;
	m_sEffect = { 0, };
	m_nAmount = 0;
}


mItem::~mItem()
{
}

mItem::mItem(int type, int id, Effect effectinput){
	m_nType = type;
	m_nID = id;
	m_sEffect = effectinput;
}

void mItem::Init(){

}

void mItem::Update(float delta){	
	// 각 mItem이 doubleclick됬을 경우 아이템 사용, 클릭앤 드래그 했을 경우 이동하게
	// 드롭시에 벨트 위에 드롭했을 경우 해당 칸에 포인터 입력
	// 만약 벨트위에 드롭이 아닐 경우 노띵해픈
}

void mItem::Render(){
	// 차후 각 mItem에 render를 넣어서, position에 따라서 렌더링하게 처리
}

// 타입 수정시
void mItem::setType(int type, int id){
	m_nType = type;
	m_nID = id;
}

int mItem::getType(){
	return m_nType;
}

void mItem::setEffect(EFFECT input){
	m_sEffect = input;
}

void mItem::setEffect(float hp, float mp, float attack, float attackspeed, float defense, float movespeed){
	//
	m_sEffect.HP = hp;
	m_sEffect.MP = mp;
	m_sEffect.Attack = attack;
	m_sEffect.AttackSpeed = attackspeed;
	m_sEffect.Defense = defense;
	m_sEffect.MoveSpeed = movespeed;
}

// 사용시
void mItem::itemOnEffect(ICharacter* character){
	if (m_nAmount > 0){
		if (m_nType == ITEM_CONSUME){
			float currentHP = character->getHealth() + m_sEffect.HP;
			if (currentHP > character->getMAXHealth()){
				currentHP = character->getMAXHealth();
			}

			float currentMP = character->getMP() + m_sEffect.MP;
			if (currentMP > character->getMaxMp()){
				currentMP = character->getMaxMp();
			}

			character->setHealth(currentHP);
			character->setMP(currentMP);
			// Consume일 경우 나중에 지속시간을 정한다.
			//TODO: Attack
			//TODO: attack speed
			character->setDefense(character->getDefense() + m_sEffect.Defense);
			character->setMoveSpeed(character->getMoveSpeed() + m_sEffect.MoveSpeed);
		}
		else if (m_nType == ITEM_EQUIPMENT){
			character->setMAXHealth(character->getHealth() + m_sEffect.HP);
			character->setMaxMp(character->getMaxMp() + m_sEffect.MP);
			//TODO: Equipment일 경우 영구적인 부분을 정한다.
			//TODO: Equipment일 경우에는 장비 해제 같은 경우의 수도 있기 때문에 
			//		off effect도 만들어줘야 할듯 하다.
			//		혹은 클래스 분화를 통해 분화하는 것도 생각해봐야 할듯.
			//TODO: Attack
			//TODO: attack speed
			character->setDefense(character->getDefense() + m_sEffect.Defense);
			character->setMoveSpeed(character->getMoveSpeed() + m_sEffect.MoveSpeed);
		}
	}
}