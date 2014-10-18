#include "stdafx.h"

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

#include "mGFX.h"
#include "mEffect.h"

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
	m_MAXMP = 50.0f;
	m_HP = 2000.0f;
	m_MP = 50.0f;
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
	
	/// skill list init
	// player�� ��ų ����Ʈ �Է�
	// ��ųĿ�ǵ帮��Ʈ�� ��ų ������ �Բ� DB_Skill_Area_List�� �߰��Ǿ� ����
	m_SkillList.push_back(skill1);
	m_SkillList.push_back(skill2);
	
	/// item
	// TODO: ���� ������ ���� �κ��丮�� �߰��Ҽ� �ֵ��� �� ��
	mItem* adder = new mItem(ITEM_CONSUME, ITEM_POTION_HEALTH_SMALL, Item_Consume_DB[ITEM_POTION_HEALTH_SMALL]);
	adder->setAmount(3);
	m_Inventory->addToInventory(adder);
	m_Inventory->addToInventory(adder); // should be 6, ok

	adder = new mItem(ITEM_CONSUME, ITEM_POTION_HEALTH_BIG, Item_Consume_DB[ITEM_POTION_HEALTH_BIG]);
	adder->setAmount(3);
	m_Inventory->addToInventory(adder);
	adder = new mItem(ITEM_CONSUME, ITEM_POTION_HEALTH_1, Item_Consume_DB[ITEM_POTION_HEALTH_1]);
	adder->setAmount(3);
	m_Inventory->addToInventory(adder);
	adder = new mItem(ITEM_CONSUME, ITEM_POTION_HEALTH_2, Item_Consume_DB[ITEM_POTION_HEALTH_2]);
	adder->setAmount(3);
	m_Inventory->addToInventory(adder);
	adder = new mItem(ITEM_CONSUME, ITEM_POTION_HEALTH_3, Item_Consume_DB[ITEM_POTION_HEALTH_3]);
	adder->setAmount(3);
	m_Inventory->addToInventory(adder);
	adder = new mItem(ITEM_CONSUME, ITEM_POTION_HEALTH_4, Item_Consume_DB[ITEM_POTION_HEALTH_4]);
	adder->setAmount(3);
	m_Inventory->addToInventory(adder);



	adder = new mItem(ITEM_CONSUME, ITEM_POTION_MANA_SMALL, Item_Consume_DB[ITEM_POTION_MANA_SMALL]);
	adder->setAmount(3);
	m_Inventory->addToInventory(adder);
	adder = new mItem(ITEM_CONSUME, ITEM_POTION_MANA_BIG, Item_Consume_DB[ITEM_POTION_MANA_BIG]);
	adder->setAmount(3);
	m_Inventory->addToInventory(adder);
	adder = new mItem(ITEM_CONSUME, ITEM_POTION_MANA_1, Item_Consume_DB[ITEM_POTION_MANA_1]);
	adder->setAmount(3);
	m_Inventory->addToInventory(adder);
	adder = new mItem(ITEM_CONSUME, ITEM_POTION_MANA_2, Item_Consume_DB[ITEM_POTION_MANA_2]);
	adder->setAmount(3);
	m_Inventory->addToInventory(adder);
	adder = new mItem(ITEM_CONSUME, ITEM_POTION_MANA_3, Item_Consume_DB[ITEM_POTION_MANA_3]);
	adder->setAmount(3);
	m_Inventory->addToInventory(adder);
	adder = new mItem(ITEM_CONSUME, ITEM_POTION_MANA_4, Item_Consume_DB[ITEM_POTION_MANA_4]);
	adder->setAmount(3);
	m_Inventory->addToInventory(adder);
	adder = nullptr;
	
	// TODO: ��Ʈ���� �κ��丮�� ����� �����͸� �Ѱܼ� ����ϴ� ������� ���
	// ��Ʈ�� ���� �ִ� ����Ű�� ������ �����Ƿ� �Ϲ� ��̸� �̿��ؼ�
	// ��ġŸ���� ���̴� ���� �̿��ص� �ɰ� ����.
	m_aBelt[0] = m_Inventory->getInventory()->at(ITEM_POTION_HEALTH_SMALL)->getID();
	//m_aBelt[0]->setAmount(3);

	m_aBelt[1] = m_Inventory->getInventory()->at(ITEM_POTION_MANA_SMALL)->getID();
	m_aBelt[2] = NULLITEM;
}

void mPlayer::onUpdate(float fdeltatime){
	// ����� primitive�� ����� �������� �̿��� statecontroller, 
	// ���� �ð��� ������ statemachine���� ��ü
	VECTOR2D coord;
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
			mPlayer::dmgToTile(fdeltatime, m_default_attackPower);
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
		mPlayer::dmgToTile(fdeltatime, m_default_attackPower);
	}

	else if (m_State == ONSKILLEFFECTING){		
		switch (m_castingSkill)
		{
		case 0:{
			
			mPlayer::onAttack(fdeltatime);
			mPlayer::dmgToArea(fdeltatime, m_default_attackPower, AREA_TYPE1);
			
			//delete coord;
			break;
		}
		case 1:{
			mPlayer::onAttack(fdeltatime);
			mPlayer::dmgToTile(fdeltatime, m_default_attackPower*10.0f);			
			break;
		}
		default:
			break;
		}	
		// onAttack ��� �����Ŀ� ��ų �÷��׷� ��ų���� ����
	}

	else if (::coControl::GetInstance().getKeyControlInfo()[0x58]){
		if (m_State == ONCASTING){
			// �Է��ϴ� Ű���� ������� ���, ���� Ȥ�� ���ڿ��� �Է�
			// �ִϸ��̼��� ĳ���þִϸ��̼�����
			mPlayer::onCasting(fdeltatime);
			putKeyIntoQueue();
		}
		else {
			// ���¸� ��ĳ�������� ����
			m_State = ONCASTING;
			// ���� ��ų ĳ���� ����
			mPlayer::onCasting(fdeltatime);
			cSoundManager::GetInstance().executeBeginSpell();
			// Ȥ�ó� ������ �Ǵ� ùŰ�� �Է¹���
			putKeyIntoQueue();			
			//m_attackaccumtime = 0.0f;
			//m_spriteAtlas->setCurrentFrame(0);
		}
	}
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
				for (unsigned int i = 0; i < m_SkillList.size(); i++){
					std::queue<int> temp = m_qKeyInput;
					if (skillCompare(temp, m_SkillList[i], 0)){
						m_castingSkill = i;
						break;
					}
				}
				
				if(m_castingSkill==99) {
					// �ƴϸ� ���Ƽ�� �ִ� �ɷ�
					getHit(10.0f);			
				}

				while (!m_qKeyInput.empty()){
					m_qKeyInput.pop();
				}
			}
			else {
				if (m_castingSkill != 99){
					// skill������ ��ų ����
					if (m_MP >= 10.0f){
						m_State = ONSKILLEFFECTING;
						cSoundManager::GetInstance().executeSkill(m_castingSkill);
						m_MP -= 10.0f;
						m_spriteAtlas->setCurrentFrame(0);

						//
						VECTOR2D currentTile = m_pTileMap->getTileCoordinates(*_realVector);
						VECTOR2D iso;
						switch (m_castingSkill)
						{
						case 0:
							mPlayer::effectToArea(fdeltatime,0, AREA_TYPE1);
							break;
						case 1:
							mPlayer::effectToTile(fdeltatime, 0);
							break;
						default:
							break;
						}			
						
						/*float x = iso.x*m_pTileMap->getRectTileWidth();
						float y = iso.y*m_pTileMap->getRectTileHeight();
						VECTOR2D in(x, y);
						iso = m_pTileMap->twoDtoISO(in);
						::mGFX::GetInstance().pushToEventQueue(new mEffect(1, 0, new VECTOR2D(iso.x, iso.y), m_Cam));*/

					}
					else{
						// ���� ������ ���Ƽ
						getHit(10.0f);
					}
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
	mGFX::GetInstance().pushToEventQueue(new mEffect(0, dmg, new VECTOR2D(*_drawVector), m_Cam));
	cSoundManager::GetInstance().executeOnHit(1);
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
		
		//if (this->getDmg() > 0){
		//	/// �ؽ�Ʈ ���
		//	wchar_t* wszText_ = new wchar_t[20];
		//	swprintf(wszText_, 20, L" %.0f",
		//		this->getDmg());
		//	UINT32 cTextLength_ = (UINT32)wcslen(wszText_);

		//	D2D1_RECT_F layoutRect = dxArea;
		//	// draw text
		//	::cD2DRenderer::GetInstance().GetRenderTarget()->DrawTextW(
		//		wszText_,
		//		cTextLength_,
		//		::cD2DRenderer::GetInstance().GetTextFormatDmg(),
		//		layoutRect,
		//		::cD2DRenderer::GetInstance().GetRedBrush());
		//}
		////ȸ��� �ʿ��� �κ�
		////renderer.GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Identity());

		////debug ��
		//::cD2DRenderer::GetInstance().GetRenderTarget()->DrawRectangle(dxArea, ::cD2DRenderer::GetInstance().GetBlackBrush());
		//
		//::D2D1_RECT_F pivotArea;
		//pivotArea.top = cpos.y - 2.0f;
		//pivotArea.bottom = cpos.y + 2.0f;
		//pivotArea.left = cpos.x - 2.0f;
		//pivotArea.right = cpos.x + 2.0f;
		//::cD2DRenderer::GetInstance().GetRenderTarget()->DrawRectangle(pivotArea, ::cD2DRenderer::GetInstance().GetBlackBrush());
		//
		////renderer.GetRenderTarget()->DrawRectangle(dxArea, renderer.GetBlackBrush());
		////pivotArea;
		//cpos = m_Cam->translasteToScreen(_realVector);
		//pivotArea.top = cpos.y - 2.0f;
		//pivotArea.bottom = cpos.y + 2.0f;
		//pivotArea.left = cpos.x - 2.0f;
		//pivotArea.right = cpos.x + 2.0f;
		//::cD2DRenderer::GetInstance().GetRenderTarget()->DrawRectangle(pivotArea, ::cD2DRenderer::GetInstance().GetBlackBrush());
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

		//if (this->getDmg() > 0){
		//	/// �ؽ�Ʈ ���
		//	wchar_t* wszText_ = new wchar_t[20];
		//	swprintf(wszText_, 20, L" %.0f",
		//		this->getDmg());
		//	UINT32 cTextLength_ = (UINT32)wcslen(wszText_);

		//	D2D1_RECT_F layoutRect = dxArea;
		//	// draw text
		//	::cD2DRenderer::GetInstance().GetRenderTarget()->DrawTextW(
		//		wszText_,
		//		cTextLength_,
		//		::cD2DRenderer::GetInstance().GetTextFormatDmg(),
		//		layoutRect,
		//		::cD2DRenderer::GetInstance().GetRedBrush());
		//}
		//ȸ��� �ʿ��� �κ�
		//renderer.GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Identity());

		////debug ��
		//::cD2DRenderer::GetInstance().GetRenderTarget()->DrawRectangle(dxArea, ::cD2DRenderer::GetInstance().GetBlackBrush());

		//::D2D1_RECT_F pivotArea;
		//pivotArea.top = cpos.y - 2.0f;
		//pivotArea.bottom = cpos.y + 2.0f;
		//pivotArea.left = cpos.x - 2.0f;
		//pivotArea.right = cpos.x + 2.0f;
		//::cD2DRenderer::GetInstance().GetRenderTarget()->DrawRectangle(pivotArea, ::cD2DRenderer::GetInstance().GetBlackBrush());


		////renderer.GetRenderTarget()->DrawRectangle(dxArea, renderer.GetBrush());
		////pivotArea;
		//cpos = m_Cam->translasteToScreen(_realVector);
		//pivotArea.top = cpos.y - 2.0f;
		//pivotArea.bottom = cpos.y + 2.0f;
		//pivotArea.left = cpos.x - 2.0f;
		//pivotArea.right = cpos.x + 2.0f;
		//::cD2DRenderer::GetInstance().GetRenderTarget()->DrawRectangle(pivotArea, ::cD2DRenderer::GetInstance().GetBlackBrush());
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
		if (keyinput.empty()){
			return true;
		}
		else {
			return false;
		}
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

