#include "stdafx.h"
#include "mItem.h"

mItem::mItem()
{
	m_nType = 0;
	m_sEffect = { 0, };
}


mItem::~mItem()
{
}

mItem::mItem(int type, Effect effectinput){
	m_nType = type;
	m_sEffect = effectinput;
}
// Ÿ�� ������
void mItem::setType(int type){
	m_nType = type;
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

// ����
void mItem::itemOnEffect(ICharacter* character){
	if (m_nType == ITEM_CONSUME){
		character->setHealth(character->getHealth() + m_sEffect.HP);
		character->setMP(character->getMP() + m_sEffect.MP);
		// Consume�� ��� ���߿� ���ӽð��� ���Ѵ�.
		//TODO: Attack
		//TODO: attack speed
		character->setDefense(character->getDefense() + m_sEffect.Defense);
		character->setMoveSpeed(character->getMoveSpeed() + m_sEffect.MoveSpeed);
	}
	else if (m_nType == ITEM_EQUIPMENT){
		character->setMAXHealth(character->getHealth() + m_sEffect.HP);
		character->setMaxMp(character->getMaxMp() + m_sEffect.MP);
		//TODO: Equipment�� ��� �������� �κ��� ���Ѵ�.
		//TODO: Equipment�� ��쿡�� ��� ���� ���� ����� ���� �ֱ� ������ 
		//		off effect�� �������� �ҵ� �ϴ�.
		//		Ȥ�� Ŭ���� ��ȭ�� ���� ��ȭ�ϴ� �͵� �����غ��� �ҵ�.
		//TODO: Attack
		//TODO: attack speed
		character->setDefense(character->getDefense() + m_sEffect.Defense);
		character->setMoveSpeed(character->getMoveSpeed() + m_sEffect.MoveSpeed);
	}
}