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

mPlayer::mPlayer()
{	
	m_ipD2DBitmap = nullptr;
	m_Cam = nullptr;
	
	//todo: 임시로 중앙에 대기, 차후 맵정보에 따라 시작점 정보 수정	
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
}

void mPlayer::onUpdate(float fdeltatime){	
	// 대단히 primitive한 컨디션 스테잇을 이용한 statecontroller, 
	// 차후 시간이 남으면 statemachine으로 교체
	
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
	else if (::coControl::GetInstance().getKeyControlInfo()[0x58]){
		if (m_State == ONCASTING){
			// 입력하는 키들을 순서대로 어레이, 벡터 혹은 문자열에 입력
			// 애니메이션은 캐스팅애니메이션으로
			putKeyIntoQueue();			
		}
		else {
			// 상태를 온캐스팅으로 변경
			m_State = ONCASTING;
			putKeyIntoQueue();
			// 혹시나 들어오게 되는 첫키를 입력받음
			//m_attackaccumtime = 0.0f;
			//m_spriteAtlas->setCurrentFrame(0);
		}
	}
	else if (m_State == ONCASTING){
		// 캐스팅을 실시하고 x키를 떼었을때
		if (!::coControl::GetInstance().getKeyControlInfo()[0x58]){
			// 입력 된 키를 기술표와 비교하여 기술표에 존재할 경우 해당 스킬을,
			// 아닐경우에는 패널티를 부여한다. (자기에게 데미지)
			// 스킬 발사시, 공격모션과 동일안 모션을 취하는 대신,
			// 자기주변으로 스킬에 관련된 이펙트를 표현해야한다.
			
			// 업데이트 시마다 체크하게 되므로 문제가 된다.
			// TODO 업데이트 타임 체크
			if (!m_qKeyInput.empty()){
				if (skillCompare(m_qKeyInput, m_naSkill, 0)){
					// 스킬 목록에 있는 스킬과 같을 경우
					// 어택
					m_State = ONATTACK;
					m_attackaccumtime = 0.0f;
					m_spriteAtlas->setCurrentFrame(0);					
					
					/*while (!m_qKeyInput.empty()){
						m_qKeyInput.pop();
					}*/

				}
				else {
					// 아니면 페널티를 주는 걸로
					m_State = ONMOVE;
				}				
			}			
		}
		else {
			// do nothing
		}
	}

	// skill
	else if (::coControl::GetInstance().getKeyControlInfo()[0x5A]){
		if (m_State == ONATTACK){
			mPlayer::onAttack(fdeltatime);
		}
		else {
			m_State = ONATTACK;
			m_attackaccumtime = 0.0f;
			m_spriteAtlas->setCurrentFrame(0);			
		}
	}
	else if (m_State == ONATTACK){
		mPlayer::onAttack(fdeltatime);
	}
	else if (m_State == ONMOVE){
		m_attackaccumtime = 0.0f;
		mPlayer::onMove(fdeltatime);
	}
}


// 피격 시 처리 (체력감소)
void mPlayer::getHit(float dmg){
	mIObject::getHit(dmg);
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
		// Pivot 이미지의 한가운데 바닥 -> dxArea에서 지정
		::D2D1_RECT_F dxArea
			= m_spriteAtlas->getCoordinateFromPivot(cpos);

		//	
		::D2D1_RECT_F srcArea
			= m_spriteAtlas->getSrcFrameFromSprite();

		::cD2DRenderer::GetInstance().GetRenderTarget()->DrawBitmap(m_ipD2DBitmap, dxArea, m_alpha,
			D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
			srcArea);
		
		//회전등에 필요한 부분
		//renderer.GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Identity());

		//debug 용
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
		//회전등에 필요한 부분
		//renderer.GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Identity());

		//debug 용
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
	// 아무래도 키 우선순위는 존재하기 마련이다. 동시 입력이나 잘못 된 입력이 있을때 체킹은 일단 나중으로 미루고
	// 가장 간단한 커맨드와 액션으로 처리하는 걸 처리...
	if (m_qKeyInput.size() < SKILLCOMMAND_MAX){
		if (::coControl::GetInstance().getKeyControlInfo()[VK_LEFT] &&
			::coControl::GetInstance().getKeyControlInfo()[VK_DOWN]){
			if (!m_qKeyInput.empty() && m_qKeyInput.back() != DIRECTION::LEFTDOWN){
				m_qKeyInput.push(DIRECTION::LEFTDOWN);
			}
			else if (m_qKeyInput.empty()) {
				m_qKeyInput.push(DIRECTION::LEFTDOWN);
			}
		}

		else if (::coControl::GetInstance().getKeyControlInfo()[VK_LEFT] &&
			::coControl::GetInstance().getKeyControlInfo()[VK_UP]){
			if (!m_qKeyInput.empty() && m_qKeyInput.back() != DIRECTION::LEFTUP){
				m_qKeyInput.push(DIRECTION::LEFTUP);
			}
			else if (m_qKeyInput.empty()) {
				m_qKeyInput.push(DIRECTION::LEFTUP);
			}
		}

		else if (::coControl::GetInstance().getKeyControlInfo()[VK_RIGHT] &&
			::coControl::GetInstance().getKeyControlInfo()[VK_DOWN]){
			if (!m_qKeyInput.empty() && m_qKeyInput.back() != DIRECTION::RIGHTDOWN){
				m_qKeyInput.push(DIRECTION::RIGHTDOWN);
			}
			else if (m_qKeyInput.empty()) {
				m_qKeyInput.push(DIRECTION::RIGHTDOWN);
			}
		}

		else if (::coControl::GetInstance().getKeyControlInfo()[VK_RIGHT] &&
			::coControl::GetInstance().getKeyControlInfo()[VK_UP]){
			if (!m_qKeyInput.empty() && m_qKeyInput.back() != DIRECTION::RIGHTUP){
				m_qKeyInput.push(DIRECTION::RIGHTUP);
			}
			else if (m_qKeyInput.empty()) {
				m_qKeyInput.push(DIRECTION::RIGHTUP);
			}
		}

		else if (::coControl::GetInstance().getKeyControlInfo()[VK_RIGHT]){
			if (!m_qKeyInput.empty() && m_qKeyInput.back() != DIRECTION::RIGHT){
				m_qKeyInput.push(DIRECTION::RIGHT);
			}
			else if (m_qKeyInput.empty()) {
				m_qKeyInput.push(DIRECTION::RIGHT);
			}
		}
		else if (::coControl::GetInstance().getKeyControlInfo()[VK_LEFT]){
			if (!m_qKeyInput.empty() && m_qKeyInput.back() != DIRECTION::LEFT){
				m_qKeyInput.push(DIRECTION::LEFT);
			}
			else if (m_qKeyInput.empty()){
				m_qKeyInput.push(DIRECTION::LEFT);
			}
		}
		else if (::coControl::GetInstance().getKeyControlInfo()[VK_DOWN]){
			if (!m_qKeyInput.empty() && m_qKeyInput.back() != DIRECTION::DOWN){
				m_qKeyInput.push(DIRECTION::DOWN);
			}
			else if (m_qKeyInput.empty()) {
				m_qKeyInput.push(DIRECTION::DOWN);
			}
		}
		else if (::coControl::GetInstance().getKeyControlInfo()[VK_UP]){
			if (!m_qKeyInput.empty() && m_qKeyInput.back() != DIRECTION::UP){
				m_qKeyInput.push(DIRECTION::UP);
			}
			else if (m_qKeyInput.empty()) {
				m_qKeyInput.push(DIRECTION::UP);
			}
		}
	}
}

bool mPlayer::skillCompare(std::queue<int> keyinput, int* skillArray, int index){
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