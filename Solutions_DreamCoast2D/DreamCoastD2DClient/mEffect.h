#pragma once
#include "IEffect.h"


class uSprite;
class uCamera;
class VECTOR2D;

class mEffect : public IEffect
{
public:
	mEffect();
	mEffect(int type, float dmg, VECTOR2D* cpos, uCamera* cam);
	mEffect(int type, int skillEffectType, VECTOR2D* cpos, uCamera* cam);
	~mEffect();

	virtual void update(float);
	virtual void render();
	virtual bool isEnd(){ return m_endEffect; }

private:
	uSprite* m_sprite;
	uCamera* m_cam;
	bool m_endEffect = false;
	float m_fDmg = 0.0f;
	float m_fAlpha = 1.0f;
	int m_nEffectType = 0;
	int m_nSkillEffectType = 0;
	VECTOR2D* m_cpos;
};

