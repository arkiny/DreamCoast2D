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

class cD2DRenderer
{
private:

	ID2D1Factory*				m_ipD2DFactory;
	ID2D1HwndRenderTarget*		m_ipRT;

	IWICImagingFactory*			m_ipWICFactory;
	IWICFormatConverter*		m_ipConvertedSrcBmp;

	ID2D1SolidColorBrush* m_pBlackBrush;
	ID2D1SolidColorBrush* m_pGreenBrush;
	ID2D1SolidColorBrush* m_pRedBrush;

	IDWriteFactory* m_pDWriteFactory;
	IDWriteTextFormat* m_pTextFormat;

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

	ID2D1SolidColorBrush* GetBrush()
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

	IDWriteTextFormat* GetTextFormat()
	{
		return m_pTextFormat;
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
