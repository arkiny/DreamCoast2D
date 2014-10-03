#include "stdafx.h"
#include "cResourceManager.h"

template<> cResourceManager* Singleton<cResourceManager>::_instance = 0;

cResourceManager::cResourceManager()
{
	m_Bitmap_Player = nullptr;
	m_Bitmap_TileMap = nullptr;
	m_Bitmap_Poring = nullptr;
	m_Bitmap_MainBG = nullptr;
	for (ID2D1Bitmap* x : m_Bitmap_Button){
		x = nullptr;
	}
	for (ID2D1Bitmap* x : m_Bitmap_UI){
		x = nullptr;
	}
	//for (D2D_POINT_2F x : m_ButtonSize){
	//	x = { 0.0f, 0.0f };
	//}
	memset(m_ButtonSize, NULL, BUTTONTYPEMAX);
	memset(m_UI_SIZE, NULL, UIID::UI_ID_MAX);
}

// 이제 모든 리소스는 여기서 관리하므로
// GameManager 이하 다른 곳에서의 SafeRelease는 삭제한다.
cResourceManager::~cResourceManager()
{
	// todo : destructor fix
	SafeRelease(m_Bitmap_Player);
	SafeRelease(m_Bitmap_TileMap);
	SafeRelease(m_Bitmap_Poring);
	SafeRelease(m_Bitmap_MainBG);
	for (ID2D1Bitmap* x : m_Bitmap_Button){
		if (x != nullptr){
			SafeRelease(x);
		}
	}
	for (ID2D1Bitmap* x : m_Bitmap_UI){
		if (x != nullptr){
			SafeRelease(x);
		}
	}
}

void cResourceManager::load(cD2DRenderer& renderer){	
	HWND hWnd = renderer.GetHwnd();
	m_Bitmap_MainBG = renderer.CreateD2DBitmapFromFile(hWnd, L"Images/bg/bg_river.jpg", NULL);
	m_Bitmap_Player = renderer.CreateD2DBitmapFromFile(hWnd, L"Images/sprites.png", NULL);		// 플레이어
	m_Bitmap_TileMap = renderer.CreateD2DBitmapFromFile(hWnd, L"Images/maptile.png", NULL);		// 타일맵
	m_Bitmap_Poring = renderer.CreateD2DBitmapFromFile(hWnd, L"Images/poring.png", NULL);		// 몬스터 포링 주소	
	m_Bitmap_UI[UIID::STATBAR] = renderer.CreateD2DBitmapFromFile(hWnd, L"Images/UI/statbar.png", NULL);
	m_Bitmap_UI[UIID::BLUEBAR] = renderer.CreateD2DBitmapFromFile(hWnd, L"Images/UI/bar_bluebar.png", NULL);
	m_Bitmap_UI[UIID::REDBAR] = renderer.CreateD2DBitmapFromFile(hWnd, L"Images/UI/bar_redbar.png", NULL);
	
	m_Bitmap_UI[UIID::MAP_L_BORDER] = renderer.CreateD2DBitmapFromFile(hWnd, L"Images/UI/ui_bigminimap.png", NULL);
	m_Bitmap_UI[UIID::MAP_TAG] = renderer.CreateD2DBitmapFromFile(hWnd, L"Images/UI/ui_minimaptag.png", NULL);

	m_UI_SIZE[UIID::STATBAR] = { 352.0f, 44.0f };
	m_UI_SIZE[UIID::BLUEBAR] = { 279.0f, 12.0f };
	m_UI_SIZE[UIID::REDBAR] = { 343.0f, 19.0f };
	m_UI_SIZE[UIID::MAP_L_BORDER] = { 210.0f, 210.0f };
	m_UI_SIZE[UIID::MAP_TAG] = { 210.0f, 20.0f };
}

void cResourceManager::loadMainMenuResource(cD2DRenderer& renderer){
	HWND hWnd = renderer.GetHwnd();
	m_Bitmap_MainBG = renderer.CreateD2DBitmapFromFile(hWnd, L"Images/MainMenu/knight1.png", NULL);
	m_Bitmap_Button[SPACETOPLAY] = renderer.CreateD2DBitmapFromFile(hWnd, L"Images/MainMenu/knight-space-start.png", NULL);
	m_Bitmap_Button[NEWGAME] = renderer.CreateD2DBitmapFromFile(hWnd, L"Images/MainMenu/button_newGame.png", NULL);
	m_Bitmap_Button[LOAD] = renderer.CreateD2DBitmapFromFile(hWnd, L"Images/MainMenu/button_load.png", NULL);
	m_Bitmap_Button[CONFIG] = renderer.CreateD2DBitmapFromFile(hWnd, L"Images/MainMenu/button_config.png", NULL);
	m_ButtonSize[SPACETOPLAY] = { 310.0f, 30.0f };
	m_ButtonSize[NEWGAME] = { 130.0f, 30.0f };
	m_ButtonSize[LOAD] = {60.0f, 22.0f};
	m_ButtonSize[CONFIG] = { 80.0f, 30.0f }; 

	// 차후 플레이어 이미지 및 스프라이트 좌표 정보도 이와 같이 관리
}

void cResourceManager::exitMainMenu(){
	SafeRelease(m_Bitmap_MainBG);
	for (ID2D1Bitmap* x : m_Bitmap_Button){
			SafeRelease(x);
	}
}

void cResourceManager::releaseGameResource(){
	SafeRelease(m_Bitmap_Player);
	SafeRelease(m_Bitmap_TileMap);
	SafeRelease(m_Bitmap_Poring);
}