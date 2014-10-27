#include "stdafx.h"
#include "mEffect.h"
#include "cD2DRenderer.h"
#include "cResourceManager.h"
#include "uSprite.h"
#include "VECTOR2D.h"
#include "uCamera.h"


mEffect::mEffect()
{
}

mEffect::mEffect(int type, float dmg, VECTOR2D* cpos, uCamera* cam){
	m_nEffectType = type;
	m_fDmg = dmg;
	m_cpos = cpos;
	m_cam = new uCamera(*cam);
	m_sprite = new uSprite;
}

mEffect::mEffect(int type, int skillEffectType, VECTOR2D* cpos, uCamera* cam){
	m_nEffectType = type;
	m_nSkillEffectType = skillEffectType;
	m_cpos = cpos;
	m_cam = new uCamera(*cam);
	m_sprite = new uSprite;

	switch (m_nSkillEffectType)
	{
	case 0:
		
		m_sprite->pickSpriteAtlas(
			cResourceManager::GetInstance().getEffectSpriteInfo(0)->x, 
			cResourceManager::GetInstance().getEffectSpriteInfo(0)->y, 
			cResourceManager::GetInstance().getEffectSpriteInfo(0)->width, 
			cResourceManager::GetInstance().getEffectSpriteInfo(0)->height, 
			cResourceManager::GetInstance().getEffectSpriteInfo(0)->offsetX, 
			cResourceManager::GetInstance().getEffectSpriteInfo(0)->offsetY, 
			cResourceManager::GetInstance().getEffectSpriteInfo(0)->maxFrame);
		break;
	case 1:
		//m_sprite->pickSpriteAtlas(0.0f, 0.0f, 168.0f, 118.0f, 5);
		m_sprite->pickSpriteAtlas(
			cResourceManager::GetInstance().getEffectSpriteInfo(1)->x,
			cResourceManager::GetInstance().getEffectSpriteInfo(1)->y,
			cResourceManager::GetInstance().getEffectSpriteInfo(1)->width,
			cResourceManager::GetInstance().getEffectSpriteInfo(1)->height,
			cResourceManager::GetInstance().getEffectSpriteInfo(1)->offsetX,
			cResourceManager::GetInstance().getEffectSpriteInfo(1)->offsetY,
			cResourceManager::GetInstance().getEffectSpriteInfo(1)->maxFrame);
		break;
	default:
		break;
	}
}

mEffect::~mEffect()
{
	if (m_nEffectType > 0){
		delete m_sprite;
	}
	delete m_cpos;
	delete m_cam;
	// cam�� �����͸� �޾ƿ°��̹Ƿ� ����� �ȴ�
}

void mEffect::update(float delta){
	switch (m_nEffectType)
	{
	case 0: // font effect
		m_fAlpha -= (1.0f * delta);
		m_cpos->y -= 1.0f;

		if (m_fAlpha <= 0){
			m_endEffect = true;
		}

		break;
	case 1: // using bitmap
		m_sprite->nextFrame(delta);
		// ����Ʈ ���� ����
		if (m_sprite->getCurrentFrame() >= 9){
			m_endEffect = true;
		}
		break;
	default:
		break;
	}
}

void mEffect::render(){
	switch (m_nEffectType)
	{
	case 0:
		if (m_fDmg > 0){
			VECTOR2D cpos = m_cam->translasteToScreen(m_cpos);
			D2D1_RECT_F layoutRect = {
				cpos.x - 20.0f,
				cpos.y - 30.0f,
				cpos.x + 20.0f,
				cpos.y
			};
			/// �ؽ�Ʈ ���
			wchar_t* wszText_ = new wchar_t[20];
			swprintf(wszText_, 20, L" %.0f",
				m_fDmg);
			UINT32 cTextLength_ = (UINT32)wcslen(wszText_);

			// draw text
			::cD2DRenderer::GetInstance().GetRenderTarget()->DrawTextW(
				wszText_,
				cTextLength_,
				::cD2DRenderer::GetInstance().GetTextFormatDmg(),
				layoutRect,
				::cD2DRenderer::GetInstance().GetRedBrush());
			delete[] wszText_;
		}
		break;
	case 1:
	{
		VECTOR2D cpos = m_cam->translasteToScreen(m_cpos);
		::D2D1_RECT_F dxArea
			= m_sprite->getCoordinateFromPivot(cpos);
		::D2D1_RECT_F srcArea
			= m_sprite->getSrcFrameFromSprite();
		if (cResourceManager::GetInstance().getGEffectBitMap(SKILL2) != nullptr){
			::cD2DRenderer::GetInstance().GetRenderTarget()
				->DrawBitmap(cResourceManager::GetInstance().getGEffectBitMap(SKILL2), dxArea, 0.6f,
				D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
				srcArea);
		}
	}
		break;

	default:
		break;
	}
	
}