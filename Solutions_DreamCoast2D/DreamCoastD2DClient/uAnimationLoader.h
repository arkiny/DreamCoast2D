#pragma once
#include <vector>

typedef struct SpriteAnimation{
	float x;
	float y; 
	float width; 
	float height; 
	float offsetX; 
	float offsetY; 
	int maxFrame; // ½ÇÁ¦ maxFrame - 1;
} *LPSpriteAnimation;

typedef struct AnimationInfo
{
	int seq_id;
	float ani_time;
	std::string strFilaName;
}*LPAnimationInfo;



class uAnimationLoader
{
public:
	uAnimationLoader();
	~uAnimationLoader();
	void LoadSprites(const char* szFileName);
	void LoadAnimationFileInfo(const char* szFileName);

private:
	std::vector<LPSpriteAnimation> m_vecSprite;
	std::vector<LPAnimationInfo> m_vecAnimation;
};

