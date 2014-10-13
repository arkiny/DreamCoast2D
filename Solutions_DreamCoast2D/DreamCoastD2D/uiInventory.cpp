#include "stdafx.h"
#include "uiInventory.h"
#include "VECTOR2D.h"
#include "cResourceManager.h"
#include "coControl.h"
#include "uiBelt.h"
#include "mPlayer.h"
#include "mItem.h"

uiInventory::uiInventory()
{
}


uiInventory::~uiInventory()
{
}


uiInventory::uiInventory(ICharacter* player){
	m_player = player;
	this->setPos(new VECTOR2D(20.0f, 350.0f));
}

void uiInventory::OnInit(){
	m_bActivated = false;
}

void uiInventory::Update(float delta){
	// 차후 여기에서 드래그엔 드랍?
	// 벨트에 올리기?
	// 사용 구현

	 //i키로 인벤토리 불러오기
	if (coControl::GetInstance().getKeyControlInfo()[0x49]){
		if (m_fdelaytime >= m_fKeydelay){
			if (m_bActivated == false){
				m_bActivated = true;
			}
			else{
				m_bActivated = false;
			}
		}
		m_fdelaytime -= delta;
		if (m_fdelaytime <= 0){
			m_fdelaytime = m_fKeydelay;
		}
	}
	if (!coControl::GetInstance().getKeyControlInfo()[0x49]){
		m_fdelaytime = m_fKeydelay;
	}	

	mPlayer* playerPtr = (mPlayer*)m_player;
	std::map<int, mItem*> inventory = playerPtr->getInventory()->getInventory();

	if (m_bActivated){
		for (std::map<int, mItem*>::iterator itr = inventory.begin(); itr != inventory.end(); itr++){
			itr->second->Update(delta);
			if (itr->second->isActivated()){
				itr->second->itemOnEffect(m_player);
				itr->second->setAmount(itr->second->getAmount() - 1);

				if (itr->second->getAmount() == 0){
					//
					for (int i = 0; i < BELT_MAX; i++){
						if (playerPtr->getBelt(i) != nullptr){
							if (playerPtr->getBelt(i)->getType() == itr->first){
								playerPtr->setBelt(i, nullptr);
							}
						}
					}
					//
					playerPtr->getInventory()->removeFromInventory(itr->first);					
				}				
			}
		}
	}
}

void uiInventory::Render(){
	if (m_bActivated){
		if (::cResourceManager::GetInstance().getUIBitMap(UIID::UI_INVENTORY) != nullptr){
			::D2D1_RECT_F dxArea
				= { this->getPos()->x,
				this->getPos()->y,
				this->getPos()->x + ::cResourceManager::GetInstance().getUISize(UIID::UI_INVENTORY).x,
				this->getPos()->y + ::cResourceManager::GetInstance().getUISize(UIID::UI_INVENTORY).y };
			::D2D1_RECT_F srcArea
				= { 0, 0,
				::cResourceManager::GetInstance().getUISize(UIID::UI_INVENTORY).x,
				::cResourceManager::GetInstance().getUISize(UIID::UI_INVENTORY).y };

			::cD2DRenderer::GetInstance().GetRenderTarget()
				->DrawBitmap(::cResourceManager::GetInstance().getUIBitMap(UIID::UI_INVENTORY), dxArea, 1.0f,
				D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
				srcArea);
		}

		// TODO: 현재는 각 아이템을 받아와서 글자로 표현하지만
		// 차후 각 mItem에 render를 넣어서, position에 따라서 렌더링하게 처리
		// 각 mItem이 doubleclick됬을 경우 아이템 사용, 클릭앤 드래그 했을 경우 이동하게
		// 드롭시에 벨트 위에 드롭했을 경우 해당 칸에 포인터 입력
		// 만약 벨트위에 드롭이 아닐 경우 노띵해픈

		mPlayer* playerPtr = (mPlayer*)m_player;
		std::map<int, mItem*> inventory = playerPtr->getInventory()->getInventory();

		wchar_t* wszText_ = new wchar_t[1028];

		int length = 0;
		length += swprintf(wszText_ + length, 1028, L"");
		int i = 0;
		for (std::map<int, mItem*>::iterator itr = inventory.begin(); itr != inventory.end(); itr++){

			itr->second->setPos(this->getPos()->x + 10.0f + (i*50.0f), this->getPos()->y + 20.0f);
			itr->second->Render();
			
			if (itr->first == 0){
				length += swprintf(wszText_ + length, 1028, L"HealthPotion / ");
			}
			else if (itr->first == 2){
				length += swprintf(wszText_ + length, 1028, L"ManaPotion / ");
			}
			length+= swprintf(wszText_+length, 1028, L"amount %d \n", itr->second->getAmount());

			i++;
		}		
		
		UINT32 cTextLength_ = (UINT32)wcslen(wszText_);
		
		D2D1_RECT_F layoutRect = D2D1::RectF(
			this->getPos()->x,
			this->getPos()->y,
			this->getPos()->x + ::cResourceManager::GetInstance().getUISize(UIID::UI_INVENTORY).x,
			this->getPos()->y + ::cResourceManager::GetInstance().getUISize(UIID::UI_INVENTORY).y
			);

		// draw text
		::cD2DRenderer::GetInstance().GetRenderTarget()->DrawTextW(
			wszText_,
			cTextLength_,
			::cD2DRenderer::GetInstance().GetTextFormat(),
			layoutRect,
			::cD2DRenderer::GetInstance().GetBlackBrush());
	}
}