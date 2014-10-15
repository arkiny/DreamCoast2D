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
	this->setMoveRectangle({ 4.0f,
		0.0f,
		273.0f,
		13.0f });

	m_RectPrevButton = { this->getPos()->x + 115.0f, this->getPos()->y + 132.0f,
		this->getPos()->x + 129.0f, this->getPos()->y + 143.0f };
	m_RectNextButton = { this->getPos()->x + 149.0f, this->getPos()->y + 132.0f,
		this->getPos()->x + 163.0f, this->getPos()->y + 143.0f };
	m_RectPageOut = { this->getPos()->x + 130.0f, this->getPos()->y + 132.0f,
		this->getPos()->x + 148.0f, this->getPos()->y + 144.0f };
}

void uiInventory::OnInit(){
	this->setActivated(false);
	m_bMoving = NULLITEM;

	mPlayer* playerPtr = (mPlayer*)m_player;
	std::map<int, mItem*> inventory = playerPtr->getInventory()->getInventory();
	std::map<int, mItem*>::iterator itr = inventory.begin();
		int i = 0;
	int j = 0;
	while (itr != inventory.end()){
		itr->second->setPos(this->getPos()->x + 10.0f + (i * 50.0f), this->getPos()->y + 20.0f + (j * 50.0f));
		itr++;
		i++;
		if (i >= m_nWidthMax){
			i = 0;
			j++;
			if (j >= m_nHeightMax){
				j = 0;
			}
		}
	}


	/*itr->second->setPos(this->getPos()->x + 10.0f + (0*50.0f), this->getPos()->y + 20.0f + (0*50.0f));
	itr++;
	itr->second->setPos(this->getPos()->x + 10.0f + (1 * 50.0f), this->getPos()->y + 20.0f + (0 * 50.0f));*/

	//for (std::map<int, mItem*>::iterator itr = inventory.begin(); itr != inventory.end(); itr++){		
	//	

	//}

	m_nInventorySize = inventory.size();

}

void uiInventory::Update(float delta){
	// ���� ���⿡�� �巡�׿� ���?
	// ��Ʈ�� �ø���?
	// ��� ����

	 //iŰ�� �κ��丮 �ҷ�����
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

		if (::coControl::GetInstance().getKeyControlInfo()[VK_LBUTTON]){
			if (::coControl::GetInstance().getClickPosition().x >= m_RectPrevButton.left
				&&::coControl::GetInstance().getClickPosition().y >= m_RectPrevButton.top
				&&::coControl::GetInstance().getClickPosition().x <= m_RectPrevButton.right
				&&::coControl::GetInstance().getClickPosition().y <= m_RectPrevButton.bottom){
				::coControl::GetInstance().onKeyUp(VK_LBUTTON);
				m_nCurrentPage--;
			}
			if (::coControl::GetInstance().getClickPosition().x >= m_RectNextButton.left
				&&::coControl::GetInstance().getClickPosition().y >= m_RectNextButton.top
				&&::coControl::GetInstance().getClickPosition().x <= m_RectNextButton.right
				&&::coControl::GetInstance().getClickPosition().y <= m_RectNextButton.bottom){
				::coControl::GetInstance().onKeyUp(VK_LBUTTON);
				m_nCurrentPage++;
			}

			if (m_nCurrentPage > static_cast<int>(inventory.size()) / m_nMaxNumforaPage){
				m_nCurrentPage = 0;
			}

			if (m_nCurrentPage < 0){
				m_nCurrentPage = static_cast<int>(inventory.size()) / m_nMaxNumforaPage;
			}
		}

		// �������� �´� �����۸� ����
		int index = 0;

		for (std::map<int, mItem*>::iterator itr = inventory.begin(); itr != inventory.end(); itr++){
			if (index / m_nMaxNumforaPage == m_nCurrentPage){

				itr->second->Update(delta);
				if (itr->second->isMoving()){
					POINTFLOAT mousepoint = ::coControl::GetInstance().getMousePosition();
					// �̵����̰� ���콺 Ű�� ��������, ���� ��ġ�� �ǵ�����.
					// ���� ��ġ�� �ǵ��� ������ ���ٸ�, 
					// �Ʒ� ��ǥ�� ���� ��ǥ�� Ȯ���Ѵ�.

					itr->second->moveTo(mousepoint.x, mousepoint.y);
					bool info = ::coControl::GetInstance().getKeyControlInfo()[VK_LBUTTON];
					if (info == false){
						// ���콺�� �������� ��Ʈ�� ���� ���� ���̸� �ش� ��Ʈ�� 
						// ���̵� ����ִ´�.
						itr->second->setPos(itr->second->getOldcur().x, itr->second->getOldcur().y);
						itr->second->setMoving(false);

						// ���� ���� ���� ���̸�
						for (int i = 0; i < BELT_MAX; i++){
							D2D1_RECT_F rect = dynamic_cast<uiBelt*>(m_belt)->getBeltRect(i);
							if (mousepoint.x >= rect.left &&
								mousepoint.y >= rect.top &&
								mousepoint.x <= rect.right &&
								mousepoint.y <= rect.bottom){
								// 3*3�� ���μ����� ������ ������ ���� ������ brute force ó��
								for (int j = 0; j < BELT_MAX; j++){
									if (dynamic_cast<mPlayer*>(m_player)->getBelt(j) == itr->first){
										dynamic_cast<mPlayer*>(m_player)->setBelt(j, NULLITEM);
									}
								}
								//
								dynamic_cast<mPlayer*>(m_player)->setBelt(i, itr->first);
							}
						}

						// ���� �κ��丮 ������ ��������� �ش� ������ ���� �߰�
						//if (mousepoint.x < this->getPos()->x &&
						//	mousepoint.y < this->getPos()->y &&
						//	mousepoint.x > this->getPos()->x + ::cResourceManager::GetInstance().getUISize(UIID::UI_INVENTORY).x &&
						//	mousepoint.y > this->getPos()->y + ::cResourceManager::GetInstance().getUISize(UIID::UI_INVENTORY).y){
						//	playerPtr->getInventory()->removeFromInventory(itr->first, itr->second->getAmount()+1);
						//}
					}
				}

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
						// ���� �����

					}
				}
			}

			// ������� ���� �����Ǽ� ���� ������� �޶������� �����
			if (m_nInventorySize != inventory.size()){
				mPlayer* playerPtr = (mPlayer*)m_player;
				std::map<int, mItem*> inventory = playerPtr->getInventory()->getInventory();
				std::map<int, mItem*>::iterator itr = inventory.begin();
				int i = 0;
				int j = 0;
				while (itr != inventory.end()){
					itr->second->setPos(this->getPos()->x + 10.0f + (i * 50.0f), this->getPos()->y + 20.0f + (j * 50.0f));
					itr++;
					i++;
					if (i >= m_nWidthMax){
						i = 0;
						j++;
						if (j >= m_nHeightMax){
							j = 0;
						}
					}
				}
				m_nInventorySize = inventory.size();
			}
			index++;
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

		// TODO: ����� �� �������� �޾ƿͼ� ���ڷ� ǥ��������
		// ���� �� mItem�� render�� �־, position�� ���� �������ϰ� ó��
		// �� mItem�� doubleclick���� ��� ������ ���, Ŭ���� �巡�� ���� ��� �̵��ϰ�
		// ��ӽÿ� ��Ʈ ���� ������� ��� �ش� ĭ�� ������ �Է�
		// ���� ��Ʈ���� ����� �ƴ� ��� �������

		mPlayer* playerPtr = (mPlayer*)m_player;
		std::map<int, mItem*> inventory = playerPtr->getInventory()->getInventory();
		int movingItemID = NULLITEM;

		// �������� �´� �����۸� ����
		int index = 0;
		for (std::map<int, mItem*>::iterator itr = inventory.begin(); itr != inventory.end(); itr++){
			if (index / m_nMaxNumforaPage == m_nCurrentPage){
				if (itr->second->isMoving()){
					movingItemID = itr->first;
				}
				else{
					itr->second->Render();
				}
			}
			index++;
		}
		//

		if (movingItemID != NULLITEM){
			inventory.at(movingItemID)->Render();
		}

		wchar_t* wszText_ = new wchar_t[20];

		int length = 0;
		length += swprintf(wszText_ + length, 20, L"%d", m_nCurrentPage);
		UINT32 cTextLength_ = (UINT32)wcslen(wszText_);

		// draw text
		::cD2DRenderer::GetInstance().GetRenderTarget()->DrawTextW(
			wszText_,
			cTextLength_,
			::cD2DRenderer::GetInstance().GetTextFormat(),
			m_RectPageOut,
			::cD2DRenderer::GetInstance().GetBlackBrush());
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
	m_RectPrevButton = { this->getPos()->x + 115.0f, this->getPos()->y + 132.0f,
		this->getPos()->x + 129.0f, this->getPos()->y + 143.0f };
	m_RectNextButton = { this->getPos()->x + 149.0f, this->getPos()->y + 132.0f,
		this->getPos()->x + 163.0f, this->getPos()->y + 143.0f };
	m_RectPageOut = { this->getPos()->x + 130.0f, this->getPos()->y + 132.0f,
		this->getPos()->x + 148.0f, this->getPos()->y + 144.0f };
}