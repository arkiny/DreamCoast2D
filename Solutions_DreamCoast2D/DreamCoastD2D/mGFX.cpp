#include "stdafx.h"
#include "mGFX.h"

template<> mGFX* Singleton<mGFX>::_instance = 0;

mGFX::mGFX()
{
}


mGFX::~mGFX()
{
}

void mGFX::pushToEventQueue(IEffect* effect){
	m_qEffects.push(effect);
}

void mGFX::update(float delta){
	std::queue<IEffect*> tempQueue;
	
	while (!m_qEffects.empty()){
		m_qEffects.front()->update(delta);

		if (!m_qEffects.front()->isEnd()){
			tempQueue.push(m_qEffects.front());
		}
		m_qEffects.pop();
	}

	m_qEffects = tempQueue;
}

void mGFX::render(){
	std::queue<IEffect*> tempQueue;	
	while (!m_qEffects.empty()){
		m_qEffects.front()->render();	
		tempQueue.push(m_qEffects.front());		
		m_qEffects.pop();
	}
	m_qEffects = tempQueue;
}