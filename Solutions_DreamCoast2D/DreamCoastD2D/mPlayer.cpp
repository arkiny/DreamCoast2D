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
	
	//todo: 임시로 중앙에 대기, 차후 맵정보에 따라 시작점 정보 수정	
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
	// player의 스킬 리스트 입력
	// 스킬커맨드리스트는 스킬 범위와 함께 DB_Skill_Area_List에 추가되어 있음
	m_SkillList.push_back(skill1);
	m_SkillList.push_back(skill2);
	
	/// item
	// TODO: 차후 상점을 통해 인벤토리에 추가할수 있도록 할 것
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
	
	// TODO: 벨트에는 인벤토리에 저장된 포인터를 넘겨서 사용하는 방식으로 사용
	// 벨트는 쓸수 있는 단축키의 제한이 있으므로 일반 어레이를 이용해서
	// 서치타임을 줄이는 법을 이용해도 될것 같다.
	m_aBelt[0] = m_Inventory->getInventory()->at(ITEM_POTION_HEALTH_SMALL)->getID();
	//m_aBelt[0]->setAmount(3);

	m_aBelt[1] = m_Inventory->getInventory()->at(ITEM_POTION_MANA_SMALL)->getID();
	m_aBelt[2] = NULLITEM;
}

void mPlayer::onUpdate(float fdeltatime){
	// 대단히 primitive한 컨디션 스테잇을 이용한 statecontroller, 
	// 차후 시간이 남으면 statemachine으로 교체
	VECTOR2D coord;
	if (m_State == ONDEAD){
		// 플레이어 사망 처리, 가장 기본적인 DeadEnd State
		// 가장 1순위 처리는 사망시 처리,
		mPlayer::onDead(fdeltatime);
	}
	else if (m_State == ONHIT){
		// 가장 우선순위가 높은 건 피격 판정 액션, 경직 타임도 있어야하고...
		// 피격 경직시에는 모든 컨트롤 불가...
		// 차후 아이템이나 스킬에 따라 피격 판정시 경직 제거
		//(피격시 wTileMap에서 callback으로 getHit() 함수 콜이 되고 state가 변경됨)
		// 후에 IDLE로 상태 변경... 일단 여기서 움직임이 없을 경우
		// ONMOVE에서 처리했으므로 ONMOVE로 처리
		mPlayer::onHit(fdeltatime);
	}
	// skill
	// x키를 누른뒤 뗄때까지 스킬 커맨드를 입력하고
	// x키를 뗄때 스킬 커맨드를 발현시킨다.
	// 물론 입력중에 타격을 받으면 취소되므로, 우선순위는 onhit보다는 아래
	// 하지만 이동은 멈추고 키를 입력받아야 하므로 이동/대기 보다는 빠르게


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
		// onAttack 모션 종료후에 스킬 플래그로 스킬역시 종료
	}

	else if (::coControl::GetInstance().getKeyControlInfo()[0x58]){
		if (m_State == ONCASTING){
			// 입력하는 키들을 순서대로 어레이, 벡터 혹은 문자열에 입력
			// 애니메이션은 캐스팅애니메이션으로
			mPlayer::onCasting(fdeltatime);
			putKeyIntoQueue();
		}
		else {
			// 상태를 온캐스팅으로 변경
			m_State = ONCASTING;
			// 최초 스킬 캐스팅 시전
			mPlayer::onCasting(fdeltatime);
			cSoundManager::GetInstance().executeBeginSpell();
			// 혹시나 들어오게 되는 첫키를 입력받음
			putKeyIntoQueue();			
			//m_attackaccumtime = 0.0f;
			//m_spriteAtlas->setCurrentFrame(0);
		}
	}
	else if (m_State == ONCASTING){
		// 캐스팅을 실시하고 x키를 떼었을때
		if (!::coControl::GetInstance().getKeyControlInfo()[0x58]){
			// TODO: 키를 떼었을때 캐스팅 사운드 멈추기
			cSoundManager::GetInstance().stopBeginSpell();
			
			// 입력 된 키를 기술표와 비교하여 기술표에 존재할 경우 해당 스킬을,
			// 아닐경우에는 패널티를 부여한다. (자기에게 데미지)
			// 스킬 발사시, 공격모션과 동일안 모션을 취하는 대신,
			// 자기주변으로 스킬에 관련된 이펙트를 표현해야한다.

			// 업데이트 시마다 체크하게 되므로 문제가 된다.
			// TODO 업데이트 타임 체크
			if (!m_qKeyInput.empty()){
				for (unsigned int i = 0; i < m_SkillList.size(); i++){
					std::queue<int> temp = m_qKeyInput;
					if (skillCompare(temp, m_SkillList[i], 0)){
						m_castingSkill = i;
						break;
					}
				}
				
				if(m_castingSkill==99) {
					// 아니면 페널티를 주는 걸로
					getHit(10.0f);			
				}

				while (!m_qKeyInput.empty()){
					m_qKeyInput.pop();
				}
			}
			else {
				if (m_castingSkill != 99){
					// skill에따른 스킬 시전
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
						// 마나 없을때 페널티
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


// 피격 시 처리 (체력감소)
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
		// Pivot 이미지의 한가운데 바닥 -> dxArea에서 지정
		::D2D1_RECT_F dxArea
			= m_spriteAtlas->getCoordinateFromPivot(cpos);

		//	
		::D2D1_RECT_F srcArea
			= m_spriteAtlas->getSrcFrameFromSprite();

		::cD2DRenderer::GetInstance().GetRenderTarget()->DrawBitmap(m_ipD2DBitmap, dxArea, m_alpha,
			D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
			srcArea);
		
		//if (this->getDmg() > 0){
		//	/// 텍스트 출력
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
		////회전등에 필요한 부분
		////renderer.GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Identity());

		////debug 용
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
		// Pivot 이미지의 한가운데 바닥 -> dxArea에서 지정
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
		//	/// 텍스트 출력
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
		//회전등에 필요한 부분
		//renderer.GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Identity());

		////debug 용
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
	// 아무래도 키 우선순위는 존재하기 마련이다. 동시 입력이나 잘못 된 입력이 있을때 체킹은 일단 나중으로 미루고
	// 가장 간단한 커맨드와 액션으로 처리하는 걸 처리...
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

