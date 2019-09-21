#include "stdafx.h"
#include "DX2DApp.h"


DX2DApp::DX2DApp()
	: pWriteFactory(nullptr),
	pDefaultBrush(nullptr),
	pRenderTarget(nullptr),
	pDirect2dFactory(nullptr)
{

}

bool DX2DApp::CreateFactory(void)
{
	//	FAILED = HRESULT
	//	bool 보다 정확히 에러 내용을 보여줌
	//	성공하면 S_OK, 실패하면 기타기타에러에러 등등
	if (FAILED(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pDirect2dFactory)))
	{
		return false;
	}

	return true;
}

bool DX2DApp::CreateDirect2dResources(void)
{
	RECT rc = { 0,0,(LONG)WinSizeX, (LONG)WinSizeY };

	D2D1_SIZE_U size = D2D1::SizeU(
		rc.right - rc.left,
		rc.bottom - rc.top
	);

	UINT CenterX = (GetSystemMetrics(SM_CXSCREEN) - (UINT)WinSizeX) / 2;
	UINT CenterY = (GetSystemMetrics(SM_CYSCREEN) - (UINT)WinSizeY) / 2;

	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, false);
	MoveWindow(AppDesc._hWnd,
		CenterX, CenterY,
		rc.right - rc.left,
		rc.bottom - rc.top, true);

	if (FAILED(pDirect2dFactory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(AppDesc._hWnd, size),
		&pRenderTarget))) return false;

	if (FAILED(pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &pDefaultBrush))) return false;

	if (FAILED(DWriteCreateFactory(
		DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(pWriteFactory),
		reinterpret_cast<IUnknown**>(&pWriteFactory))))return false;

	return true;
}


void DX2DApp::OnResize(UINT width, UINT height)
{
	pRenderTarget->Resize(D2D1::SizeU(width, height));
}

void DX2DApp::Release(void)
{
	SafeRelease(pWriteFactory);

	SafeRelease(pDefaultBrush);
	SafeRelease(pRenderTarget);
	SafeRelease(pDirect2dFactory);
}

void DX2DApp::BeginDraw(void)
{
	if (pRenderTarget) {
		pRenderTarget->BeginDraw();
		pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
		pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));
		//pRenderTarget->Clear(D2D1::ColorF(0x99ccff));
	}
}

void DX2DApp::EndDraw(void)
{
	if (pRenderTarget) pRenderTarget->EndDraw();
}


//void DX2DApp::RenderText(const wstring str, D2D1_RECT_F rc)
//{
//	pRenderTarget->DrawTextW(str.c_str(), str.size(),
//		pDefaultTextFormat, rc, pDefaultBrush);
//}
//
//void DX2DApp::RenderText(const wstring str, D2D1_RECT_F rc, ID2D1SolidColorBrush* brush, DWRITE_TEXT_ALIGNMENT align)
//{
//	pDefaultTextFormat->SetTextAlignment(align);
//	pRenderTarget->DrawTextW(str.c_str(), str.size(),
//		pDefaultTextFormat, rc, brush);
//	pDefaultTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_JUSTIFIED);
//}

void DX2DApp::ChangeColor(const COLORREF & color, float opacity)
{
	UINT col = (((BYTE)GetBValue(color)) |
		(((WORD)(BYTE)GetGValue(color)) << 8) |
		(((DWORD)(BYTE)GetRValue(color)) << 16));

	pDefaultBrush->SetColor(ColorF(col, opacity));
}

void DX2DApp::ChangeColor(const D2D1_COLOR_F & color)
{
	pDefaultBrush->SetColor(color);
}

HRESULT DX2DApp::TransformGeometry(ID2D1Geometry * ipGeometryToTransform, ID2D1Geometry ** oppTranformedGeometry, D2D1_MATRIX_3X2_F const & transform)
{
	HRESULT hr;
	ID2D1Factory *pFactory = NULL;
	ipGeometryToTransform->GetFactory(&pFactory);

	ID2D1TransformedGeometry *pTransformedGeometry = NULL;
	hr = pFactory->CreateTransformedGeometry(
		ipGeometryToTransform,
		transform,
		&pTransformedGeometry
	);
	// See Q&A Explanation from user treckle to understand why I should release the pFactory here 
	pFactory->Release();

	*oppTranformedGeometry = pTransformedGeometry;
	(*oppTranformedGeometry)->AddRef();
	pTransformedGeometry->Release();

	return hr;
}
