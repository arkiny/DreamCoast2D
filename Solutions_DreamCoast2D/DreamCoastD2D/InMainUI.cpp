#include "stdafx.h"
#include "InMainUI.h"
#include "uiButton.h"


InMainUI::InMainUI()
{
	m_pInterface.push_back(new uiButton(135.0f, 530.0f, 0));
}


InMainUI::~InMainUI()
{
}

void InMainUI::Render(cD2DRenderer& renderer){
	for (uiInterface* x : m_pInterface){
		x->Render(renderer);
	}
}

void InMainUI::Update(float delta){
	for (uiInterface* x : m_pInterface){
		x->Update(delta);
	}
}

void InMainUI::OnInit(cD2DRenderer& renderer){
	for (uiInterface* x : m_pInterface){
		x->OnInit(renderer);
	}
}