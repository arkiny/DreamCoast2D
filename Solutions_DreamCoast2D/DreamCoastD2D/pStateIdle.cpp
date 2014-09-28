#include "stdafx.h"
#include "pStateIdle.h"
#include "mPlayer.h"

void pStateIdle::enter(mPlayer* pplayer){
	m_sprite = pplayer->getSprite();
	//pplayer->onIdle();
}

void pStateIdle::execute(mPlayer* pplayer){

}

void pStateIdle::exit(mPlayer* pplayer){

}