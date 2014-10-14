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
	// ���� ���⿡�� �巡�׿� ���?
	// ��Ʈ�� �ø���?
	// ��� ����

	 //iŰ�� �κ��丮 �ҷ�����
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
						if (playerPtr->getBelt(i) != NULLITEM){
							if (playerPtr->getBelt(i) == itr->first){
								playerPtr->setBelt(i, NULLITEM);
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

		// TODO: ����� �� �������� �޾ƿͼ� ���ڷ� ǥ��������
		// ���� �� mItem�� render�� �־, position�� ���� �������ϰ� ó��
		// �� mItem�� doubleclick���� ��� ������ ���, Ŭ���� �巡�� ���� ��� �̵��ϰ�
		// ��ӽÿ� ��Ʈ ���� ������� ��� �ش� ĭ�� ������ �Է�
		// ���� ��Ʈ���� ����� �ƴ� ��� �������

		mPlayer* playerPtr = (mPlayer*)m_player;
		std::map<int, mItem*> inventory = playerPtr->getInventory()->getInventory();

		wchar_t* wszText_ = new wchar_t[1028];

		int length = 0;
		length += swprintf(wszText_ + length, 1028, L"");
		int i = 0;
		for (std::map<int, mItem*>::iterator itr = inventory.begin(); itr != inventory.end(); itr++){
			itr->second->setPos(this->getPos()->x + 10.0f + (i*50.0f), this->getPos()->y + 20.0f);
			itr->second->Render();
			i++;
		}
			
		/*	if (itr->first == 0){
				length += swprintf(wszText_ + length, 1028, L"HealthPotion / ");
			}
			else if (itr->first == 2){
				length += swprintf(wszText_ + length, 1028, L"ManaPotion / ");
			}
			length+= swprintf(wszText_+length, 1028, L"amount %d \n", itr->second->getAmount());*/

			
		
		//UINT32 cTextLength_ = (UINT32)wcslen(wszText_);
		//
		//D2D1_RECT_F layoutRect = D2D1::RectF(
		//	this->getPos()->x,
		//	this->getPos()->y,
		//	this->getPos()->x + ::cResourceManager::GetInstance().getUISize(UIID::UI_INVENTORY).x,
		//	this->getPos()->y + ::cResourceManager::GetInstance().getUISize(UIID::UI_INVENTORY).y
		//	);

		//// draw text
		//::cD2DRenderer::GetInstance().GetRenderTarget()->DrawTextW(
		//	wszText_,
		//	cTextLength_,
		//	::cD2DRenderer::GetInstance().GetTextFormat(),
		//	layoutRect,
		//	::cD2DRenderer::GetInstance().GetBlackBrush());
	}
}