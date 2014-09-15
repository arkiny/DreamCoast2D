#include "stdafx.h"
#include "DreamCoastD2D.h"
#include "cGameApplication.h"
#include "cGameManager.h"

cGameApplication* app;

int APIENTRY _tWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	int       nCmdShow)
{

	app = new cGameApplication(new cGameManager);
	app->Init(hInstance, L"MyD2DGame", L"MyD2DClass", nCmdShow);
	app->Run();
	delete app;

	return 0;
}
