#include "stdafx.h"
#include "mEffect.h"
#include "cD2DRenderer.h"
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
}

mEffect::mEffect(int type, int skillEffectType, VECTOR2D* cpos, uCamera* cam){
	m_nEffectType = type;
	m_nSkillEffectType = skillEffectType;
	m_cpos = cpos;
	m_cam = new uCamera(*cam);
}

mEffect::~mEffect()
{
	if (m_nEffectType > 0){
		delete m_sprite;
	}
	delete m_cpos;
	delete m_cam;
	// cam은 포인터를 받아온것이므로 지우면 안댐
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
			/// 텍스트 출력
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
		break;
	default:
		break;
	}
	
}