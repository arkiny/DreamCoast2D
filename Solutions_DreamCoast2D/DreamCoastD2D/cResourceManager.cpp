#include "stdafx.h"
#include "cResourceManager.h"

template<> cResourceManager* Singleton<cResourceManager>::_instance = 0;

cResourceManager::cResourceManager()
{
	m_Bitmap_Player = nullptr;
	m_Bitmap_TileMap = nullptr;
	m_Bitmap_Poring = nullptr;
	m_Bitmap_MainBG = nullptr;
	for (int i = 0; i < 20; i++){
		m_Bitmap_Button[i] = nullptr;
	}
}

cResourceManager::~cResourceManager()
{
	// todo : destructor fix
	SafeRelease(m_Bitmap_Player);
	SafeRelease(m_Bitmap_TileMap);
	SafeRelease(m_Bitmap_Poring);
	//SafeRelease(m_Bitmap_MainBG);
	/*for (int i = 0; i < 20; i++){
		SafeRelease(m_Bitmap_Button[i]);
	}*/
	/*if (m_Bitmap_Button != NULL){
		delete[] m_Bitmap_Button;
	}*/
}

void cResourceManager::load(cD2DRenderer& renderer){

	//
	/*SafeRelease(m_Bitmap_MainBG);
	for (int i = 0; i < 20; i++){
		SafeRelease(m_Bitmap_Button[i]);
	}
	if (m_Bitmap_Button != NULL){
		delete[] m_Bitmap_Button;
	}*/
	//

	HWND hWnd = renderer.GetHwnd();
	m_Bitmap_Player = renderer.CreateD2DBitmapFromFile(hWnd, L"Images/sprites.png", NULL);		// 플레이어
	m_Bitmap_TileMap = renderer.CreateD2DBitmapFromFile(hWnd, L"Images/maptile.png", NULL);		// 타일맵
	m_Bitmap_Poring = renderer.CreateD2DBitmapFromFile(hWnd, L"Images/poring.png", NULL);		// 몬스터 포링 주소	
}

void cResourceManager::loadMainMenuResource(cD2DRenderer& renderer){
	HWND hWnd = renderer.GetHwnd();
	m_Bitmap_MainBG = renderer.CreateD2DBitmapFromFile(hWnd, L"Images/MainMenu/knight1.png", NULL);
	m_Bitmap_Button[SPACETOPLAY] = renderer.CreateD2DBitmapFromFile(hWnd, L"Images/MainMenu/knight-space-start.png", NULL);
	m_Bitmap_Button[NEWGAME] = renderer.CreateD2DBitmapFromFile(hWnd, L"Images/MainMenu/button_newGame.png", NULL);
	m_Bitmap_Button[LOAD] = renderer.CreateD2DBitmapFromFile(hWnd, L"Images/MainMenu/button_load.png", NULL);
	m_Bitmap_Button[CONFIG] = renderer.CreateD2DBitmapFromFile(hWnd, L"Images/MainMenu/button_config.png", NULL);
}