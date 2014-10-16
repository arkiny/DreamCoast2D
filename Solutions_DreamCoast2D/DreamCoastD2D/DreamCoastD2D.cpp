#include "stdafx.h"
#include "DreamCoastD2D.h"
#include "cGameApplication.h"
#include "cGameManager.h"


#include <xaudio2.h>



cGameApplication* app;

int APIENTRY _tWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	int       nCmdShow)
{
#ifdef _DEBUG
	int flag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
	flag |= _CRTDBG_LEAK_CHECK_DF; // Turn on leak-checking bit
	_CrtSetDbgFlag(flag);
	_CrtSetBreakAlloc(728300); // Comment or un-comment on need basis
#endif
	
	app = new cGameApplication(new cGameManager);
	app->Init(hInstance, L"DreamCoast2D", L"DreamCoast2DClass", nCmdShow);
	app->Run();
	delete app;

	return 0;
}
