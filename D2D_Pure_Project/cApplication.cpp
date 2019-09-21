#include "stdafx.h"
#include "cApplication.h"

App_Desc AppDesc;
D2D_POINT_2F AppMouse;
D2D_POINT_2F Ppos;

LRESULT cApplication::WndProc(HWND hWnd, UINT imsg, WPARAM wParam, LPARAM lParam)
{
	switch (imsg)
	{
	case WM_MOUSEMOVE:
		AppMouse.x = (float)GET_X_LPARAM(lParam);
		AppMouse.y = (float)GET_Y_LPARAM(lParam);
		break;

	case WM_ACTIVATE: // 엑티베이션 확인
		break;

	case WM_KEYDOWN:
		switch (wParam) {
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		}
		break;

	case WM_CLOSE: case WM_QUIT:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, imsg, wParam, lParam);
}

cApplication::cApplication()
{
	AppDesc = { nullptr, nullptr, 800, 600 };
}


cApplication::~cApplication()
{
	UnregisterClass(ApplicationName, AppDesc._hInstance);
}

HRESULT cApplication::CreateDevice(HINSTANCE hInstance, int nCmdShow)
{
	AppDesc._hInstance = hInstance;
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof WNDCLASSEX;

	wcex.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = ApplicationName;
	wcex.lpszClassName = ApplicationName;
	wcex.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);

	RegisterClassExW(&wcex);

	if (!_Device->CreateFactory()) return E_FAIL;

	//	DPI
	//	Dots per Inch
	//	1인치에 픽셀이 몇개 들어가는지 확인
	FLOAT dpiX, dpiY;
	_Factory->GetDesktopDpi(&dpiX, &dpiY);

	AppDesc._hWnd = CreateWindow(
		ApplicationName,
		ApplicationName,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		static_cast<UINT>(ceil(WinSizeX * dpiX / 96.f)), // 96개가 가장 일반적인? 적당한? DPI 클수록 그래픽카드가 좋아짐
		static_cast<UINT>(ceil(WinSizeY * dpiY / 96.f)),
		nullptr,
		nullptr,
		hInstance,
		this
	);

	if (!AppDesc._hWnd) return E_FAIL;
	if (!_Device->CreateDirect2dResources()) return E_FAIL;

	ShowWindow(AppDesc._hWnd, nCmdShow);
	UpdateWindow(AppDesc._hWnd);

	return S_OK;
}