#pragma once
class DX2DApp
{
public:
	ID2D1Factory * pDirect2dFactory;
	ID2D1HwndRenderTarget* pRenderTarget;
	ID2D1SolidColorBrush* pDefaultBrush;

	IDWriteFactory* pWriteFactory;


public:
	DX2DApp();

	bool CreateFactory(void);
	bool CreateDirect2dResources(void);
	void Release(void);

	void BeginDraw(void);
	void EndDraw(void);
	void OnResize(UINT width, UINT height);

	//void RenderText(const wstring str, D2D1_RECT_F rc);
	//void RenderText(const wstring str, D2D1_RECT_F rc, ID2D1SolidColorBrush* brush, DWRITE_TEXT_ALIGNMENT align = DWRITE_TEXT_ALIGNMENT_JUSTIFIED);	//	구지 쓸필요 없어졌넹

	void ChangeColor(const COLORREF& color, float opacity = 1.0f);
	void ChangeColor(const D2D1_COLOR_F& color);

	HRESULT TransformGeometry(
		ID2D1Geometry *ipGeometryToTransform,
		ID2D1Geometry **oppTranformedGeometry,
		D2D1_MATRIX_3X2_F const & transform
	);

public:
	//	Design Pattern (static이라 아래처럼 사용할 수 있는거)
	static DX2DApp* GetInstance() {
		static DX2DApp Instance;
		return &Instance;
	}

};

#define _Device			DX2DApp::GetInstance()
#define _RenderTarget	DX2DApp::GetInstance()->pRenderTarget
#define _Factory		DX2DApp::GetInstance()->pDirect2dFactory