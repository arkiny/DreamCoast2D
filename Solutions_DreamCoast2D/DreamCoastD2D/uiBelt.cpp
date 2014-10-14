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
	// �� ��ư ���� Ŭ����
	// �� ��ư ���� ������Ʈ
	// if (A button Area){
	// ::coControl::GetInstance().onKeyDown(0x41);
	// }

	// ���� ��Ʈ ������ ���� ���� �̵��ó� �׷��ÿ�
	mPlayer* ptr = (mPlayer*)m_player;
	/// item belt
	if (::coControl::GetInstance().getKeyControlInfo()[0x41]){
		::coControl::GetInstance().onKeyUp(0x41);
		if (ptr->getBelt(KEY_A) != NULLITEM){
			ptr->getInventory()->getInventory().at(ptr->getBelt(KEY_A))->itemOnEffect(m_player);
			int in = ptr->getInventory()->getInventory().at(ptr->getBelt(KEY_A))->getAmount() - 1;
			ptr->getInventory()->getInventory().at(ptr->getBelt(KEY_A))->setAmount(in);

			if (ptr->getInventory()->getInventory().at(ptr->getBelt(KEY_A))->getAmount() == 0){
				ptr->getInventory()->removeFromInventory(ptr->getBelt(KEY_A));
				//getInventory().at(ptr->getBelt(KEY_A)->getID());
				//m_Inventory->getInventory().erase(m_aBelt[KEY_A]->getID());
				//delete ptr;
				ptr->setBelt(KEY_A, NULLITEM);
			}
		}
	}
	else if (::coControl::GetInstance().getKeyControlInfo()[0x53]){
		::coControl::GetInstance().onKeyUp(0x53);
		if (ptr->getBelt(KEY_S) != NULLITEM){
			ptr->getInventory()->getInventory().at(ptr->getBelt(KEY_S))->itemOnEffect(m_player);
			int in = ptr->getInventory()->getInventory().at(ptr->getBelt(KEY_S))->getAmount() - 1;
			ptr->getInventory()->getInventory().at(ptr->getBelt(KEY_S))->setAmount(in);

			if (ptr->getInventory()->getInventory().at(ptr->getBelt(KEY_S))->getAmount() == 0){
				ptr->getInventory()->removeFromInventory(ptr->getBelt(KEY_S));
				//getInventory().at(ptr->getBelt(KEY_A)->getID());
				//m_Inventory->getInventory().erase(m_aBelt[KEY_A]->getID());
				//delete ptr;
				ptr->setBelt(KEY_S, NULLITEM);
			}
		}
	}
	else if (::coControl::GetInstance().getKeyControlInfo()[0x44]){
		::coControl::GetInstance().onKeyUp(0x44);
		if (ptr->getBelt(KEY_D) != NULLITEM){
			ptr->getInventory()->getInventory().at(ptr->getBelt(KEY_D))->itemOnEffect(m_player);
			int in = ptr->getInventory()->getInventory().at(ptr->getBelt(KEY_D))->getAmount() - 1;
			ptr->getInventory()->getInventory().at(ptr->getBelt(KEY_D))->setAmount(in);

			if (ptr->getInventory()->getInventory().at(ptr->getBelt(KEY_D))->getAmount() == 0){
				ptr->getInventory()->removeFromInventory(ptr->getBelt(KEY_D));
				//getInventory().at(ptr->getBelt(KEY_A)->getID());
				//m_Inventory->getInventory().erase(m_aBelt[KEY_A]->getID());
				//delete ptr;
				ptr->setBelt(KEY_D, NULLITEM);
			}
		}
	}
	///
}

void uiBelt::Render(){
	::RECT winRect;
	GetClientRect(::cD2DRenderer::GetInstance().GetHwnd(), &winRect);

	mPlayer* ptr = (mPlayer*)m_player;

	/// TOdo, ���� ���ҽ�ȭ
	wchar_t* wszText_ = new wchar_t[20];
	int length = 0;
	length += swprintf(wszText_ + length, 20, L"");
	swprintf(wszText_, 20, L"");

	// release������ ������ �ȵǴµ� ����׿��� �ͼ����� ����.
	// ���� �Ƚ��ؾ���
	//if (ptr->getBelt(0) == NULL || ptr->getBelt(0) == nullptr){
	//	int i = 0;
	//}

	if (ptr->getBelt(0) != NULLITEM){
		swprintf(wszText_, 20, L"%d",
			ptr->getInventory()->getInventory().at(ptr->getBelt(KEY_A))->getAmount());
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

	if (ptr->getBelt(1) != NULLITEM){
		swprintf(wszText_, 20, L"%d",
			ptr->getInventory()->getInventory().at(ptr->getBelt(KEY_S))->getAmount());
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

	if (ptr->getBelt(2) != NULLITEM){
		swprintf(wszText_, 20, L"%d",
			ptr->getInventory()->getInventory().at(ptr->getBelt(KEY_D))->getAmount());
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