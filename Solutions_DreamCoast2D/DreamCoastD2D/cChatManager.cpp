#include "stdafx.h"
#include "cChatManager.h"
#include "cD2DRenderer.h"

template<> cChatManager* Singleton<cChatManager>::_instance = 0;

cChatManager::cChatManager()
{
}


cChatManager::~cChatManager()
{
}

void cChatManager::OnInit(){

}

void cChatManager::Render(){
	if (m_bVisible){
		::D2D1_RECT_F chatbox = {730.0f, 470.0f, 1000.0f, 710.0f};
		::cD2DRenderer::GetInstance().GetRenderTarget()->FillRectangle(chatbox, ::cD2DRenderer::GetInstance().GetGrayBrush());
		::cD2DRenderer::GetInstance().GetRenderTarget()->DrawRectangle(chatbox, ::cD2DRenderer::GetInstance().GetBlackBrush());
		TCHAR print[1024] = {};
		std::queue<std::string> temp;
		::D2D1_RECT_F chat = { 730.0f, 470.0f, 1000.0f, 710.0f };
		
		std::queue<D2D1_RECT_F> chatline;
		for (int i = 0; i < 10; i++){
			chatline.push({ 730.0f, 470.0f + (24.0f * i), 1000.0f, 470.0f + (24.0f * (i+1)) });
		}

		//int i = 0;
		while (!m_qChat.empty()){			

			_tcscpy_s(print, CA2T(m_qChat.front().c_str()));

			::cD2DRenderer::GetInstance().GetRenderTarget()->DrawText(
				print,
				_tcslen(print),
				::cD2DRenderer::GetInstance().GetTextFormatChat(),
				chatline.front(),
				::cD2DRenderer::GetInstance().GetWhiteBrush());
			temp.push(m_qChat.front());
			m_qChat.pop();

			::cD2DRenderer::GetInstance().GetRenderTarget()->DrawRectangle(chatline.front(), ::cD2DRenderer::GetInstance().GetBlackBrush());
			chatline.pop();
		}
		m_qChat = temp;

	}
}

void cChatManager::Update(float deltaTime){
	if (m_qChat.size() >= 10){
		m_qChat.pop();
	}
}
