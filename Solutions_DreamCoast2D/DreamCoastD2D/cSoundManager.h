#pragma once
#include <irrKlang.h>
#pragma comment(lib, "irrKlang.lib")

#include "Singleton.h"


class cSoundManager : public Singleton<cSoundManager>
{
public:
	cSoundManager();
	~cSoundManager();

	void init();
	void executeBGM();
	void executeBGMinGame();
	void executeBeginSpell();
	void stopBeginSpell();

	void executeAttack();
	void executeSkill(int);
	
	void stopBGM();

private:
	irrklang::ISoundEngine* engine;
	int m_bgmplayinglist;
};

