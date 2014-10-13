#include "stdafx.h"
#include "cD2DRenderer.h"

template<> cD2DRenderer* Singleton<cD2DRenderer>::_instance = 0;

cD2DRenderer::cD2DRenderer()
{

	m_ipD2DFactory = nullptr;
	m_ipRT = nullptr;
	m_ipWICFactory = nullptr;
	m_ipConvertedSrcBmp = nullptr;
}


cD2DRenderer::~cD2DRenderer()
{

	SafeRelease(m_ipWICFactory);
	SafeRelease(m_ipRT);
	SafeRelease(m_ipD2DFactory);

	SafeRelease(m_pBlackBrush);
	SafeRelease(m_pRedBrush);
	SafeRelease(m_pGreenBrush);
	SafeRelease(m_pWhiteBrush);

	SafeRelease(m_pDWriteFactory);
	SafeRelease(m_pTextFormat);

}

void cD2DRenderer::InitializeD2D(void)
{

	HRESULT hr = E_FAIL;

	//-----------------------------------------------------------------------
	//	D2D Factory �� �����Ѵ�.
	//-----------------------------------------------------------------------
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED,
		&m_ipD2DFactory);
	assert(hr == S_OK);

	// Create a DirectWrite factory.
	hr = DWriteCreateFactory(
		DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(IDWriteFactory),
		reinterpret_cast<IUnknown**>(&m_pDWriteFactory)
		);
	assert(hr == S_OK);


	m_pDWriteFactory->CreateTextFormat(
		L"Gabriola",                // Font family name.
		NULL,                       // Font collection (NULL sets it to use the system font collection).
		DWRITE_FONT_WEIGHT_REGULAR,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		20.0f,
		L"en-us",
		&m_pTextFormat
		);

	if (SUCCEEDED(hr))
	{
		hr = m_pTextFormat->SetTextAlignment(::DWRITE_TEXT_ALIGNMENT_CENTER);
	}

	if (SUCCEEDED(hr))
	{
		hr = m_pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT::DWRITE_PARAGRAPH_ALIGNMENT_FAR);
	}


	m_pDWriteFactory->CreateTextFormat(
		L"Gabriola",                // Font family name.
		NULL,                       // Font collection (NULL sets it to use the system font collection).
		DWRITE_FONT_WEIGHT_REGULAR,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		20.0f,
		L"en-us",
		&m_pTextFormat2
		);

	if (SUCCEEDED(hr))
	{
		hr = m_pTextFormat2->SetTextAlignment(::DWRITE_TEXT_ALIGNMENT::DWRITE_TEXT_ALIGNMENT_LEADING);
	}

	if (SUCCEEDED(hr))
	{
		hr = m_pTextFormat2->SetParagraphAlignment(::DWRITE_PARAGRAPH_ALIGNMENT::DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
	}
	if (SUCCEEDED(hr))
	{
		// �����̽� �޼ҵ带 ���������� ������, ���� ù������ ���̽����� ��Ƽ� �׷�����
		hr = m_pTextFormat2->SetLineSpacing(DWRITE_LINE_SPACING_METHOD::DWRITE_LINE_SPACING_METHOD_UNIFORM, 20.0f, 1.4f);
	}

	CoInitialize(0);

	//-----------------------------------------------------------------------
	//	Windows Imaging Component Factory �� �����Ѵ�.
	//-----------------------------------------------------------------------
	hr = ::CoCreateInstance(CLSID_WICImagingFactory,
		NULL, CLSCTX_INPROC_SERVER,
		IID_PPV_ARGS(&m_ipWICFactory));
	assert(hr == S_OK);

}

void cD2DRenderer::InitializeRT(HWND hWnd)
{

	assert(m_ipRT == nullptr);
	assert(hWnd != 0);

	HRESULT hr = E_FAIL;
	RECT rc;
	::GetClientRect(hWnd, &rc);


	D2D1_RENDER_TARGET_PROPERTIES dxRTProperties = ::D2D1::RenderTargetProperties();
	m_dxSize = ::D2D1::SizeU(rc.right - rc.left,
		rc.bottom - rc.top);

	/*m_dxSize = ::D2D1::SizeU(800,
		600);*/

	//::D2D1_PRESENT_OPTIONS_IMMEDIATELY�� ���� ��������ȭ�� �����ִ�.
	// �⺻�ɼ��� ��������ȭ...
	// ���ϴ� �������� �����Ϸ���, â�� ���� �����ؾ��ϳ�?
	hr = m_ipD2DFactory->CreateHwndRenderTarget(dxRTProperties,
		::D2D1::HwndRenderTargetProperties(hWnd, m_dxSize),
		&m_ipRT);
	assert(hr == S_OK);

	// Brush
	hr = m_ipRT->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::Black),
		&m_pBlackBrush
		);

	assert(hr == S_OK);

	hr = m_ipRT->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::GreenYellow),
		&m_pGreenBrush
		);

	assert(hr == S_OK);

	hr = m_ipRT->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::DarkRed),
		&m_pRedBrush
		);
	assert(hr == S_OK);

	hr = m_ipRT->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::White),
		&m_pWhiteBrush
		);
	assert(hr == S_OK);

	//default
	hr = m_ipRT->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::White),
		&m_pBrush
		);
	assert(hr == S_OK);
	
}

void cD2DRenderer::ChangeBrush(D2D1::ColorF in){
	HRESULT hr = m_ipRT->CreateSolidColorBrush(
		D2D1::ColorF(in),
		&m_pBrush
		);
	assert(hr == S_OK);
}

ID2D1Bitmap* cD2DRenderer::CreateD2DBitmapFromFile(
	HWND hWnd, TCHAR* pImageFullPath, int option){
	assert(pImageFullPath != nullptr);
	assert(m_ipWICFactory != nullptr);
	assert(m_ipRT != nullptr);
	HRESULT hr = E_FAIL;

	// ���ڴ� ����
	IWICBitmapDecoder* ipDecoderPtr = nullptr;
	hr = m_ipWICFactory->CreateDecoderFromFilename(pImageFullPath, nullptr,
		GENERIC_READ,
		WICDecodeMetadataCacheOnDemand,
		&ipDecoderPtr);
	assert(hr == S_OK);

	// 1������ �̾ƿ���
	IWICBitmapFrameDecode* ipFramePtr = nullptr;
	hr = ipDecoderPtr->GetFrame(0, &ipFramePtr);
	assert(hr == S_OK);

	//--------------------------------------------------------------
	// Frame�� option�� ���� �����ų� ������. ���⼭ �ٲ� ���������� ����������
	// ���� ���μ����� �ּ�ȭ �Ҽ� �ִ�.
	//--------------------------------------------------------------
	//flip rotator�� �޾Ƽ�
	IWICBitmapFlipRotator *pIFlipRotator = NULL;
	hr = m_ipWICFactory->CreateBitmapFlipRotator(&pIFlipRotator);
	assert(hr == S_OK);

	// ���ҽ��� ����ֽ��ϴ�.
	hr = pIFlipRotator->Initialize(
		ipFramePtr,					    // Bitmap source to flip.
		(WICBitmapTransformOptions)option);						// Flip the pixels along the 
	//  vertical y-axis.
	assert(hr == S_OK);

	//----------------------------------------------------------------
	//	�������� ������� �ؼ� ���� �����͸� �����.
	//----------------------------------------------------------------
	SafeRelease(m_ipConvertedSrcBmp);
	hr = m_ipWICFactory->CreateFormatConverter(&m_ipConvertedSrcBmp);
	assert(hr == S_OK);

	hr = m_ipConvertedSrcBmp->Initialize(pIFlipRotator,
		GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone,
		nullptr,
		0.0f,
		WICBitmapPaletteTypeCustom);
	assert(hr == S_OK);

	//----------------------------------------------------------------
	//	����Ʈ�� �����͸� ������� �ؼ� ���� ��Ʈ���� �����.
	//----------------------------------------------------------------
	ID2D1Bitmap* ipD2DBitmap = nullptr;

	hr = m_ipRT->CreateBitmapFromWicBitmap(m_ipConvertedSrcBmp,
		nullptr,
		&ipD2DBitmap);
	assert(hr == S_OK);

	
	SafeRelease(ipDecoderPtr);
	SafeRelease(ipFramePtr);
	SafeRelease(pIFlipRotator);

	return ipD2DBitmap;
}

void cD2DRenderer::BeginRender(HWND hWnd)
{
	m_hWnd = hWnd;
	hdc = BeginPaint(hWnd, &ps);
}

void cD2DRenderer::Setup(HWND hWnd)
{
	m_hWnd = hWnd;
	if (m_ipRT == nullptr)
	{
		InitializeRT(hWnd);

		return;

	}
}

void cD2DRenderer::EndRender()
{

	EndPaint(m_hWnd, &ps);

}