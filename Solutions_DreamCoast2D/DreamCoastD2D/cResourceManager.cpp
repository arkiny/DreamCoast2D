#include "stdafx.h"
#include "cResourceManager.h"
#include "atlstr.h"
#include "atlbase.h"


template<> cResourceManager* Singleton<cResourceManager>::_instance = 0;

cResourceManager::cResourceManager()
{
	m_Bitmap_Player = nullptr;
	m_Bitmap_TileMap = nullptr;

	for (ID2D1Bitmap* x : m_Bitmap_MoB){
		x = nullptr;
	}

	m_Bitmap_MainBG = nullptr;
	for (ID2D1Bitmap* x : m_Bitmap_Button){
		x = nullptr;
	}
	for (ID2D1Bitmap* x : m_Bitmap_UI){
		x = nullptr;
	}
	for (ID2D1Bitmap* x : m_Bitmap_Item_Consume){
		x = nullptr;
	}
	for (ID2D1Bitmap* x : m_Bitmap_Effect){
		x = nullptr;
	}
	for (ID2D1Bitmap* x : m_Bitmap_MapObject){
		x = nullptr;
	}

	//for (TCHAR* x : m_File_path){
	//	x = nullptr;
	//}

	//for (D2D_POINT_2F x : m_ButtonSize){
	//	x = { 0.0f, 0.0f };
	//}
	memset(m_ButtonSize, NULL, sizeof(m_ButtonSize));
	memset(m_UI_SIZE, NULL, sizeof(m_UI_SIZE));
	memset(m_Size_Item_Consume, NULL, sizeof(m_Size_Item_Consume));
	memset(m_Size_Effect, NULL, sizeof(m_Size_Effect));
	memset(m_MapObject_Size, NULL, sizeof(m_MapObject_Size));

	loadFilePath("./Data/filepath.txt");
	loadNormalSpritePath("./Data/filepath_NormalSprite.txt");
	loadMobSpritePath("./Data/filepath_MobSprite.txt");

	for (unsigned int i = 0; i < m_vecNormalSpriteFilePath.size(); i++){
		loadSpritePlayerData(m_vecNormalSpriteFilePath[i], i);
	}
	for (unsigned int i = 0; i < m_mobSpriteFilePath.size(); i++){
		loadSpriteMonsterData(m_mobSpriteFilePath[i], i);
	}

	/*loadSpritePlayerData("./Data/Player_Sprite_Data.txt", SPR_PLAYER);
	loadSpritePlayerData("./Data/MapTile_Sprite_Data.txt", SPR_TILEMAP);
	loadSpritePlayerData("./Data/Effect1_Sprite_Data.txt", SPR_EFFECT);*/
	//loadSpriteMonsterData("./Data/Poring_Sprite_Data.txt", SPR_MOB_PORING);
	//loadSpriteMonsterData("./Data/Poring_Sprite_Data.txt", SPR_MOB_PORING_A);
	//loadSpriteMonsterData("./Data/Bapomat_Sprite_Data.txt", SPR_MOB_BAPOMAT);
	//int a = 0;
}

// 이제 모든 리소스는 여기서 관리하므로
// GameManager 이하 다른 곳에서의 SafeRelease는 삭제한다.
cResourceManager::~cResourceManager()
{
	// todo : destructor fix
	SafeRelease(m_Bitmap_Player);
	SafeRelease(m_Bitmap_TileMap);
	for (ID2D1Bitmap* x : m_Bitmap_MoB){
		if (x != nullptr){
			SafeRelease(x);
		}
	}
	//SafeRelease(m_Bitmap_Poring);
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
	for (ID2D1Bitmap* x : m_Bitmap_Item_Consume){
		if (x != nullptr){
			SafeRelease(x);
		}
	}
	for (ID2D1Bitmap* x : m_Bitmap_Effect){
		if (x != nullptr){
			SafeRelease(x);
		}
	}

	for (ID2D1Bitmap* x : m_Bitmap_MapObject){
		if (x != nullptr){
			SafeRelease(x);
		}
	}

	while (!m_vecFilepath.empty()){
		delete m_vecFilepath.back();
		m_vecFilepath.pop_back();
	}

	while (!m_mobSpriteFilePath.empty()){
		delete m_mobSpriteFilePath.back();
		m_mobSpriteFilePath.pop_back();
	}

	for (int i = 0; i < SPR_ID_MAX; i++){
		while (!m_vecSpriteInfo[i].empty()){
			delete m_vecSpriteInfo[i].back();
			m_vecSpriteInfo[i].pop_back();
		}
	}
}

void cResourceManager::loadFilePath(const char* szFileName){
	char szBuf[1024];

	FILE* fp;
	errno_t err;
	err = fopen_s(&fp, szFileName, "r");
	if (err != 0)
	{
		// error message
		wchar_t szDebug[128];
		wsprintf(szDebug, L"%s 파일 읽기 에러");
		MessageBox(NULL, szDebug, L"Error", MB_OK);
		return;
	}


	while (!feof(fp))
	{
		fgets(szBuf, 1024, fp);
		if (szBuf[0] == '#')
		{
			continue;
		}
		else if (szBuf[0] == 'a')
		{
			/*char fileName[1024];*/
			//ani.strFilaName = fileName;

			char* fileName = new char[1024];
			POINTFLOAT* size = new POINTFLOAT;
			
			/*char* x = new char[100];
			char* y = new char[100];*/
			float x;
			float y;

			int id;
			sscanf_s(szBuf, "%*s %d %f %f %s",
				&id, &x, &y, fileName, 1024);
			size->x = x;
			size->y = y;
			TCHAR* szName = new TCHAR[1024];
			USES_CONVERSION;
			_tcscpy(szName, A2T(fileName));
			
			m_vecFilepath.push_back(szName);
			m_vecImageSize.push_back(size);

			size = nullptr;
			szName = nullptr;
			fileName = nullptr;
			
			//m_vecAnimation.push_back(ani);
		}
	}
	fclose(fp);
}

void cResourceManager::loadMobSpritePath(const char* szFileName){
	char szBuf[1024];

	FILE* fp;
	errno_t err;
	err = fopen_s(&fp, szFileName, "r");
	if (err != 0)
	{
		// error message
		wchar_t szDebug[128];
		wsprintf(szDebug, L"%s 파일 읽기 에러");
		MessageBox(NULL, szDebug, L"Error", MB_OK);
		return;
	}


	while (!feof(fp))
	{
		fgets(szBuf, 1024, fp);
		if (szBuf[0] == '#')
		{
			continue;
		}
		else if (szBuf[0] == 'a')
		{
			/*char fileName[1024];*/
			//ani.strFilaName = fileName;

			char* fileName = new char[1024];

			/*char* x = new char[100];
			char* y = new char[100];*/
			/*float x;
			float y;*/

			int id;
			sscanf_s(szBuf, "%*s %d %s",
				&id, fileName, 1024);
			/*TCHAR* szName = new TCHAR[1024];
			USES_CONVERSION;
			_tcscpy(szName, A2T(fileName));*/

			m_mobSpriteFilePath.push_back(fileName);

			//szName = nullptr;
			fileName = nullptr;

			//m_vecAnimation.push_back(ani);
		}
	}
	fclose(fp);
}

void cResourceManager::loadNormalSpritePath(const char* szFileName){
	char szBuf[1024];

	FILE* fp;
	errno_t err;
	err = fopen_s(&fp, szFileName, "r");
	if (err != 0)
	{
		// error message
		wchar_t szDebug[128];
		wsprintf(szDebug, L"%s 파일 읽기 에러");
		MessageBox(NULL, szDebug, L"Error", MB_OK);
		return;
	}


	while (!feof(fp))
	{
		fgets(szBuf, 1024, fp);
		if (szBuf[0] == '#')
		{
			continue;
		}
		else if (szBuf[0] == 'a')
		{
			/*char fileName[1024];*/
			//ani.strFilaName = fileName;

			char* fileName = new char[1024];

			/*char* x = new char[100];
			char* y = new char[100];*/
		/*	float x;
			float y;*/

			int id;
			sscanf_s(szBuf, "%*s %d %s",
				&id, fileName, 1024);
			/*TCHAR* szName = new TCHAR[1024];
			USES_CONVERSION;
			_tcscpy(szName, A2T(fileName));*/

			m_vecNormalSpriteFilePath.push_back(fileName);

			//szName = nullptr;
			fileName = nullptr;

			//m_vecAnimation.push_back(ani);
		}
	}
	fclose(fp);
}



void cResourceManager::loadSpritePlayerData(const char* szFileName, int inid){
	char szBuf[1024];

	FILE* fp;
	errno_t err;
	err = fopen_s(&fp, szFileName, "r");
	if (err != 0)
	{
		// error message
		wchar_t szDebug[128];
		wsprintf(szDebug, L"%s 파일 읽기 에러");
		MessageBox(NULL, szDebug, L"Error", MB_OK);
		return;
	}


	while (!feof(fp))
	{
		fgets(szBuf, 1024, fp);
		if (szBuf[0] == '#')
		{
			continue;
		}
		else if (szBuf[0] == 'a')
		{			
			SpriteAnimationInfo* sprinfo = new SpriteAnimationInfo;

			DWORD id;
			DWORD direction;
			float _x;
			float _y;
			float _width;
			float _height;
			float _offsetX;
			float _offsetY;
			DWORD _maxFrame;			

			sscanf_s(szBuf, "%*s %d %d %f %f %f %f %f %f %d",
				&id, &direction, &_x, &_y, &_width, &_height, &_offsetX, &_offsetY, &_maxFrame);

			sprinfo->typ = id;
			sprinfo->direction = direction;
			sprinfo->x = _x;
			sprinfo->y = _y;
			sprinfo->width = _width;
			sprinfo->height = _height;
			sprinfo->offsetX = _offsetX;
			sprinfo->offsetY = _offsetY;
			sprinfo->maxFrame = _maxFrame;

			m_vecSpriteInfo[inid].push_back(sprinfo);

			sprinfo = nullptr;
		}
	}
	fclose(fp);
}

void cResourceManager::loadSpriteMonsterData(const char* szFileName, int inid){
	char szBuf[1024];

	FILE* fp;
	errno_t err;
	err = fopen_s(&fp, szFileName, "r");
	if (err != 0)
	{
		// error message
		wchar_t szDebug[128];
		wsprintf(szDebug, L"%s 파일 읽기 에러");
		MessageBox(NULL, szDebug, L"Error", MB_OK);
		return;
	}


	while (!feof(fp))
	{
		fgets(szBuf, 1024, fp);
		if (szBuf[0] == '#')
		{
			continue;
		}
		else if (szBuf[0] == 'a')
		{
			SpriteAnimationInfo* sprinfo = new SpriteAnimationInfo;

			DWORD id;
			DWORD direction;
			float _x;
			float _y;
			float _width;
			float _height;
			float _offsetX;
			float _offsetY;
			DWORD _maxFrame;

			sscanf_s(szBuf, "%*s %d %d %f %f %f %f %f %f %d",
				&id, &direction, &_x, &_y, &_width, &_height, &_offsetX, &_offsetY, &_maxFrame);

			sprinfo->typ = id;
			sprinfo->direction = direction;
			sprinfo->x = _x;
			sprinfo->y = _y;
			sprinfo->width = _width;
			sprinfo->height = _height;
			sprinfo->offsetX = _offsetX;
			sprinfo->offsetY = _offsetY;
			sprinfo->maxFrame = _maxFrame;

			m_vecMobSpriteInfo[inid].push_back(sprinfo);

			sprinfo = nullptr;
		}
	}
	fclose(fp);
}

SpriteAnimationInfo* cResourceManager::getPlayerSpriteInfo(int action, int direction){
	/// @todo 차후 수정 가능시 수정
	int index = 0;
	if (action == 0){
		index = 0;
	}
	else if (action == 1){
		index = 4;
	}
	else if (action == 2){
		index = 12;
	}
	else if (action == 3){
		index = 16;
	}
	else if (action == 4){
		index = 20;
	}
	else if (action == 5){
		index = 24;
	}
	else {
		return NULL;
	}

	for (unsigned int i = index; i < m_vecSpriteInfo[SPR_PLAYER].size(); i++){
		if (m_vecSpriteInfo[SPR_PLAYER][i]->typ == action &&
			m_vecSpriteInfo[SPR_PLAYER][i]->direction == direction){
			return m_vecSpriteInfo[SPR_PLAYER][i];
		}
	}
	return NULL;
}


SpriteAnimationInfo* cResourceManager::getMonsterSpriteInfo(int mobtype, int action, int direction){
	/// @todo 차후 수정 가능시 수정
	/// 차후 몹타입 추가
	

	int index = 0;
	if (action == 0){
		index = 0;
	}
	else if (action == 1){
		index = 2;
	}
	else if (action == 2){
		if (mobtype == 0 || mobtype == 1){
			index = 2;
		}
		else{
			index = 4;
		}
	}
	else if (action == 4){
		if (mobtype == 0 || mobtype == 1){
			index = 4;
		}
		else{
			index = 6;
		}		
	}
	else if (action == 5){
		if (mobtype == 0 || mobtype == 1){
			index = 6;
		}
		else{
			index = 8;
		}
	}	
	else {
		return NULL;
	}

	for (unsigned int i = index; i < m_vecMobSpriteInfo[mobtype].size(); i++){
		if (m_vecMobSpriteInfo[mobtype][i]->typ == action &&
			m_vecMobSpriteInfo[mobtype][i]->direction == direction){
			return m_vecMobSpriteInfo[mobtype][i];
		}
	}
	return NULL;
}

SpriteAnimationInfo* cResourceManager::getMapSpriteInfo(int tiletype, int type){
	int index = 0;
	if (tiletype == 0){
		index = 0;
	}
	else if (tiletype == 1){
		index = 2;
	}
	else {
		return NULL;
	}

	for (unsigned int i = index; i < m_vecSpriteInfo[SPR_TILEMAP].size(); i++){
		if (m_vecSpriteInfo[SPR_TILEMAP][i]->typ == tiletype &&
			m_vecSpriteInfo[SPR_TILEMAP][i]->direction == type){
			return m_vecSpriteInfo[SPR_TILEMAP][i];
		}
	}

	return NULL;
}

SpriteAnimationInfo* cResourceManager::getEffectSpriteInfo(int type){
	return m_vecSpriteInfo[SPR_EFFECT][type];
}

void cResourceManager::load(){
	HWND hWnd = ::cD2DRenderer::GetInstance().GetHwnd();
	m_Bitmap_MainBG = ::cD2DRenderer::GetInstance().CreateD2DBitmapFromFile(hWnd, m_vecFilepath[FILE_GAME_BG], NULL);
	
	m_MainBG_Size = { m_vecImageSize[FILE_GAME_BG]->x, m_vecImageSize[FILE_GAME_BG]->y };
	
	///sprites
	m_Bitmap_Player = ::cD2DRenderer::GetInstance().CreateD2DBitmapFromFile(hWnd, m_vecFilepath[FILE_GAME_PLAYER], NULL);		// 플레이어
	m_Bitmap_TileMap = ::cD2DRenderer::GetInstance().CreateD2DBitmapFromFile(hWnd, m_vecFilepath[FILE_GAME_TILEMAP], NULL);		// 타일맵
	m_Bitmap_MoB[MOB_ID_PORING] = ::cD2DRenderer::GetInstance().CreateD2DBitmapFromFile(hWnd, m_vecFilepath[FILE_GAME_MOB_PORING], NULL);		// 몬스터 포링 주소	
	m_Bitmap_MoB[MOB_ID_PORING_A] = ::cD2DRenderer::GetInstance().CreateD2DBitmapFromFile(hWnd, m_vecFilepath[FILE_GAME_MOB_PORING], NULL);
	m_Bitmap_MoB[MOB_ID_BAPOMAT] = ::cD2DRenderer::GetInstance().CreateD2DBitmapFromFile(hWnd, m_vecFilepath[FILE_GAME_MOB_BAPOMAT], NULL);
	///sprites

	m_Bitmap_UI[UIID::STATBAR] = ::cD2DRenderer::GetInstance().CreateD2DBitmapFromFile(hWnd, m_vecFilepath[FILE_UI_STAT_BAR], NULL);
	m_Bitmap_UI[UIID::BLUEBAR] = ::cD2DRenderer::GetInstance().CreateD2DBitmapFromFile(hWnd, m_vecFilepath[FILE_UI_BLUEBAR], NULL);
	m_Bitmap_UI[UIID::REDBAR] = ::cD2DRenderer::GetInstance().CreateD2DBitmapFromFile(hWnd, m_vecFilepath[FILE_UI_REDBAR], NULL);

	m_Bitmap_UI[UIID::MAP_L_BORDER] = ::cD2DRenderer::GetInstance().CreateD2DBitmapFromFile(hWnd, m_vecFilepath[FILE_UI_MAP_L_BORDER], NULL);
	m_Bitmap_UI[UIID::MAP_TAG] = ::cD2DRenderer::GetInstance().CreateD2DBitmapFromFile(hWnd, m_vecFilepath[FILE_UI_MAP_TAG], NULL);

	m_Bitmap_UI[UIID::UI_BELT] = ::cD2DRenderer::GetInstance().CreateD2DBitmapFromFile(hWnd, m_vecFilepath[FILE_UI_BELT], NULL);
	m_Bitmap_UI[UIID::UI_INVENTORY] = ::cD2DRenderer::GetInstance().CreateD2DBitmapFromFile(hWnd, m_vecFilepath[FILE_UI_INVENTORY], NULL);
	m_Bitmap_UI[UIID::UI_STAT] = ::cD2DRenderer::GetInstance().CreateD2DBitmapFromFile(hWnd, m_vecFilepath[FILE_UI_STAT], NULL);
	m_Bitmap_UI[UIID::UI_HUD_MENU] = ::cD2DRenderer::GetInstance().CreateD2DBitmapFromFile(hWnd, m_vecFilepath[FILE_UI_HUD_MENU], NULL);
	
	m_UI_SIZE[UIID::STATBAR] = { m_vecImageSize[FILE_UI_STAT_BAR]->x, m_vecImageSize[FILE_UI_STAT_BAR]->y };
	m_UI_SIZE[UIID::BLUEBAR] = { m_vecImageSize[FILE_UI_BLUEBAR]->x, m_vecImageSize[FILE_UI_BLUEBAR]->y };
	m_UI_SIZE[UIID::REDBAR] = { m_vecImageSize[FILE_UI_REDBAR]->x, m_vecImageSize[FILE_UI_REDBAR]->y };
	m_UI_SIZE[UIID::MAP_L_BORDER] = { m_vecImageSize[FILE_UI_MAP_L_BORDER]->x, m_vecImageSize[FILE_UI_MAP_L_BORDER]->y };
	m_UI_SIZE[UIID::MAP_TAG] = { m_vecImageSize[FILE_UI_MAP_TAG]->x, m_vecImageSize[FILE_UI_MAP_TAG]->y };
	m_UI_SIZE[UIID::UI_BELT] = { m_vecImageSize[FILE_UI_BELT]->x, m_vecImageSize[FILE_UI_BELT]->y };
	m_UI_SIZE[UIID::UI_INVENTORY] = { m_vecImageSize[FILE_UI_INVENTORY]->x, m_vecImageSize[FILE_UI_INVENTORY]->y };
	m_UI_SIZE[UIID::UI_STAT] = { m_vecImageSize[FILE_UI_STAT]->x, m_vecImageSize[FILE_UI_STAT]->y };
	m_UI_SIZE[UIID::UI_HUD_MENU] = { m_vecImageSize[FILE_UI_HUD_MENU]->x, m_vecImageSize[FILE_UI_HUD_MENU]->y };

	// Normal Menu
	m_Bitmap_UI[UIID::MN_NORMAL] = ::cD2DRenderer::GetInstance().CreateD2DBitmapFromFile(hWnd, m_vecFilepath[FILE_MN_NORMAL], NULL);
	m_UI_SIZE[UIID::MN_NORMAL] = { m_vecImageSize[FILE_MN_NORMAL]->x, m_vecImageSize[FILE_MN_NORMAL]->y };

	m_Bitmap_Button[BTN_RESUME] = ::cD2DRenderer::GetInstance().CreateD2DBitmapFromFile(hWnd, m_vecFilepath[FILE_BTN_RESUME], NULL);
	m_Bitmap_Button[BTN_SAVE] = ::cD2DRenderer::GetInstance().CreateD2DBitmapFromFile(hWnd, m_vecFilepath[FILE_BTN_SAVE], NULL);
	m_Bitmap_Button[BTN_LOAD2] = ::cD2DRenderer::GetInstance().CreateD2DBitmapFromFile(hWnd, m_vecFilepath[FILE_BTN_LOAD2], NULL);
	m_Bitmap_Button[BTN_RESTART] = ::cD2DRenderer::GetInstance().CreateD2DBitmapFromFile(hWnd, m_vecFilepath[FILE_BTN_RESTART], NULL);
	m_Bitmap_Button[BTN_MAINMENU] = ::cD2DRenderer::GetInstance().CreateD2DBitmapFromFile(hWnd, m_vecFilepath[FILE_BTN_MAINMENU], NULL);
	m_Bitmap_Button[BTN_EXITGAME] = ::cD2DRenderer::GetInstance().CreateD2DBitmapFromFile(hWnd, m_vecFilepath[FILE_BTN_EXITGAME], NULL);
	m_Bitmap_Button[BTN_REDARROW2] = ::cD2DRenderer::GetInstance().CreateD2DBitmapFromFile(hWnd, m_vecFilepath[FILE_BTN_REDARROW2], NULL);

	m_ButtonSize[BTN_RESUME] = { m_vecImageSize[FILE_BTN_RESUME]->x, m_vecImageSize[FILE_BTN_RESUME]->y };
	m_ButtonSize[BTN_SAVE] = { m_vecImageSize[FILE_BTN_SAVE]->x, m_vecImageSize[FILE_BTN_SAVE]->y };
	m_ButtonSize[BTN_LOAD2] = { m_vecImageSize[FILE_BTN_LOAD2]->x, m_vecImageSize[FILE_BTN_LOAD2]->y };
	m_ButtonSize[BTN_RESTART] = { m_vecImageSize[FILE_BTN_RESTART]->x, m_vecImageSize[FILE_BTN_RESTART]->y };
	m_ButtonSize[BTN_MAINMENU] = { m_vecImageSize[FILE_BTN_MAINMENU]->x, m_vecImageSize[FILE_BTN_MAINMENU]->y };
	m_ButtonSize[BTN_EXITGAME] = { m_vecImageSize[FILE_BTN_EXITGAME]->x, m_vecImageSize[FILE_BTN_EXITGAME]->y };
	m_ButtonSize[BTN_REDARROW2] = { m_vecImageSize[FILE_BTN_REDARROW2]->x, m_vecImageSize[FILE_BTN_REDARROW2]->y };

	// Gameover Menu
	m_Bitmap_UI[UIID::MN_GAMEOVER] = ::cD2DRenderer::GetInstance().CreateD2DBitmapFromFile(hWnd, m_vecFilepath[FILE_MN_GAMEOVER], NULL);
	m_UI_SIZE[UIID::MN_GAMEOVER] = { m_vecImageSize[FILE_MN_GAMEOVER]->x, m_vecImageSize[FILE_MN_GAMEOVER]->y };
	
	m_Bitmap_Button[BTN_LOADLAST] = ::cD2DRenderer::GetInstance().CreateD2DBitmapFromFile(hWnd, m_vecFilepath[FILE_BTN_LOADLAST], NULL);
	m_Bitmap_Button[BTN_VILLAGE] = ::cD2DRenderer::GetInstance().CreateD2DBitmapFromFile(hWnd, m_vecFilepath[FILE_BTN_VILLAGE], NULL);
	m_ButtonSize[BTN_LOADLAST] = { m_vecImageSize[FILE_BTN_LOADLAST]->x, m_vecImageSize[FILE_BTN_LOADLAST]->y };
	m_ButtonSize[BTN_VILLAGE] = { m_vecImageSize[FILE_BTN_VILLAGE]->x, m_vecImageSize[FILE_BTN_VILLAGE]->y };

	// Items
	m_Bitmap_Item_Consume[ITEM_POTION_HEALTH_SMALL] =
		::cD2DRenderer::GetInstance().CreateD2DBitmapFromFile
		(hWnd, m_vecFilepath[FILE_ITEM_POTION_HEALTH_SMALL], NULL);
	m_Bitmap_Item_Consume[ITEM_POTION_HEALTH_BIG] =
		::cD2DRenderer::GetInstance().CreateD2DBitmapFromFile
		(hWnd, m_vecFilepath[FILE_ITEM_POTION_HEALTH_BIG], NULL);
	m_Bitmap_Item_Consume[ITEM_POTION_HEALTH_1] =
		::cD2DRenderer::GetInstance().CreateD2DBitmapFromFile
		(hWnd, m_vecFilepath[FILE_ITEM_POTION_HEALTH_1], NULL);
	m_Bitmap_Item_Consume[ITEM_POTION_HEALTH_2] =
		::cD2DRenderer::GetInstance().CreateD2DBitmapFromFile
		(hWnd, m_vecFilepath[FILE_ITEM_POTION_HEALTH_2], NULL);
	m_Bitmap_Item_Consume[ITEM_POTION_HEALTH_3] =
		::cD2DRenderer::GetInstance().CreateD2DBitmapFromFile
		(hWnd, m_vecFilepath[FILE_ITEM_POTION_HEALTH_3], NULL);
	m_Bitmap_Item_Consume[ITEM_POTION_HEALTH_4] =
		::cD2DRenderer::GetInstance().CreateD2DBitmapFromFile
		(hWnd, m_vecFilepath[FILE_ITEM_POTION_HEALTH_4], NULL);
	m_Bitmap_Item_Consume[ITEM_POTION_MANA_SMALL] =
		::cD2DRenderer::GetInstance().CreateD2DBitmapFromFile
		(hWnd, m_vecFilepath[FILE_ITEM_POTION_MANA_SMALL], NULL);
	m_Bitmap_Item_Consume[ITEM_POTION_MANA_BIG] =
		::cD2DRenderer::GetInstance().CreateD2DBitmapFromFile
		(hWnd, m_vecFilepath[FILE_ITEM_POTION_MANA_BIG], NULL);
	m_Bitmap_Item_Consume[ITEM_POTION_MANA_1] =
		::cD2DRenderer::GetInstance().CreateD2DBitmapFromFile
		(hWnd, m_vecFilepath[FILE_ITEM_POTION_MANA_1], NULL);
	m_Bitmap_Item_Consume[ITEM_POTION_MANA_2] =
		::cD2DRenderer::GetInstance().CreateD2DBitmapFromFile
		(hWnd, m_vecFilepath[FILE_ITEM_POTION_MANA_2], NULL);
	m_Bitmap_Item_Consume[ITEM_POTION_MANA_3] =
		::cD2DRenderer::GetInstance().CreateD2DBitmapFromFile
		(hWnd, m_vecFilepath[FILE_ITEM_POTION_MANA_3], NULL);
	m_Bitmap_Item_Consume[ITEM_POTION_MANA_4] =
		::cD2DRenderer::GetInstance().CreateD2DBitmapFromFile
		(hWnd, m_vecFilepath[FILE_ITEM_POTION_MANA_4], NULL);

	for (int i = 0; i < ITEM_CONSUME_MAX; i++){
		m_Size_Item_Consume[i] = { 60.0f, 60.0f };
	}

	m_Bitmap_Effect[SKILL1] =
		::cD2DRenderer::GetInstance().CreateD2DBitmapFromFile
		(hWnd, m_vecFilepath[FILE_SKILL1], NULL);
	m_Size_Effect[SKILL1] = { m_vecImageSize[FILE_SKILL1]->x, m_vecImageSize[FILE_SKILL1]->y };

	m_Bitmap_Effect[SKILL2] = 
		::cD2DRenderer::GetInstance().CreateD2DBitmapFromFile
		(hWnd, m_vecFilepath[FILE_SKILL2], NULL);
	m_Size_Effect[SKILL2] = { m_vecImageSize[FILE_SKILL2]->x, m_vecImageSize[FILE_SKILL2]->y };
	
	m_Bitmap_Effect[HEALTHPOTION] = nullptr;
	m_Size_Effect[HEALTHPOTION] = { 0.0f, 0.0f };



	m_Bitmap_MapObject[MAP_ID_BUILDING] = ::cD2DRenderer::GetInstance().CreateD2DBitmapFromFile
		(hWnd, m_vecFilepath[FILE_MAP_ID_BUILDING], NULL);
	m_MapObject_Size[MAP_ID_BUILDING] = { m_vecImageSize[FILE_MAP_ID_BUILDING]->x, m_vecImageSize[FILE_MAP_ID_BUILDING]->y };
}

void cResourceManager::loadMainMenuResource(){
	HWND hWnd = ::cD2DRenderer::GetInstance().GetHwnd();
	m_Bitmap_MainBG = ::cD2DRenderer::GetInstance().CreateD2DBitmapFromFile(hWnd, m_vecFilepath[FILE_MAIN_MENU_BG], NULL);
	m_MainBG_Size = { m_vecImageSize[FILE_MAIN_MENU_BG]->x, m_vecImageSize[FILE_MAIN_MENU_BG]->y };
	
	m_Bitmap_Button[BTN_SPACETOPLAY] = ::cD2DRenderer::GetInstance().CreateD2DBitmapFromFile(hWnd, m_vecFilepath[FILE_BUTTON_SPACE_TO_PLAY], NULL);
	m_Bitmap_Button[BTN_NEWGAME] = ::cD2DRenderer::GetInstance().CreateD2DBitmapFromFile(hWnd, m_vecFilepath[FILE_BUTTON_NEWGAME], NULL);
	m_Bitmap_Button[BTN_LOAD] = ::cD2DRenderer::GetInstance().CreateD2DBitmapFromFile(hWnd, m_vecFilepath[FILE_BUTTON_LOAD], NULL);
	m_Bitmap_Button[BTN_CONFIG] = ::cD2DRenderer::GetInstance().CreateD2DBitmapFromFile(hWnd, m_vecFilepath[FILE_BUTTON_CONFIG], NULL);
	m_Bitmap_Button[BTN_REDARROW] = ::cD2DRenderer::GetInstance().CreateD2DBitmapFromFile(hWnd, m_vecFilepath[FILE_BUTTON_REDARROW], NULL);
	
	m_ButtonSize[BTN_SPACETOPLAY] = { m_vecImageSize[FILE_BUTTON_SPACE_TO_PLAY]->x, m_vecImageSize[FILE_BUTTON_SPACE_TO_PLAY]->y };
	m_ButtonSize[BTN_NEWGAME] = { m_vecImageSize[FILE_BUTTON_NEWGAME]->x, m_vecImageSize[FILE_BUTTON_NEWGAME]->y };
	m_ButtonSize[BTN_LOAD] = { m_vecImageSize[FILE_BUTTON_LOAD]->x, m_vecImageSize[FILE_BUTTON_LOAD]->y };
	m_ButtonSize[BTN_CONFIG] = { m_vecImageSize[FILE_BUTTON_CONFIG]->x, m_vecImageSize[FILE_BUTTON_CONFIG]->y };
	m_ButtonSize[BTN_REDARROW] = { m_vecImageSize[FILE_BUTTON_REDARROW]->x, m_vecImageSize[FILE_BUTTON_REDARROW]->y };

	// 차후 플레이어 이미지 및 스프라이트 좌표 정보도 이와 같이 관리
}

void cResourceManager::exitMainMenu(){
	SafeRelease(m_Bitmap_MainBG);
	for (int i = 0; i < BTN_MAIN_MAX; i++){
		SafeRelease(m_Bitmap_Button[i]);
	}
}

void cResourceManager::releaseGameResource(){
	SafeRelease(m_Bitmap_MainBG);
	SafeRelease(m_Bitmap_Player);
	SafeRelease(m_Bitmap_TileMap);
	for (ID2D1Bitmap* x : m_Bitmap_MoB){
		if (x != nullptr){
			SafeRelease(x);
		}
	}
	for (int i = BTN_GAME_START + 1; i < BTN_BUTTONTYPEMAX; i++){
		SafeRelease(m_Bitmap_Button[i]);
	}
	for (int i = 0; i < UI_ID_MAX; i++){
		SafeRelease(m_Bitmap_UI[i]);
	}
	for (ID2D1Bitmap* x : m_Bitmap_Item_Consume){
		if (x != nullptr){
			SafeRelease(x);
		}
	}
	for (ID2D1Bitmap* x : m_Bitmap_Effect){
		if (x != nullptr){
			SafeRelease(x);
		}
	}
}