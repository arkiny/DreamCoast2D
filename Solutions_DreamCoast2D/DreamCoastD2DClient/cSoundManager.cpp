#include "stdafx.h"
#include "cSoundManager.h"

template<> cSoundManager* Singleton<cSoundManager>::_instance = 0;

cSoundManager::cSoundManager()
{
}


cSoundManager::~cSoundManager()
{
	engine->drop(); // delete engine
}

void cSoundManager::init(){
	engine = irrklang::createIrrKlangDevice();
	if (!engine) {
		m_init = false;
		return; // could not start engine
	}
}

void cSoundManager::executeBGM(){
	if (m_init){
		engine->play2D("Sounds/BGM/title_01.wav", true); // play some mp3 file, looped	
		m_bgmplayinglist = 0;
	}
}

void cSoundManager::executeBGMinGame(){
	if (m_init){
		engine->play2D("Sounds/BGM/stage_01.wav", true); // play some mp3 file, looped	
		m_bgmplayinglist = 1;
	}
}

void cSoundManager::stopBGM(){
	if (m_init){
		if (m_bgmplayinglist == 0){
			engine->removeSoundSource("Sounds/BGM/title_01.wav");
		}
		else if (m_bgmplayinglist == 1){
			engine->removeSoundSource("Sounds/BGM/stage_01.wav");
		}
	}
}

void cSoundManager::executeBeginSpell(){
	if (m_init){
		engine->play2D("Sounds/Effect/ef_beginspell.wav");
	}
}

void cSoundManager::stopBeginSpell(){
	if (m_init){
		engine->removeSoundSource("Sounds/Effect/ef_beginspell.wav");
	}
}

void cSoundManager::executeAttack(){
	if (m_init){
		engine->play2D("Sounds/Effect/_attack_sword.wav");
	}
}

void cSoundManager::executeSkill(int in){
	if (m_init){
		if (in == 0 || in == 1){
			engine->play2D("Sounds/Effect/ef_magnumbreak.wav");
		}
	}
}

void cSoundManager::executeOnHit(int type){
	// todo 차후 무기에 따라서 다른소리
	if (m_init){		
		switch (type)
		{
		case 0:
			engine->play2D("Sounds/Effect/_hit_sword.wav");
			break;
		case 1:
			engine->play2D("Sounds/Effect/_enemy_hit1.wav");
			break;
		default:
			engine->play2D("Sounds/Effect/_hit_sword.wav");
			break;
		}
		
	}
}

void cSoundManager::executeOnDie(int montype){
	// todo 차후 몬스터에 따라서 다른 소리
	if (m_init){
		engine->play2D("Sounds/Monster/poring_die.wav");
	}
}

