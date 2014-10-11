#include "stdafx.h"
#include "uiBelt.h"
#include "mPlayer.h"
#include "cResourceManager.h"
#include "VECTOR2D.h"
#include "mItem.h"
#include "coControl.h"
#include "IInventory.h"

uiBelt::uiBelt()
{
	this->setPos(new VECTOR2D(20.0f, 40.0f));
}

uiBelt::uiBelt(ICharacter* player){
	this->setPos(new VECTOR2D(20.0f, 40.0f));
	m_player = player;
}

uiBelt::~uiBelt()
{
}

void uiBelt::OnInit(){

}

void uiBelt::Update(float){
	// 차후 벨트 포인터 갱신 포션 이동시나 그럴시에
	mPlayer* ptr = (mPlayer*)m_player;
	/// item belt
	if (::coControl::GetInstance().getKeyControlInfo()[0x41]){
		::coControl::GetInstance().onKeyUp(0x41);
		if (ptr->getBelt(KEY_A)!= nullptr){
			ptr->getBelt(KEY_A)->itemOnEffect(m_player);
			int in = ptr->getBelt(KEY_A)->getAmount() - 1;
			ptr->getBelt(KEY_A)->setAmount(in);

			if (ptr->getBelt(KEY_A)->getAmount() == 0){
				ptr->getInventory()->removeFromInventory(ptr->getBelt(KEY_A)->getID());
				//getInventory().at(ptr->getBelt(KEY_A)->getID());
				//m_Inventory->getInventory().erase(m_aBelt[KEY_A]->getID());
				//delete ptr;
				ptr->setBelt(KEY_A, nullptr);
			}
		}
	}
	else if (::coControl::GetInstance().getKeyControlInfo()[0x53]){
		::coControl::GetInstance().onKeyUp(0x53);
		if (ptr->getBelt(KEY_S) != nullptr){
			ptr->getBelt(KEY_S)->itemOnEffect(m_player);
			int in = ptr->getBelt(KEY_S)->getAmount() - 1;
			ptr->getBelt(KEY_S)->setAmount(in);

			if (ptr->getBelt(KEY_S)->getAmount() == 0){
				ptr->getInventory()->removeFromInventory(ptr->getBelt(KEY_S)->getID());
				//getInventory().at(ptr->getBelt(KEY_A)->getID());
				//m_Inventory->getInventory().erase(m_aBelt[KEY_A]->getID());
				//delete ptr;
				ptr->setBelt(KEY_S, nullptr);
			}
		}
	}
	else if (::coControl::GetInstance().getKeyControlInfo()[0x44]){
		::coControl::GetInstance().onKeyUp(0x44);
		if (ptr->getBelt(KEY_S) != nullptr){
			ptr->getBelt(KEY_S)->itemOnEffect(m_player);
			int in = ptr->getBelt(KEY_S)->getAmount() - 1;
			ptr->getBelt(KEY_S)->setAmount(in);

			if (ptr->getBelt(KEY_S)->getAmount() == 0){
				ptr->getInventory()->removeFromInventory(ptr->getBelt(KEY_S)->getID());
				//getInventory().at(ptr->getBelt(KEY_A)->getID());
				//m_Inventory->getInventory().erase(m_aBelt[KEY_A]->getID());
				//delete ptr;
				ptr->setBelt(KEY_S, nullptr);
			}
		}
	}
	///
}

void uiBelt::Render(){
	::RECT winRect;
	GetClientRect(::cD2DRenderer::GetInstance().GetHwnd(), &winRect);

	mPlayer* ptr = (mPlayer*)m_player;

	/// TOdo, 차후 리소스화
	wchar_t* wszText_ = new wchar_t[20];
	if (ptr->getBelt(0) != nullptr){
		swprintf(wszText_, 20, L"%d",
			ptr->getBelt(0)->getAmount());
		UINT32 cTextLength_ = (UINT32)wcslen(wszText_);

		D2D1_RECT_F layoutRect = D2D1::RectF(
			this->getPos()->x + 5.0f,
			winRect.bottom - this->getPos()->y - ::cResourceManager::GetInstance().getUISize(UIID::UI_BELT).y + 6.0f,
			this->getPos()->x + 59.0f,
			winRect.bottom - this->getPos()->y - ::cResourceManager::GetInstance().getUISize(UIID::UI_BELT).y + 60.0f
			);

		// draw text
		::cD2DRenderer::GetInstance().GetRenderTarget()->DrawTextW(
			wszText_,
			cTextLength_,
			::cD2DRenderer::GetInstance().GetTextFormat(),
			layoutRect,
			::cD2DRenderer::GetInstance().GetWhiteBrush());
	}

	if (ptr->getBelt(1) != nullptr){
		swprintf(wszText_, 20, L"%d",
			ptr->getBelt(1)->getAmount());
		UINT32 cTextLength_ = (UINT32)wcslen(wszText_);

		D2D1_RECT_F layoutRect = D2D1::RectF(
			this->getPos()->x + 70.0f,
			winRect.bottom - this->getPos()->y - ::cResourceManager::GetInstance().getUISize(UIID::UI_BELT).y + 6.0f,
			this->getPos()->x + 124.0f,
			winRect.bottom - this->getPos()->y - ::cResourceManager::GetInstance().getUISize(UIID::UI_BELT).y + 60.0f
			);

		// draw text
		::cD2DRenderer::GetInstance().GetRenderTarget()->DrawTextW(
			wszText_,
			cTextLength_,
			::cD2DRenderer::GetInstance().GetTextFormat(),
			layoutRect,
			::cD2DRenderer::GetInstance().GetWhiteBrush());
	}

	if (ptr->getBelt(2) != nullptr){
		swprintf(wszText_, 20, L"%d",
			ptr->getBelt(2)->getAmount());
		UINT32 cTextLength_ = (UINT32)wcslen(wszText_);

		D2D1_RECT_F layoutRect = D2D1::RectF(
			this->getPos()->x + 137.0f,
			winRect.bottom - this->getPos()->y - ::cResourceManager::GetInstance().getUISize(UIID::UI_BELT).y + 6.0f,
			this->getPos()->x + 191.0f,
			winRect.bottom - this->getPos()->y - ::cResourceManager::GetInstance().getUISize(UIID::UI_BELT).y + 60.0f
			);

		// draw text
		::cD2DRenderer::GetInstance().GetRenderTarget()->DrawTextW(
			wszText_,
			cTextLength_,
			::cD2DRenderer::GetInstance().GetTextFormat(),
			layoutRect,
			::cD2DRenderer::GetInstance().GetWhiteBrush());
	}
	///

	if (::cResourceManager::GetInstance().getUIBitMap(UIID::UI_BELT) != nullptr){
		::D2D1_RECT_F dxArea
			= { this->getPos()->x, 
			winRect.bottom - this->getPos()->y - ::cResourceManager::GetInstance().getUISize(UIID::UI_BELT).y,
			this->getPos()->x + ::cResourceManager::GetInstance().getUISize(UIID::UI_BELT).x,
			winRect.bottom - this->getPos()->y};
		::D2D1_RECT_F srcArea
			= { 0, 0, 
			::cResourceManager::GetInstance().getUISize(UIID::UI_BELT).x, 
			::cResourceManager::GetInstance().getUISize(UIID::UI_BELT).y };

		::cD2DRenderer::GetInstance().GetRenderTarget()
			->DrawBitmap(::cResourceManager::GetInstance().getUIBitMap(UIID::UI_BELT), dxArea, 1.0f,
			D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
			srcArea);
	}
}