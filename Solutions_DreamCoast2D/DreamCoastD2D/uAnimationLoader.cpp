#include "stdafx.h"
#include "uAnimationLoader.h"


uAnimationLoader::uAnimationLoader()
{
	
}


uAnimationLoader::~uAnimationLoader()
{
	while (!m_vecSprite.empty()){
		delete m_vecSprite.back();
		m_vecSprite.pop_back();
	}
	m_vecSprite.clear();

	while (!m_vecAnimation.empty()){
		delete m_vecAnimation.back();
		m_vecAnimation.pop_back();
	}
	m_vecAnimation.clear();
}


void uAnimationLoader::LoadAnimationFileInfo(const char* szFileName)
{
	char szBuf[1024];

	FILE* fp;
	errno_t err;
	err = fopen_s(&fp, szFileName, "r");
	if (err != 0)
	{
		// error message
		wchar_t szDebug[128];
		wsprintf(szDebug, L"%s 파일 읽기 에러");
		MessageBox(NULL, szDebug, L"Error", MB_OK);
		return;
	}

	while (!feof(fp))
	{
		fgets(szBuf, 1024, fp);
		if (szBuf[0] == '#')
		{
			continue;
		}
		else if (szBuf[0] == 'a')
		{
			char fileName[1024];
			LPAnimationInfo ani = new AnimationInfo;
			
			sscanf_s(szBuf, "%*s %d %f %s",
				ani->seq_id,
				ani->ani_time,
				fileName, 1024);

			ani->strFilaName = fileName;

			m_vecAnimation.push_back(ani);
			ani = nullptr;
		}
	}
	fclose(fp);
}

void uAnimationLoader::LoadSprites(const char* szFileName)
{
	char szBuf[1024];

	FILE* fp;
	errno_t err;
	err = fopen_s(&fp, szFileName, "r");
	if (err != 0)
	{
		// error message
		return;
	}

	while (!feof(fp))
	{
		fgets(szBuf, 1024, fp);
		if (szBuf[0] == '#')
		{
			continue;
		}
		else if (szBuf[0] == 's')
		{
			LPSpriteAnimation sprite = new SpriteAnimation;

			sscanf_s(szBuf, "%*s %f %f %f %f %f %f %d",
				sprite->x,
				sprite->y,
				sprite->width,
				sprite->height,
				sprite->offsetX,
				sprite->offsetY,
				sprite->maxFrame);

			m_vecSprite.push_back(sprite);
		}
	}
	fclose(fp);
}