#include "stdafx.h"
#include "sEditScreen.h"
#include "sGameScreen.h"
#include "wWorld.h"
#include "wTileMap.h"
#include "uCamera.h"
#include "cResourceManager.h"
#include "cD2DRenderer.h"
#include "cGameManager.h"
#include "coControl.h"
#include "uFileControl.h"
#include "mPlayer.h"
#include "VECTOR2D.h"
#include "mGFX.h"
#include "uSprite.h"

sEditScreen::sEditScreen(cGameManager* cg)
{
	m_pWorld = nullptr;
	m_pGameManager = cg;
	m_sprite = new uSprite;
	m_nHook = 0;
	m_sprite->pickSpriteAtlas(
		cResourceManager::GetInstance().getMapSpriteInfo(0, 0)->x,
		cResourceManager::GetInstance().getMapSpriteInfo(0, 0)->y,
		cResourceManager::GetInstance().getMapSpriteInfo(0, 0)->width,
		cResourceManager::GetInstance().getMapSpriteInfo(0, 0)->height,
		cResourceManager::GetInstance().getMapSpriteInfo(0, 0)->maxFrame);
}


sEditScreen::~sEditScreen()
{
	if (m_pWorld != NULL){
		delete m_pWorld;
	}
	if (m_sprite != nullptr){
		delete m_sprite;
	}
}

void sEditScreen::setWorld(wWorld* in){
	if (m_pWorld != NULL){
		delete m_pWorld;
	}
	m_pWorld = in;
}

void sEditScreen::Render(){
	m_pWorld->RenderEdit();
	mGFX::GetInstance().render();

	/// 간단한 UI
	POINTFLOAT uipos = { 15.0f, 15.0f };
	if (cResourceManager::GetInstance().getUIBitMap(UIID::UI_HOOK)){		
		::D2D1_RECT_F dxArea
			= { uipos.x,
			uipos.y,
			uipos.x + ::cResourceManager::GetInstance().getUISize(UIID::UI_HOOK).x,
			uipos.y + ::cResourceManager::GetInstance().getUISize(UIID::UI_HOOK).y };
		::D2D1_RECT_F srcArea
			= { 0, 0,
			::cResourceManager::GetInstance().getUISize(UIID::UI_HOOK).x,
			::cResourceManager::GetInstance().getUISize(UIID::UI_HOOK).y };

		::cD2DRenderer::GetInstance().GetRenderTarget()
			->DrawBitmap(::cResourceManager::GetInstance().getUIBitMap(UIID::UI_HOOK), dxArea, 1.0f,
			D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
			srcArea);
	}
	//POINTFLOAT stpos = { 19.0f, 19.0f };
	switch (m_nHook)
	{
	case 0:
	case 1:
	case 2:
	case 3:
	case 4:
	{
		if (cResourceManager::GetInstance().getTileMapBitMap() != nullptr){
			// Pivot 이미지의 한가운데 바닥 -> dxArea에서 지정
			::D2D1_RECT_F dxArea
				= { 19.0f, 19.0f, 145.0f, 145.0f };

			//	
			::D2D1_RECT_F srcArea
				= m_sprite->getSrcFrameFromSprite();

			::cD2DRenderer::GetInstance().GetRenderTarget()->DrawBitmap(cResourceManager::GetInstance().getTileMapBitMap(),
				dxArea, 1.0f,
				D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
				srcArea);

			//회전등에 필요한 부분
			//renderer.GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Identity());	
	}
	break; }
	
	case 5:{
		//::cResourceManager::GetInstance().getMobBitMap(m_nMonsterType)
		if (::cResourceManager::GetInstance().getMobBitMap(0) != nullptr){			
			// Pivot 이미지의 한가운데 바닥 -> dxArea에서 지정
			::D2D1_RECT_F dxArea
				= { 19.0f, 19.0f, 145.0f, 145.0f };			
			::D2D1_RECT_F srcArea
				= m_sprite->getSrcFrameFromSprite();
			::cD2DRenderer::GetInstance().GetRenderTarget()->DrawBitmap(
				::cResourceManager::GetInstance().getMobBitMap(0), dxArea, 1.0f,
					D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
					srcArea);			
		}
		break; }
	case 6:{
		if (::cResourceManager::GetInstance().getMobBitMap(0) != nullptr){
			// Pivot 이미지의 한가운데 바닥 -> dxArea에서 지정
			::D2D1_RECT_F dxArea
				= { 19.0f, 19.0f, 145.0f, 145.0f };
			::D2D1_RECT_F srcArea
				= m_sprite->getSrcFrameFromSprite();
			::cD2DRenderer::GetInstance().GetRenderTarget()->DrawBitmap(
				::cResourceManager::GetInstance().getMobBitMap(0), dxArea, 1.0f,
				D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
				srcArea);
		}
		break; }
	case 7:{
		if (::cResourceManager::GetInstance().getMobBitMap(2) != nullptr){
			// Pivot 이미지의 한가운데 바닥 -> dxArea에서 지정
			::D2D1_RECT_F dxArea
				= { 19.0f, 19.0f, 145.0f, 145.0f };
			::D2D1_RECT_F srcArea
				= m_sprite->getSrcFrameFromSprite();
			::cD2DRenderer::GetInstance().GetRenderTarget()->DrawBitmap(
				::cResourceManager::GetInstance().getMobBitMap(2), dxArea, 1.0f,
				D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
				srcArea);
		}
		break; }
	default:{
		::D2D1_RECT_F dxArea
			= { 19.0f, 19.0f, 145.0f, 145.0f };

		wchar_t* wszText_ = new wchar_t[10];
		int length = 0;
		length += swprintf(wszText_ + length, 10, L"No Image");
		UINT32 cTextLength_ = (UINT32)wcslen(wszText_);

		::cD2DRenderer::GetInstance().GetRenderTarget()->DrawTextW(
			wszText_,
			cTextLength_,
			::cD2DRenderer::GetInstance().GetTextFormat(),
			dxArea,
			::cD2DRenderer::GetInstance().GetBlackBrush());

		delete[] wszText_;
	}
		break;
	}
	///
}

void sEditScreen::Update(float deltaTime){

	if (coControl::GetInstance().getKeyControlInfo()[VK_TAB]){
		coControl::GetInstance().onKeyUp(VK_TAB);
		sGameScreen* input = new sGameScreen(m_pGameManager);
		m_pGameManager->changeScreen(input);
		return;
	}

	// if keydown 's' save map as a binary file
	if (coControl::GetInstance().getKeyControlInfo()[0x53]){
		coControl::GetInstance().onKeyUp(0x53);
		uFileControl save = uFileControl(m_pWorld);
		save.SaveToFile(1);
		return;
	}

	if (::coControl::GetInstance().getKeyControlInfo()[0x30]){
		::coControl::GetInstance().onKeyUp(0x30);
		m_nHook = TILE_EMPTY;
		m_sprite->pickSpriteAtlas(
			cResourceManager::GetInstance().getMapSpriteInfo(0, 0)->x,
			cResourceManager::GetInstance().getMapSpriteInfo(0, 0)->y,
			cResourceManager::GetInstance().getMapSpriteInfo(0, 0)->width,
			cResourceManager::GetInstance().getMapSpriteInfo(0, 0)->height,
			cResourceManager::GetInstance().getMapSpriteInfo(0, 0)->maxFrame);
	}
	if (::coControl::GetInstance().getKeyControlInfo()[0x31]){
		::coControl::GetInstance().onKeyUp(0x31);
		m_nHook = TILE_CANNOTMOVE;
		m_sprite->pickSpriteAtlas(
			cResourceManager::GetInstance().getMapSpriteInfo(0, 1)->x,
			cResourceManager::GetInstance().getMapSpriteInfo(0, 1)->y,
			cResourceManager::GetInstance().getMapSpriteInfo(0, 1)->width,
			cResourceManager::GetInstance().getMapSpriteInfo(0, 1)->height,
			cResourceManager::GetInstance().getMapSpriteInfo(0, 1)->maxFrame);
	}
	if (::coControl::GetInstance().getKeyControlInfo()[0x32]){
		::coControl::GetInstance().onKeyUp(0x32);
		m_nHook = TILE_HIGH_GROUND;
		m_sprite->pickSpriteAtlas(
			cResourceManager::GetInstance().getMapSpriteInfo(1, 0)->x,
			cResourceManager::GetInstance().getMapSpriteInfo(1, 0)->y,
			cResourceManager::GetInstance().getMapSpriteInfo(1, 0)->width,
			cResourceManager::GetInstance().getMapSpriteInfo(1, 0)->height,
			cResourceManager::GetInstance().getMapSpriteInfo(1, 0)->offsetX,
			cResourceManager::GetInstance().getMapSpriteInfo(1, 0)->offsetY,
			cResourceManager::GetInstance().getMapSpriteInfo(1, 0)->maxFrame);
	}
	if (::coControl::GetInstance().getKeyControlInfo()[0x33]){
		::coControl::GetInstance().onKeyUp(0x33);
		m_nHook = TILE_TREE;
		m_sprite->pickSpriteAtlas(
			cResourceManager::GetInstance().getMapSpriteInfo(1, 1)->x,
			cResourceManager::GetInstance().getMapSpriteInfo(1, 1)->y,
			cResourceManager::GetInstance().getMapSpriteInfo(1, 1)->width,
			cResourceManager::GetInstance().getMapSpriteInfo(1, 1)->height,
			cResourceManager::GetInstance().getMapSpriteInfo(1, 1)->offsetX,
			cResourceManager::GetInstance().getMapSpriteInfo(1, 1)->offsetY,
			cResourceManager::GetInstance().getMapSpriteInfo(1, 1)->maxFrame);
	}
	if (::coControl::GetInstance().getKeyControlInfo()[0x34]){
		::coControl::GetInstance().onKeyUp(0x34);
		m_nHook = TILE_BUILDING;
		// 이동불가로 만들 타일 범위 설정 납작한 2번으로 다 설정해버림 됨
		m_sprite->pickSpriteAtlas(
			cResourceManager::GetInstance().getMapSpriteInfo(1, 2)->x,
			cResourceManager::GetInstance().getMapSpriteInfo(1, 2)->y,
			cResourceManager::GetInstance().getMapSpriteInfo(1, 2)->width,
			cResourceManager::GetInstance().getMapSpriteInfo(1, 2)->height,
			cResourceManager::GetInstance().getMapSpriteInfo(1, 2)->offsetX,
			cResourceManager::GetInstance().getMapSpriteInfo(1, 2)->offsetY,
			cResourceManager::GetInstance().getMapSpriteInfo(1, 2)->maxFrame);
	}
	if (::coControl::GetInstance().getKeyControlInfo()[0x51]){
		::coControl::GetInstance().onKeyUp(0x51);
		// 이동불가로 만들 타일 범위 설정 납작한 2번으로 다 설정해버림 됨
		m_nHook = MOB_PORING;		
		SpriteAnimationInfo* in = cResourceManager::GetInstance().getMonsterSpriteInfo(0, 0, 0);
		//SpriteAnimationInfo* in = cResourceManager::GetInstance().getMonsterSpriteInfo(2, 0, 0);
		m_sprite->pickSpriteAtlas(
			in->x,
			in->y,
			in->width,
			in->height,
			in->offsetX,
			in->offsetY,
			in->maxFrame);
	}
	if (::coControl::GetInstance().getKeyControlInfo()[0x57]){
		::coControl::GetInstance().onKeyUp(0x57);
		// 이동불가로 만들 타일 범위 설정 납작한 2번으로 다 설정해버림 됨
		m_nHook = MOB_PORING_A;
		SpriteAnimationInfo* in = cResourceManager::GetInstance().getMonsterSpriteInfo(0, 0, 0);
		//SpriteAnimationInfo* in = cResourceManager::GetInstance().getMonsterSpriteInfo(2, 0, 0);
		m_sprite->pickSpriteAtlas(
			in->x,
			in->y,
			in->width,
			in->height,
			in->offsetX,
			in->offsetY,
			in->maxFrame);
	}
	if (::coControl::GetInstance().getKeyControlInfo()[0x45]){
		::coControl::GetInstance().onKeyUp(0x45);
		// 이동불가로 만들 타일 범위 설정 납작한 2번으로 다 설정해버림 됨
		m_nHook = MOB_BAPO;
		SpriteAnimationInfo* in = cResourceManager::GetInstance().getMonsterSpriteInfo(2, 0, 0);
		//SpriteAnimationInfo* in = cResourceManager::GetInstance().getMonsterSpriteInfo(2, 0, 0);
		m_sprite->pickSpriteAtlas(
			in->x,
			in->y,
			in->width,
			in->height,
			in->offsetX,
			in->offsetY,
			in->maxFrame);
	}


	if (::coControl::GetInstance().getKeyControlInfo()[VK_LBUTTON]){		
		::coControl::GetInstance().onKeyUp(VK_LBUTTON);
		VECTOR2D clickpoint(::coControl::GetInstance().getClickPosition().x, ::coControl::GetInstance().getClickPosition().y);
		float x = m_pWorld->getMap()->getCamera()->getX();
		float y = m_pWorld->getMap()->getCamera()->getY();
		clickpoint.x = clickpoint.x + x;
		clickpoint.y = clickpoint.y + y;

		VECTOR2D mousecoord = m_pWorld->getMap()
			->getTileCoordinates(clickpoint);
		if (m_nHook >= 0 && m_nHook <= 1){
			if (mousecoord.x >= 0.0f && mousecoord.y >= 0.0f &&
				mousecoord.x < m_pWorld->getMap()->getMapLimit().x&&
				mousecoord.y < m_pWorld->getMap()->getMapLimit().y){

				// 여기에 고른 타일이나 몬스터에 따라 추가하는 choose 명령어를 넣는다.
				m_pWorld->getMap()->setTile(mousecoord.x, mousecoord.y, m_nHook);
				m_pWorld->getMap()->removeMapObjectFromTile(mousecoord.x, mousecoord.y);
			}
		}
		else if (m_nHook == TILE_HIGH_GROUND){
			if (mousecoord.x >= 0.0f && mousecoord.y >= 0.0f &&
				mousecoord.x < m_pWorld->getMap()->getMapLimit().x&&
				mousecoord.y < m_pWorld->getMap()->getMapLimit().y){

				// 여기에 고른 타일이나 몬스터에 따라 추가하는 choose 명령어를 넣는다.
				m_pWorld->getMap()->setTile(mousecoord.x, mousecoord.y, 1);
				m_pWorld->getMap()->addMapObjectTotile(mousecoord.y, mousecoord.x, 2);
			}
		}
		else if (m_nHook == TILE_TREE){
			if (mousecoord.x >= 0.0f && mousecoord.y >= 0.0f &&
				mousecoord.x < m_pWorld->getMap()->getMapLimit().x&&
				mousecoord.y < m_pWorld->getMap()->getMapLimit().y){

				// 여기에 고른 타일이나 몬스터에 따라 추가하는 choose 명령어를 넣는다.
				m_pWorld->getMap()->setTile(mousecoord.x, mousecoord.y, 1);
				m_pWorld->getMap()->addMapObjectTotile(mousecoord.y, mousecoord.x, 1);
			}
		}
		else if (m_nHook == TILE_BUILDING){
			if (mousecoord.x >= 0.0f && mousecoord.y >= 0.0f &&
				mousecoord.x < m_pWorld->getMap()->getMapLimit().x&&
				mousecoord.y < m_pWorld->getMap()->getMapLimit().y){

				m_pWorld->getMap()->addMapObjectTotile(mousecoord.y, mousecoord.x, 0);
				
				// 여기에 고른 타일이나 몬스터에 따라 추가하는 choose 명령어를 넣는다.
				m_pWorld->getMap()->setTile(mousecoord.x, mousecoord.y, 1);

				//if (mousecoord.y + 1.0f <= m_pWorld->getMap()->getMapLimit().y){
				//	m_pWorld->getMap()->setTile(mousecoord.x, mousecoord.y + 1.0f, 1);
				//}
				//if (mousecoord.y + 2.0f <= m_pWorld->getMap()->getMapLimit().y){
				//	m_pWorld->getMap()->setTile(mousecoord.x, mousecoord.y + 2.0f, 1);
				//}
				//if (mousecoord.x - 1.0f >= 0){
				//	m_pWorld->getMap()->setTile(mousecoord.x - 1.0f, mousecoord.y, 1);
				//}
				//if (mousecoord.x - 1.0f >= 0 && mousecoord.y + 1.0f <= m_pWorld->getMap()->getMapLimit().y){
				//	m_pWorld->getMap()->setTile(mousecoord.x - 1.0f, mousecoord.y + 1.0f, 1);
				//}
				//if (mousecoord.x - 1.0f >= 0 && mousecoord.y + 2.0f <= m_pWorld->getMap()->getMapLimit().y){
				//	m_pWorld->getMap()->setTile(mousecoord.x - 1.0f, mousecoord.y + 2.0f, 1);
				//}
				//if (mousecoord.x - 2.0f >= 0){
				//	m_pWorld->getMap()->setTile(mousecoord.x - 2.0f, mousecoord.y, 1);
				//}
				//if (mousecoord.x - 2.0f >= 0 && mousecoord.y + 1.0f <= m_pWorld->getMap()->getMapLimit().y){
				//	m_pWorld->getMap()->setTile(mousecoord.x - 2.0f, mousecoord.y + 1.0f, 1);
				//}
				//if (mousecoord.x - 2.0f >= 0 && mousecoord.y + 2.0f <= m_pWorld->getMap()->getMapLimit().y){
				//	m_pWorld->getMap()->setTile(mousecoord.x - 2.0f, mousecoord.y + 2.0f, 1);
				//}

				if (mousecoord.y - 1.0f >= 0){
					m_pWorld->getMap()->setTile(mousecoord.x, mousecoord.y - 1.0f, 1);
				}
				if (mousecoord.y + 1.0f <= m_pWorld->getMap()->getMapLimit().y){
					m_pWorld->getMap()->setTile(mousecoord.x, mousecoord.y + 1.0f, 1);
				}
				if (mousecoord.x - 1.0f >= 0){
					m_pWorld->getMap()->setTile(mousecoord.x - 1.0f, mousecoord.y, 1);
				}
				if (mousecoord.x - 1.0f >= 0 && mousecoord.y - 1.0f >= 0){
					m_pWorld->getMap()->setTile(mousecoord.x - 1.0f, mousecoord.y - 1.0f, 1);
				}
				if (mousecoord.x - 1.0f >= 0 && mousecoord.y <= m_pWorld->getMap()->getMapLimit().y){
					m_pWorld->getMap()->setTile(mousecoord.x - 1.0f, mousecoord.y + 1.0f, 1);
				}
				if (mousecoord.x + 1.0f >= 0){
					m_pWorld->getMap()->setTile(mousecoord.x - 2.0f, mousecoord.y, 1);
				}
				if (mousecoord.x + 1.0f >= 0 && mousecoord.y - 1.0f >= 0){
					m_pWorld->getMap()->setTile(mousecoord.x - 2.0f, mousecoord.y - 1.0f, 1);
				}
				if (mousecoord.x + 1.0f >= 0 && mousecoord.y + 1.0f <= m_pWorld->getMap()->getMapLimit().y){
					m_pWorld->getMap()->setTile(mousecoord.x - 2.0f, mousecoord.y + 1.0f, 1);
				}


				/*if (mousecoord.x + 1.0f <= m_pWorld->getMap()->getMapLimit().x && mousecoord.y <= m_pWorld->getMap()->getMapLimit().y){
					m_pWorld->getMap()->setTile(mousecoord.x + 1.0f, mousecoord.y , 1);
				}*/
				//if (mousecoord.x + 1.0f <= m_pWorld->getMap()->getMapLimit().x && mousecoord.y - 1.0f >= 0){
				//	// 차후 알맞은 타일로 교체
				//	m_pWorld->getMap()->setTile(mousecoord.x + 1.0f, mousecoord.y - 1.0f, 1);
				//}
				//if (mousecoord.x + 1.0f <= m_pWorld->getMap()->getMapLimit().x && mousecoord.y - 2.0f >= 0){
				//	// 차후 알맞은 타일료 교체
				//	m_pWorld->getMap()->setTile(mousecoord.x + 1.0f, mousecoord.y - 2.0f, 1);
				//}
				//if (mousecoord.x + 2.0f <= m_pWorld->getMap()->getMapLimit().x && mousecoord.y - 1.0f >= 0){
				//	// 차후 알맞은 타일로 교체
				//	m_pWorld->getMap()->setTile(mousecoord.x + 2.0f, mousecoord.y-1.0f, 1);
				//}
			}
		}
		else if (m_nHook == MOB_PORING){
			m_pWorld->getMap()->addMonsterTotile(mousecoord.y, mousecoord.x, 0);
		}
		else if (m_nHook == MOB_PORING_A){
			m_pWorld->getMap()->addMonsterTotile(mousecoord.y, mousecoord.x, 1);
		}
		else if (m_nHook == MOB_BAPO){
			m_pWorld->getMap()->addMonsterTotile(mousecoord.y, mousecoord.x, 2);
		}
	}
	m_pWorld->Update(deltaTime);
	mGFX::GetInstance().update(deltaTime);
}

void sEditScreen::OnInit(){
	m_pWorld = new wWorld();
	//::cResourceManager::GetInstance().load();
	m_pWorld->OnInit(1);
	// 맵툴용 캐릭터 설정
	m_pWorld->getPlayer()->setAttackPower(1000.0f);
	m_pWorld->getPlayer()->setMAXHealth(10000.0f);
	m_pWorld->getPlayer()->setHealth(10000.0f);
	m_pWorld->getPlayer()->setMoveSpeed(300.0f);
}

void sEditScreen::OnExit(){	
	//::cResourceManager::GetInstance().releaseGameResource();
	this->~sEditScreen();
}