#include "stdafx.h"
#include "cChatManager.h"
#include "cD2DRenderer.h"
#include "cResourceManager.h"

template<> cChatManager* Singleton<cChatManager>::_instance = 0;

cChatManager::cChatManager()
{
	
}


cChatManager::~cChatManager()
{
}

void cChatManager::OnInit(){
	cResourceManager::GetInstance().loadChatWindow();
}

void cChatManager::Render(){
	if (m_bVisible){
		if (cResourceManager::GetInstance().getChatWindowBitMap() != nullptr){
			::D2D1_RECT_F dxArea
				= { 730.0f, 470.0f, 1000.0f, 710.0f };
			::D2D1_RECT_F srcArea
				= { 0, 0, cResourceManager::GetInstance().getChatWindowSize().x, cResourceManager::GetInstance().getChatWindowSize().y };

			::cD2DRenderer::GetInstance().GetRenderTarget()
				->DrawBitmap(cResourceManager::GetInstance().getChatWindowBitMap(), dxArea, 0.6f,
				D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
				srcArea);
		}
		else {
			::D2D1_RECT_F chatbox = { 730.0f, 470.0f, 1000.0f, 710.0f };
			::cD2DRenderer::GetInstance().GetRenderTarget()->FillRectangle(chatbox, ::cD2DRenderer::GetInstance().GetGrayBrush());
			::cD2DRenderer::GetInstance().GetRenderTarget()->DrawRectangle(chatbox, ::cD2DRenderer::GetInstance().GetBlackBrush());
		}

		TCHAR print[1024] = {};
		std::queue<std::string> temp;
		::D2D1_RECT_F chat = { 730.0f, 470.0f, 1000.0f, 710.0f };
		std::queue<D2D1_RECT_F> chatline;
		for (int i = 0; i < 10; i++){
			chatline.push({ 738.0f, 476.0f + (23.2f * i), 992.0f, 476.0f + (23.2f * (i+1)) });
		}

		//int i = 0;
		while (!m_qChat.empty()){			
			_tcscpy_s(print, CA2T(m_qChat.front().c_str()));
			::cD2DRenderer::GetInstance().GetRenderTarget()->DrawText(
				print,
				_tcslen(print),
				::cD2DRenderer::GetInstance().GetTextFormatChat(),
				chatline.front(),
				::cD2DRenderer::GetInstance().GetBlackBrush());
			temp.push(m_qChat.front());
			m_qChat.pop();

			::cD2DRenderer::GetInstance().GetRenderTarget()->DrawRectangle(chatline.front(), 
				::cD2DRenderer::GetInstance().GetBlackBrush());
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
