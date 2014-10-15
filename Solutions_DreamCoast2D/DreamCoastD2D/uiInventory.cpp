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


uiInventory::uiInventory(ICharacter* player, uiInterface* ubelt){
	m_player = player;
	m_belt = ubelt;;
	this->setPos(new VECTOR2D(20.0f, 350.0f));
	this->setMoveRectangle({2.0f,
		0.0f,
		54.0f,
		13.0f });
}

void uiInventory::OnInit(){
	this->setActivated(false);
	m_bMoving = NULLITEM;

	mPlayer* playerPtr = (mPlayer*)m_player;
	std::map<int, mItem*> inventory = playerPtr->getInventory()->getInventory();

	int i = 0;

	for (std::map<int, mItem*>::iterator itr = inventory.begin(); itr != inventory.end(); itr++){
		itr->second->setPos(this->getPos()->x + 10.0f + (i*50.0f), this->getPos()->y + 20.0f);
		i++;
	}

	m_nInventorySize = inventory.size();

}

void uiInventory::Update(float delta){
	// 차후 여기에서 드래그엔 드랍?
	// 벨트에 올리기?
	// 사용 구현

	 //i키로 인벤토리 불러오기
	if (coControl::GetInstance().getKeyControlInfo()[0x49]){
		coControl::GetInstance().onKeyUp(0x49);
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
	if (!coControl::GetInstance().getKeyControlInfo()[0x49]){
		m_fdelaytime = m_fKeydelay;
	}	

	mPlayer* playerPtr = (mPlayer*)m_player;
	std::map<int, mItem*> inventory = playerPtr->getInventory()->getInventory();

	if (this->isActivated()){
		//// window move
		//POINTFLOAT mousepoint = ::coControl::GetInstance().getMousePosition();
		//if (this->isInside(mousepoint.x, mousepoint.y)){
		//	if (::coControl::GetInstance().getKeyControlInfo()[VK_LBUTTON] && this->isMoving() == false
		//		&& this->isInside(::coControl::GetInstance().getClickPosition().x, ::coControl::GetInstance().getClickPosition().y)){
		//		POINTFLOAT clickpoint = ::coControl::GetInstance().getClickPosition();
		//		this->saveOldPos(clickpoint.x, clickpoint.y);
		//		this->setMoving(true);
		//	}
		//}
		//else
		//{
		//	this->setSelected(false);
		//}
		////

		for (std::map<int, mItem*>::iterator itr = inventory.begin(); itr != inventory.end(); itr++){
			itr->second->Update(delta);

			if (itr->second->isActivated()){
				itr->second->itemOnEffect(m_player);
				itr->second->setAmount(itr->second->getAmount() - 1);

				if (itr->second->getAmount() == 0){
					//
					for (int i = 0; i < BELT_MAX; i++){
						if (playerPtr->getBelt(i) != NULLITEM){
							if (playerPtr->getBelt(i) == itr->first){
								playerPtr->setBelt(i, NULLITEM);
							}
						}
					}
					//
					playerPtr->getInventory()->removeFromInventory(itr->first);		
					// 순서 재소팅

				}				
			}

			//if (itr->second->isSelected()){
			//	POINTFLOAT mousepoint = ::coControl::GetInstance().getMousePosition();
			//	if (::coControl::GetInstance().getKeyControlInfo()[VK_LBUTTON] && itr->second->isMoving()==false){
			//		itr->second->saveOldPos(mousepoint.x, mousepoint.y);
			//		itr->second->setMoving(true);
			//	}

			if (itr->second->isMoving()){
				POINTFLOAT mousepoint = ::coControl::GetInstance().getMousePosition();
				// 이동중이고 마우스 키를 떼었을때, 원래 위치로 되돌린다.
				// 원래 위치로 되돌릴 생각이 없다면, 
				// 아래 좌표를 현재 좌표로 확정한다.

				itr->second->moveTo(mousepoint.x, mousepoint.y);
				bool info = ::coControl::GetInstance().getKeyControlInfo()[VK_LBUTTON];
				if (info == false){
					// 마우스를 놓았을때 벨트의 일정 범위 안이면 해당 벨트에 
					// 아이디를 집어넣는다.
					itr->second->setPos(itr->second->getOldcur().x, itr->second->getOldcur().y);
					itr->second->setMoving(false);

					// 만약 숏컷 범위 안이면
					for (int i = 0; i < BELT_MAX; i++){
						D2D1_RECT_F rect = dynamic_cast<uiBelt*>(m_belt)->getBeltRect(i);
						if (mousepoint.x >= rect.left &&
							mousepoint.y >= rect.top &&
							mousepoint.x <= rect.right &&
							mousepoint.y <= rect.bottom){
							// 3*3의 프로세스가 들지만 어차피 많지 않으니 brute force 처리
							for (int j = 0; j < BELT_MAX; j++){
								if (dynamic_cast<mPlayer*>(m_player)->getBelt(j) == itr->first){
									dynamic_cast<mPlayer*>(m_player)->setBelt(j, NULLITEM);
								}
							}
							//
							dynamic_cast<mPlayer*>(m_player)->setBelt(i, itr->first);
						}
					}
					
					// 차후 인벤토리 밖으로 끌어놓으면 해당 아이템 삭제 추가
					//if (mousepoint.x < this->getPos()->x &&
					//	mousepoint.y < this->getPos()->y &&
					//	mousepoint.x > this->getPos()->x + ::cResourceManager::GetInstance().getUISize(UIID::UI_INVENTORY).x &&
					//	mousepoint.y > this->getPos()->y + ::cResourceManager::GetInstance().getUISize(UIID::UI_INVENTORY).y){
					//	playerPtr->getInventory()->removeFromInventory(itr->first, itr->second->getAmount()+1);
					//}
				}
			}
			//}
		}

		// 재소팅은 무언가 삭제되서 원래 사이즈와 달라졌을때 재소팅
		if (m_nInventorySize != inventory.size()){
			int i = 0;
			for (std::map<int, mItem*>::iterator itr = inventory.begin(); itr != inventory.end(); itr++){
				itr->second->setPos(this->getPos()->x + 10.0f + (i*50.0f), this->getPos()->y + 20.0f);
				i++;
			}
			m_nInventorySize = inventory.size();
		}
	}
}

void uiInventory::Render(){
	if (this->isActivated()){
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
		int movingItemID = NULLITEM;
		for (std::map<int, mItem*>::iterator itr = inventory.begin(); itr != inventory.end(); itr++){
			if (itr->second->isMoving()){
				movingItemID = itr->first;
			}
			else{
				itr->second->Render();
			}
		}
		if (movingItemID != NULLITEM){
			inventory.at(movingItemID)->Render();
		}
	}
}

void uiInventory::moveTo(float x, float y){
	uiInterface::moveTo(x, y);
	mPlayer* playerPtr = (mPlayer*)m_player;
	std::map<int, mItem*> inventory = playerPtr->getInventory()->getInventory();
	int i = 0;
	for (std::map<int, mItem*>::iterator itr = inventory.begin(); itr != inventory.end(); itr++){
		itr->second->setPos(this->getPos()->x + 10.0f + (i*50.0f), this->getPos()->y + 20.0f);
		i++;
	}
}