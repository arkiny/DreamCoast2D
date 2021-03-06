#pragma once
#include <vector>
#include <d2d1.h>
#include <d2d1helper.h>
#include <wincodec.h>
#include <cassert>
#include <CommDlg.h>

#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

//	최대 로드할 수 있는 이미지 갯수.
#define _MAX_IMAGE_COUNT_ 1024

#include <dwrite.h>
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")
#pragma comment(lib,"Windowscodecs.lib")


#include "Singleton.h"

class cD2DRenderer : public Singleton<cD2DRenderer>
{
private:

	ID2D1Factory*				m_ipD2DFactory;
	ID2D1HwndRenderTarget*		m_ipRT;

	IWICImagingFactory*			m_ipWICFactory;
	IWICFormatConverter*		m_ipConvertedSrcBmp;

	ID2D1SolidColorBrush* m_pBlackBrush;
	ID2D1SolidColorBrush* m_pGreenBrush;
	ID2D1SolidColorBrush* m_pRedBrush;
	ID2D1SolidColorBrush* m_pWhiteBrush;
	ID2D1SolidColorBrush* m_pForestGreenBrush;
	ID2D1SolidColorBrush* m_pGreyBrush;

	IDWriteFactory* m_pDWriteFactory;
	IDWriteTextFormat* m_pTextFormat;
	IDWriteTextFormat* m_pTextFormat2;
	IDWriteTextFormat* m_pTextFormatDmg;
	IDWriteTextFormat* m_pTextFormatChat;

	D2D1_SIZE_U m_dxSize;
	
	HDC hdc;
	PAINTSTRUCT ps;
	HWND m_hWnd;

public:
	cD2DRenderer();
	~cD2DRenderer();
	void InitializeD2D(void);
	void Setup(HWND hWnd);
	void InitializeRT(HWND hWnd);
	ID2D1Bitmap* CreateD2DBitmapFromFile(HWND hWnd, TCHAR* pImageFullPath, int option);
	void BeginRender(HWND hWnd);
	void EndRender();

	ID2D1HwndRenderTarget* GetRenderTarget(){
		return  m_ipRT;
	}

	HWND GetHwnd(){ return m_hWnd; }
	D2D1_SIZE_U GetRenderTargetSize(){
		return m_dxSize;
	}

	ID2D1SolidColorBrush* GetBlackBrush()
	{
		return m_pBlackBrush;
	}

	ID2D1SolidColorBrush* GetGreenBrush()
	{
		return m_pGreenBrush;
	}

	ID2D1SolidColorBrush* GetRedBrush(){
		return m_pRedBrush;
	}

	ID2D1SolidColorBrush* GetWhiteBrush(){
		return m_pWhiteBrush;
	}

	ID2D1SolidColorBrush* GetForestGreenBrush(){
		return m_pForestGreenBrush;
	}

	ID2D1SolidColorBrush* GetGrayBrush(){
		return m_pGreyBrush;
	}
	
	IDWriteTextFormat* GetTextFormat()
	{
		return m_pTextFormat;
	}

	IDWriteTextFormat* GetTextFormat2()
	{
		return m_pTextFormat2;
	}

	IDWriteTextFormat* GetTextFormatChat()
	{
		return m_pTextFormatChat;
	}	

	IDWriteTextFormat* GetTextFormatDmg()
	{
		return m_pTextFormatDmg;
	}
};

template <typename T>
inline void SafeRelease(T *&p)
{
	if (NULL != p)
	{
		p->Release();
		p = NULL;
	}
}
