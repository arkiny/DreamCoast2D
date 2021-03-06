#include "stdafx.h"
#include "mItem.h"
#include "VECTOR2D.h"
#include "cD2DRenderer.h"
#include "cResourceManager.h"
#include "coControl.h"

// drag and drop reference
//https://github.com/arkiny/SGA-Learning-Heedong/blob/master/WinAPI/Porfolio/DreamCoastEngine/DreamCoastEngine%20Basic/DreamCoastEngine%20Basic.cpp
//

mItem::mItem()
{
	m_nType = 0;
	m_sEffect = { 0, };
	m_nAmount = 0;
	m_vPos = new VECTOR2D(0.0f, 0.0f);
	m_fWidth = 40.0f;
	m_fHeight = 40.0f;
}


mItem::~mItem()
{
	delete  m_vPos;
}

mItem::mItem(int type, int id, Effect effectinput){
	m_nType = type;
	m_nID = id;
	m_sEffect = effectinput;
	m_vPos = new VECTOR2D(0.0f, 0.0f);
	m_fWidth = 40.0f;
	m_fHeight = 40.0f;
}

void mItem::Init(){
	
}

void mItem::Update(float delta){	
	// �� mItem�� doubleclick���� ��� ������ ���, Ŭ���� �巡�� ���� ��� �̵��ϰ�
	// ��ӽÿ� ��Ʈ ���� ������� ��� �ش� ĭ�� ������ �Է� �� onBelt Ȱ��ȭ
	
	// ���� ��Ʈ���� ����� �ƴ� ��� �������

	POINTFLOAT mousepoint = ::coControl::GetInstance().getMousePosition();
	

	if (mItem::isInside(mousepoint.x, mousepoint.y)){
		this->setSelected(true);
		if (::coControl::GetInstance().getKeyControlInfo()[VK_RBUTTON]){
			::coControl::GetInstance().onKeyUp(VK_RBUTTON);
			this->setActivated(true);
		}
		else {
			this->setActivated(false);
		}

		if (::coControl::GetInstance().getKeyControlInfo()[VK_LBUTTON] && m_bIsMoving == false
			&& mItem::isInside(::coControl::GetInstance().getClickPosition().x, ::coControl::GetInstance().getClickPosition().y)){
			POINTFLOAT clickpoint = ::coControl::GetInstance().getClickPosition();
			::mItem::saveOldPos(clickpoint.x, clickpoint.y);
			this->setMoving(true);
		}
	}
	else
	{
		this->setSelected(false);
	}
}

void mItem::Render(){
	// if inventory�� �����ϱ� �����ϸ� �����Ѵ�.
	// ���� �� mItem�� render�� �־, position�� ���� �������ϰ� ó��
	// onBelt�� true�϶� ��� ��Ʈ ��ġ(a,s,d)�� ��������� �Ѵ�.
	D2D1_RECT_F itemRect = D2D1::RectF(
		m_vPos->x,
		m_vPos->y,
		m_vPos->x + 40.0f,
		m_vPos->y + 40.0f
		);

	::cD2DRenderer::GetInstance().GetRenderTarget()->FillRectangle(itemRect, ::cD2DRenderer::GetInstance().GetWhiteBrush());
	::cD2DRenderer::GetInstance().GetRenderTarget()->DrawRectangle(itemRect, ::cD2DRenderer::GetInstance().GetBlackBrush());

	if (::cResourceManager::GetInstance().getConsumeItemBitMap(m_nID) != nullptr){
		::D2D1_RECT_F dxArea
			= { this->getPos()->x, this->getPos()->y, this->getPos()->x + m_fWidth, this->getPos()->y + m_fHeight };
		::D2D1_RECT_F srcArea
			= { 0, 0,
			::cResourceManager::GetInstance().getConsumeItemUISize(m_nID).x,
			::cResourceManager::GetInstance().getConsumeItemUISize(m_nID).y };

		::cD2DRenderer::GetInstance().GetRenderTarget()
			->DrawBitmap(::cResourceManager::GetInstance().getConsumeItemBitMap(m_nID), dxArea, 1.0f,
			D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
			srcArea);
	}

	wchar_t* wszText_ = new wchar_t[20];

	int length = 0;
	length += swprintf(wszText_ + length, 20, L"%d/%d", m_nID, m_nAmount);
	UINT32 cTextLength_ = (UINT32)wcslen(wszText_);

	// draw text
	::cD2DRenderer::GetInstance().GetRenderTarget()->DrawTextW(
		wszText_,
		cTextLength_,
		::cD2DRenderer::GetInstance().GetTextFormat(),
		itemRect,
		::cD2DRenderer::GetInstance().GetWhiteBrush());	

	delete[] wszText_;
}

// Ÿ�� ������
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

// ����
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
}

void mItem::setPos(float x, float y){
	m_vPos->x = x;
	m_vPos->y = y;
}

VECTOR2D* mItem::getPos(){
	return m_vPos;
}

void mItem::saveOldPos(float x, float y){
	m_fMB_cache_old = { m_vPos->x, m_vPos->y };
	m_fMB_cache_gap = { x - m_vPos->x, y - m_vPos->y };
}

void mItem::moveTo(float x, float y){
	m_vPos->x = x - m_fMB_cache_gap.x;
	m_vPos->y = y - m_fMB_cache_gap.y;
}

bool mItem::isInside(float mousex, float mousey){
	return (mousex >= this->getPos()->x &&
		mousey >= this->getPos()->y &&
		mousex <= (this->getPos()->x + m_fWidth) &&
		mousey <= (this->getPos()->y + m_fHeight));
}