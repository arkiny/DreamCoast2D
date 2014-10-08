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
	if (!engine) return; // could not start engine
}

void cSoundManager::executeBGM(){
	engine->play2D("Sounds/BGM/title_01.wav", true); // play some mp3 file, looped	
	m_bgmplayinglist = 0;
}

void cSoundManager::executeBGMinGame(){
	engine->play2D("Sounds/BGM/stage_01.wav", true); // play some mp3 file, looped	
	m_bgmplayinglist = 1;
}

void cSoundManager::stopBGM(){
	if (m_bgmplayinglist == 0){
		engine->removeSoundSource("Sounds/BGM/title_01.wav");
	}
	else if (m_bgmplayinglist == 1){
		engine->removeSoundSource("Sounds/BGM/stage_01.wav");
	}
}

void cSoundManager::executeBeginSpell(){
	engine->play2D("Sounds/Effect/ef_beginspell.wav");
}

void cSoundManager::stopBeginSpell(){
	engine->removeSoundSource("Sounds/Effect/ef_beginspell.wav");
}

void cSoundManager::executeAttack(){
	engine->play2D("Sounds/Effect/_attack_sword.wav");
}

void cSoundManager::executeSkill(int in){
	if (in == 0){
		engine->play2D("Sounds/Effect/ef_magnumbreak.wav");
	}
}

