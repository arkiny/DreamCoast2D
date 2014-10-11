#include "stdafx.h"
#include <algorithm>

#include "cD2DRenderer.h"
#include "mPlayer.h"
#include "coControl.h"
#include "VECTOR2D.h"
#include "uSprite.h"
#include "wTileMap.h"
#include "uCamera.h"
#include "uTile.h"
#include "cResourceManager.h"
#include "cSoundManager.h"
#include "mItem.h"
#include "mInventory.h"


mPlayer::mPlayer()
{	
	m_ipD2DBitmap = nullptr;
	m_Cam = nullptr;

	m_Inventory = new mInventory;
	
	//todo: �ӽ÷� �߾ӿ� ���, ���� �������� ���� ������ ���� ����	
	_realVector = new VECTOR2D(514.0f, 384.0f);
	_drawVector = new VECTOR2D(_realVector->x, _realVector->y + 15.0f);
	m_spriteAtlas = new uSprite();
	m_SeeDir = RIGHTDOWN;
	m_State = ONMOVE;

	m_MAXHP = 2000.0f;
	m_MAXMP = 200.0f;
	m_HP = 2000.0f;
	m_MP = 200.0f;
}


mPlayer::~mPlayer()
{
	if (m_Cam != NULL){
		delete m_Cam;
	}
	if (_drawVector != NULL){
		delete _drawVector;
	}
	if (m_spriteAtlas != NULL){
		delete m_spriteAtlas;
	}
}

void mPlayer::onInit(){
	//HWND hWnd = renderer.GetHwnd();
	m_ipD2DBitmap = ::cResourceManager::GetInstance().getPlayerBitMap();
	m_Cam = new uCamera(1028.0, 768.0f, this->getRealPos());
	
	for (int i = 0; i < SKILLCOMMAND_MAX; i++){
		m_naSkill[i] = 99;
	}
	m_naSkill[0] = DIRECTION::LEFT;
	m_naSkill[1] = DIRECTION::DOWN;
	m_naSkill[2] = DIRECTION::RIGHT;

	// TODO: ���� ���� ������
	//		�߰��Ǵ� �� �߰�
	//m_vInventory.insert
	//	(std::pair<int, mItem*>
	//	(ITEM_POTION_HEALTH_SMALL, 
	//	(new mItem(ITEM_CONSUME, ITEM_POTION_HEALTH_SMALL, Item_Consume_DB[ITEM_POTION_HEALTH_SMALL])
	//	)));

	mItem* adder = new mItem(ITEM_CONSUME, ITEM_POTION_HEALTH_SMALL, Item_Consume_DB[ITEM_POTION_HEALTH_SMALL]);
	adder->setAmount(3);
	m_Inventory->addToInventory(adder);

	// TODO: ��Ʈ���� �κ��丮�� ����� �����͸� �Ѱܼ� ����ϴ� ������� ���
	// ��Ʈ�� ���� �ִ� ����Ű�� ������ �����Ƿ� �Ϲ� ��� �̿��ؼ�
	// ��ġŸ���� ���̴� ���� �̿��ص� �ɰ� ����.
	m_aBelt[0] = m_Inventory->getInventory().at(ITEM_POTION_HEALTH_SMALL);
	//m_aBelt[0]->setAmount(3);

	m_aBelt[1] = nullptr;
	m_aBelt[2] = nullptr;
}

//void mPlayer::addToInventory(mItem* item){
//	if (m_vInventory.count(item->getID()) >= 1){
//		mItem* ptr = m_vInventory.at(item->getID());
//		ptr->setAmount(item->getAmount() + ptr->getAmount());
//		ptr = nullptr;
//	}
//	else {
//		m_vInventory.insert(std::pair<int, mItem*>(item->getID(), item));
//	}
//}
//
//void mPlayer::removeFromInventory(int ID){
//	if (m_vInventory.count(ID) >= 1){ 
//		// �ش� ���̵��� �������� �����ϰ� 1���̻� ��� �����ϴٸ�
//		mItem* ptr = m_vInventory.at(ID);
//		if (ptr->getAmount() > 2){
//			ptr->setAmount(ptr->getAmount() - 1);
//		}
//		else { 
//			// 1�� ����Ҿ縸 ���Ұų�, �ȳ��Ҵٸ�
//			// ������ equipment�� ���Ǿ��ٴ� üŷ���ϰ� ������� �ʰ� ó��...
//			mItem* ptr = m_vInventory.at(ID);
//			m_vInventory.erase(m_aBelt[KEY_A]->getID());
//			delete ptr;
//		}
//	}
//}

void mPlayer::onUpdate(float fdeltatime){	
	// ����� primitive�� ����� �������� �̿��� statecontroller, 
	// ���� �ð��� ������ statemachine���� ��ü
	
	if (m_State == ONDEAD){
		// �÷��̾� ��� ó��, ���� �⺻���� DeadEnd State
		// ���� 1���� ó���� ����� ó��,
		mPlayer::onDead(fdeltatime);
	}
	else if (m_State == ONHIT){
		// ���� �켱������ ���� �� �ǰ� ���� �׼�, ���� Ÿ�ӵ� �־���ϰ�...
		// �ǰ� �����ÿ��� ��� ��Ʈ�� �Ұ�...
		// ���� �������̳� ��ų�� ���� �ǰ� ������ ���� ����
		//(�ǰݽ� wTileMap���� callback���� getHit() �Լ� ���� �ǰ� state�� �����)
		// �Ŀ� IDLE�� ���� ����... �ϴ� ���⼭ �������� ���� ���
		// ONMOVE���� ó�������Ƿ� ONMOVE�� ó��
		mPlayer::onHit(fdeltatime);
	}
	// skill
	// xŰ�� ������ �������� ��ų Ŀ�ǵ带 �Է��ϰ�
	// xŰ�� ���� ��ų Ŀ�ǵ带 ������Ų��.
	// ���� �Է��߿� Ÿ���� ������ ��ҵǹǷ�, �켱������ onhit���ٴ� �Ʒ�
	// ������ �̵��� ���߰� Ű�� �Է¹޾ƾ� �ϹǷ� �̵�/��� ���ٴ� ������
	

	// skill
	else if (::coControl::GetInstance().getKeyControlInfo()[0x5A]){
		if (m_State == ONATTACK){
			mPlayer::onAttack(fdeltatime);
		}
		else {
			m_State = ONATTACK;
			cSoundManager::GetInstance().executeAttack();
			m_attackaccumtime = 0.0f;
			m_spriteAtlas->setCurrentFrame(0);			
		}
	}
	else if (m_State == ONATTACK){
		// skill casted
		m_castingSkill = 99;
		mPlayer::onAttack(fdeltatime);
	}

	else if (::coControl::GetInstance().getKeyControlInfo()[0x58]){
		if (m_State == ONCASTING){
			// �Է��ϴ� Ű���� ������� ���, ���� Ȥ�� ���ڿ��� �Է�
			// �ִϸ��̼��� ĳ���þִϸ��̼�����
			putKeyIntoQueue();
		}
		else {
			// ���¸� ��ĳ�������� ����
			m_State = ONCASTING;
			// ���� ��ų ĳ���� ����
			cSoundManager::GetInstance().executeBeginSpell();
			// Ȥ�ó� ������ �Ǵ� ùŰ�� �Է¹���
			putKeyIntoQueue();			
			//m_attackaccumtime = 0.0f;
			//m_spriteAtlas->setCurrentFrame(0);
		}
	}

	///ui belt�� �̵�
	///// item belt
	//else if (::coControl::GetInstance().getKeyControlInfo()[0x41]){
	//	::coControl::GetInstance().onKeyUp(0x41);
	//	if (m_aBelt[KEY_A] != nullptr){			
	//		m_aBelt[KEY_A]->itemOnEffect(this);
	//		int in = m_aBelt[KEY_A]->getAmount() - 1;
	//		m_aBelt[KEY_A]->setAmount(in);

	//		if (m_aBelt[KEY_A]->getAmount() == 0){
	//			mItem* ptr = m_Inventory->getInventory().at(m_aBelt[KEY_A]->getID());
	//			m_Inventory->getInventory().erase(m_aBelt[KEY_A]->getID());
	//			delete ptr;

	//			m_aBelt[KEY_A] = nullptr;
	//		}			
	//	}
	//}
	//else if (::coControl::GetInstance().getKeyControlInfo()[0x53]){
	//	::coControl::GetInstance().onKeyUp(0x53);
	//	if (m_aBelt[KEY_S] != nullptr){
	//		m_aBelt[KEY_S]->itemOnEffect(this);
	//		int in = m_aBelt[KEY_S]->getAmount() - 1;
	//		m_aBelt[KEY_S]->setAmount(in);
	//		if (m_aBelt[KEY_S]->getAmount() == 0){
	//			mItem* ptr = m_Inventory->getInventory().at(m_aBelt[KEY_S]->getID());
	//			m_Inventory->getInventory().erase(m_aBelt[KEY_S]->getID());
	//			delete ptr;

	//			m_aBelt[KEY_S] = nullptr;
	//		}
	//	}
	//}	
	//else if (::coControl::GetInstance().getKeyControlInfo()[0x44]){
	//	::coControl::GetInstance().onKeyUp(0x44);
	//	if (m_aBelt[KEY_D] != nullptr){
	//		m_aBelt[KEY_D]->itemOnEffect(this);
	//		int in = m_aBelt[KEY_D]->getAmount() - 1;
	//		m_aBelt[KEY_D]->setAmount(in);
	//		if (m_aBelt[KEY_D]->getAmount() == 0){
	//			mItem* ptr = m_Inventory->getInventory().at(m_aBelt[KEY_D]->getID());
	//			m_Inventory->getInventory().erase(m_aBelt[KEY_D]->getID());
	//			delete ptr;
	//			m_aBelt[KEY_D] = nullptr;			
	//		}
	//	}
	//}
	/////


	else if (m_State == ONCASTING){
		// ĳ������ �ǽ��ϰ� xŰ�� ��������
		if (!::coControl::GetInstance().getKeyControlInfo()[0x58]){
			// TODO: Ű�� �������� ĳ���� ���� ���߱�
			cSoundManager::GetInstance().stopBeginSpell();
			
			// �Է� �� Ű�� ���ǥ�� ���Ͽ� ���ǥ�� ������ ��� �ش� ��ų��,
			// �ƴҰ�쿡�� �г�Ƽ�� �ο��Ѵ�. (�ڱ⿡�� ������)
			// ��ų �߻��, ���ݸ�ǰ� ���Ͼ� ����� ���ϴ� ���,
			// �ڱ��ֺ����� ��ų�� ���õ� ����Ʈ�� ǥ���ؾ��Ѵ�.

			// ������Ʈ �ø��� üũ�ϰ� �ǹǷ� ������ �ȴ�.
			// TODO ������Ʈ Ÿ�� üũ
			if (!m_qKeyInput.empty()){
				if (skillCompare(m_qKeyInput, m_naSkill, 0)){
					m_castingSkill = 0;
				}
				else {
					// �ƴϸ� ���Ƽ�� �ִ� �ɷ�
					getHit(10.0f);
				}
				while (!m_qKeyInput.empty()){
					m_qKeyInput.pop();
				}
			}
			else {
				if (m_castingSkill == 0){
					// skill������ ��Ȳ ����
					m_State = ONATTACK;
					cSoundManager::GetInstance().executeSkill(m_castingSkill);
					m_attackaccumtime = 0.0f;
					m_spriteAtlas->setCurrentFrame(0);
				}
				else {
					m_State = ONMOVE;
				}
			}
		}
		else {
			// do nothing
		}
	}

	else if (m_State == ONMOVE){
		// casting skill reseting to idle
		m_castingSkill = 99;
		m_attackaccumtime = 0.0f;
		mPlayer::onMove(fdeltatime);
	}
}


// �ǰ� �� ó�� (ü�°���)
void mPlayer::getHit(float dmg){
	mCharacter::getHit(dmg);
	if (this->getHealth() >= 0.0f){
		m_State = ONHIT;
	}
	else {
		m_State = ONDEAD;
	}
}



void mPlayer::onRender(){
	if (m_ipD2DBitmap != nullptr){
		//
		VECTOR2D cpos = m_Cam->translasteToScreen(_drawVector);
		//
		// Pivot �̹����� �Ѱ�� �ٴ� -> dxArea���� ����
		::D2D1_RECT_F dxArea
			= m_spriteAtlas->getCoordinateFromPivot(cpos);

		//	
		::D2D1_RECT_F srcArea
			= m_spriteAtlas->getSrcFrameFromSprite();

		::cD2DRenderer::GetInstance().GetRenderTarget()->DrawBitmap(m_ipD2DBitmap, dxArea, m_alpha,
			D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
			srcArea);
		
		//ȸ��� �ʿ��� �κ�
		//renderer.GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Identity());

		//debug ��
		::cD2DRenderer::GetInstance().GetRenderTarget()->DrawRectangle(dxArea, ::cD2DRenderer::GetInstance().GetBlackBrush());
		
		::D2D1_RECT_F pivotArea;
		pivotArea.top = cpos.y - 2.0f;
		pivotArea.bottom = cpos.y + 2.0f;
		pivotArea.left = cpos.x - 2.0f;
		pivotArea.right = cpos.x + 2.0f;
		::cD2DRenderer::GetInstance().GetRenderTarget()->DrawRectangle(pivotArea, ::cD2DRenderer::GetInstance().GetBlackBrush());
		
		//renderer.GetRenderTarget()->DrawRectangle(dxArea, renderer.GetBlackBrush());
		//pivotArea;
		cpos = m_Cam->translasteToScreen(_realVector);
		pivotArea.top = cpos.y - 2.0f;
		pivotArea.bottom = cpos.y + 2.0f;
		pivotArea.left = cpos.x - 2.0f;
		pivotArea.right = cpos.x + 2.0f;
		::cD2DRenderer::GetInstance().GetRenderTarget()->DrawRectangle(pivotArea, ::cD2DRenderer::GetInstance().GetBlackBrush());
	}
}

void mPlayer::onRender(bool alpha){
	if (m_ipD2DBitmap != nullptr){
		VECTOR2D cpos = m_Cam->translasteToScreen(_drawVector);
		// Pivot �̹����� �Ѱ�� �ٴ� -> dxArea���� ����
		::D2D1_RECT_F dxArea
			= m_spriteAtlas->getCoordinateFromPivot(cpos);

		//	
		::D2D1_RECT_F srcArea
			= m_spriteAtlas->getSrcFrameFromSprite();

		if (alpha){
			::cD2DRenderer::GetInstance().GetRenderTarget()->DrawBitmap(m_ipD2DBitmap, dxArea, 0.4f,
				D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
				srcArea);
		}
		//ȸ��� �ʿ��� �κ�
		//renderer.GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Identity());

		//debug ��
		::cD2DRenderer::GetInstance().GetRenderTarget()->DrawRectangle(dxArea, ::cD2DRenderer::GetInstance().GetBlackBrush());

		::D2D1_RECT_F pivotArea;
		pivotArea.top = cpos.y - 2.0f;
		pivotArea.bottom = cpos.y + 2.0f;
		pivotArea.left = cpos.x - 2.0f;
		pivotArea.right = cpos.x + 2.0f;
		::cD2DRenderer::GetInstance().GetRenderTarget()->DrawRectangle(pivotArea, ::cD2DRenderer::GetInstance().GetBlackBrush());


		//renderer.GetRenderTarget()->DrawRectangle(dxArea, renderer.GetBrush());
		//pivotArea;
		cpos = m_Cam->translasteToScreen(_realVector);
		pivotArea.top = cpos.y - 2.0f;
		pivotArea.bottom = cpos.y + 2.0f;
		pivotArea.left = cpos.x - 2.0f;
		pivotArea.right = cpos.x + 2.0f;
		::cD2DRenderer::GetInstance().GetRenderTarget()->DrawRectangle(pivotArea, ::cD2DRenderer::GetInstance().GetBlackBrush());
	}
}



void mPlayer::putKeyIntoQueue(){
	// �ƹ����� Ű �켱������ �����ϱ� �����̴�. ���� �Է��̳� �߸� �� �Է��� ������ üŷ�� �ϴ� �������� �̷��
	// ���� ������ Ŀ�ǵ�� �׼����� ó���ϴ� �� ó��...
	if (m_qKeyInput.size() < SKILLCOMMAND_MAX){
		if (::coControl::GetInstance().getKeyControlInfo()[VK_LEFT] &&
			::coControl::GetInstance().getKeyControlInfo()[VK_DOWN]){
			::coControl::GetInstance().onKeyUp(VK_LEFT);
			::coControl::GetInstance().onKeyUp(VK_DOWN);
			m_qKeyInput.push(DIRECTION::LEFTDOWN);
		}

		else if (::coControl::GetInstance().getKeyControlInfo()[VK_LEFT] &&
			::coControl::GetInstance().getKeyControlInfo()[VK_UP]){
			::coControl::GetInstance().onKeyUp(VK_LEFT);
			::coControl::GetInstance().onKeyUp(VK_UP);
			m_qKeyInput.push(DIRECTION::LEFTUP);			
		}

		else if (::coControl::GetInstance().getKeyControlInfo()[VK_RIGHT] &&
			::coControl::GetInstance().getKeyControlInfo()[VK_DOWN]){
			::coControl::GetInstance().onKeyUp(VK_RIGHT);
			::coControl::GetInstance().onKeyUp(VK_DOWN);
			m_qKeyInput.push(DIRECTION::RIGHTDOWN);
		}

		else if (::coControl::GetInstance().getKeyControlInfo()[VK_RIGHT] &&
			::coControl::GetInstance().getKeyControlInfo()[VK_UP]){
			::coControl::GetInstance().onKeyUp(VK_RIGHT);
			::coControl::GetInstance().onKeyUp(VK_UP);
			m_qKeyInput.push(DIRECTION::RIGHTUP);			
		}

		else if (::coControl::GetInstance().getKeyControlInfo()[VK_RIGHT]){
			::coControl::GetInstance().onKeyUp(VK_RIGHT);
			m_qKeyInput.push(DIRECTION::RIGHT);
		}
		else if (::coControl::GetInstance().getKeyControlInfo()[VK_LEFT]){
			::coControl::GetInstance().onKeyUp(VK_LEFT);
			m_qKeyInput.push(DIRECTION::LEFT);
		}
		else if (::coControl::GetInstance().getKeyControlInfo()[VK_DOWN]){
			::coControl::GetInstance().onKeyUp(VK_DOWN);
			m_qKeyInput.push(DIRECTION::DOWN);
		}
		else if (::coControl::GetInstance().getKeyControlInfo()[VK_UP]){
			::coControl::GetInstance().onKeyUp(VK_UP);
			m_qKeyInput.push(DIRECTION::UP);
		}
	}
}

bool mPlayer::skillCompare(std::queue<int> &keyinput, int* skillArray, int index){
	if (index >= SKILLCOMMAND_MAX){
		return true;
	}

	if (skillArray[index] == 99){
		return true;
	}

	if (keyinput.empty()){
		return false;
	}

	if (keyinput.front() != skillArray[index]){
		return false;
	}
	

	keyinput.pop();
	
	bool ret = skillCompare(keyinput, skillArray, index + 1);
	return ret;
}