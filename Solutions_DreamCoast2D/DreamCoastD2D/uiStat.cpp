#include "stdafx.h"
#include "uiStat.h"
#include "coControl.h"
#include "VECTOR2D.h"
#include "cResourceManager.h"
#include "mPlayer.h"

uiStat::uiStat()
{
	this->setPos(new VECTOR2D(20.0f, 200.0f));
	this->setMoveRectangle({ this->getPos()->x + 4.0f, 
		this->getPos()->y + 0.0f, 
		this->getPos()->x + 54.0f, 
		this->getPos()->y + 13.0f });
}


uiStat::~uiStat()
{
}

uiStat::uiStat(ICharacter* in){
	m_player = in;
	this->setPos(new VECTOR2D(20.0f, 200.0f));
	this->setMoveRectangle({ this->getPos()->x + 4.0f,
		this->getPos()->y + 0.0f,
		this->getPos()->x + 54.0f,
		this->getPos()->y + 13.0f });
}

void uiStat::OnInit(){
	this->setActivated(false);
}

void uiStat::Update(float delta){
	// c키로 캐릭터 info창 불러오기
	if (coControl::GetInstance().getKeyControlInfo()[0x43]){
		coControl::GetInstance().onKeyUp(0x43);
		if (m_fdelaytime >= m_fKeydelay){
			if (this->isActivated() == false){
				this->setActivated(true);
			}
			else{
				this->setActivated(false);
			}
		}
		m_fdelaytime -= delta;
		if (m_fdelaytime <= 0){
			m_fdelaytime = m_fKeydelay;
		}
	}
	if (!coControl::GetInstance().getKeyControlInfo()[0x43]){
		m_fdelaytime = m_fKeydelay;
	}

	
	if (this->isActivated()){
		POINTFLOAT mousepoint = ::coControl::GetInstance().getMousePosition();
		if (this->isInside(mousepoint.x, mousepoint.y)){
			if (::coControl::GetInstance().getKeyControlInfo()[VK_LBUTTON] && this->isMoving() == false
				&& this->isInside(::coControl::GetInstance().getClickPosition().x, ::coControl::GetInstance().getClickPosition().y)){
				POINTFLOAT clickpoint = ::coControl::GetInstance().getClickPosition();
				this->saveOldPos(clickpoint.x, clickpoint.y);
				this->setMoving(true);
			}
		}
		else
		{
			this->setSelected(false);
		}
	}
}

void uiStat::Render(){
	if (this->isActivated()){
		if (::cResourceManager::GetInstance().getUIBitMap(UIID::UI_STAT) != nullptr){
			::D2D1_RECT_F dxArea
				= { this->getPos()->x,
				this->getPos()->y,
				this->getPos()->x + ::cResourceManager::GetInstance().getUISize(UIID::UI_STAT).x,
				this->getPos()->y + ::cResourceManager::GetInstance().getUISize(UIID::UI_STAT).y };
			::D2D1_RECT_F srcArea
				= { 0, 0,
				::cResourceManager::GetInstance().getUISize(UIID::UI_STAT).x,
				::cResourceManager::GetInstance().getUISize(UIID::UI_STAT).y };

			::cD2DRenderer::GetInstance().GetRenderTarget()
				->DrawBitmap(::cResourceManager::GetInstance().getUIBitMap(UIID::UI_STAT), dxArea, 1.0f,
				D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
				srcArea);
		}

		// stat 내용 출력
		mPlayer* playerPtr = (mPlayer*)m_player;

		wchar_t* wszText_ = new wchar_t[1028];

		int length = 0;
		length += swprintf(wszText_ + length, 1028, L"MaxHP : %.0f / Current HP : %.0f \r", playerPtr->getMAXHealth(), playerPtr->getHealth());
		length += swprintf(wszText_ + length, 1028, L"MaxMP : %.0f / Current MP : %.0f \r", playerPtr->getMaxMp(), playerPtr->getMP());
		length += swprintf(wszText_ + length, 1028, L"AttackPower : %.0f \r", playerPtr->getAttackPower());
		length += swprintf(wszText_ + length, 1028, L"AttackSpeed : %.0f \r", playerPtr->getAttackSpeed());
		length += swprintf(wszText_ + length, 1028, L"MoveSpeed : %.0f \r", playerPtr->getMoveSpeed());

		UINT32 cTextLength_ = (UINT32)wcslen(wszText_);

		D2D1_RECT_F layoutRect = D2D1::RectF(
			this->getPos()->x+10.0f,
			this->getPos()->y+40.0f,
			this->getPos()->x + ::cResourceManager::GetInstance().getUISize(UIID::UI_STAT).x,
			this->getPos()->y + ::cResourceManager::GetInstance().getUISize(UIID::UI_STAT).y
			);

		//debug
		//::cD2DRenderer::GetInstance().GetRenderTarget()->DrawRectangle(layoutRect, ::cD2DRenderer::GetInstance().GetBlackBrush());


		// draw text
		::cD2DRenderer::GetInstance().GetRenderTarget()->DrawTextW(
			wszText_,
			cTextLength_,
			::cD2DRenderer::GetInstance().GetTextFormat2(),
			layoutRect,
			::cD2DRenderer::GetInstance().GetBlackBrush());

	}
}

