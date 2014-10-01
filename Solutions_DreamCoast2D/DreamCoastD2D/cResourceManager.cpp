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

// ���� ��� ���ҽ��� ���⼭ �����ϹǷ�
// GameManager ���� �ٸ� �������� SafeRelease�� �����Ѵ�.
cResourceManager::~cResourceManager()
{
	// todo : destructor fix
	SafeRelease(m_Bitmap_Player);
	SafeRelease(m_Bitmap_TileMap);
	SafeRelease(m_Bitmap_Poring);
	SafeRelease(m_Bitmap_MainBG);
	for (int i = 0; i < 20; i++){
		SafeRelease(m_Bitmap_Button[i]);
	}
}

void cResourceManager::load(cD2DRenderer& renderer){	
	HWND hWnd = renderer.GetHwnd();
	m_Bitmap_Player = renderer.CreateD2DBitmapFromFile(hWnd, L"Images/sprites.png", NULL);		// �÷��̾�
	m_Bitmap_TileMap = renderer.CreateD2DBitmapFromFile(hWnd, L"Images/maptile.png", NULL);		// Ÿ�ϸ�
	m_Bitmap_Poring = renderer.CreateD2DBitmapFromFile(hWnd, L"Images/poring.png", NULL);		// ���� ���� �ּ�	
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
	m_ButtonSize[CONFIG] = { 80.0f, 30.0f }; // ���� �÷��̾� �̹����� �̿� ���� ����
}

void cResourceManager::exitMainMenu(){
	SafeRelease(m_Bitmap_MainBG);
	for (int i = 0; i < 20; i++){
		SafeRelease(m_Bitmap_Button[i]);
	}
}

void cResourceManager::releaseGameResource(){
	SafeRelease(m_Bitmap_Player);
	SafeRelease(m_Bitmap_TileMap);
	SafeRelease(m_Bitmap_Poring);
}