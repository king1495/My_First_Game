
#include "stdafx.h"
#include "MainEntryClass.h"

MainEntryClass MainClass;

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	if (FAILED(MainClass.CreateDevice(hInstance, nCmdShow))) return FALSE;
	if (FAILED(MainClass.Init())) return FALSE;

	srand((UINT)time(nullptr));

	MSG msg;

	while (true) {
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT) break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			_Timer->UpdateTime(60);	//	FPS : 60.f 기준
			MainClass.Update();

			_Device->BeginDraw();
			MainClass.Render();
			_Timer->RenderTime();
			_Device->EndDraw();
		}
	}

	return (int)msg.wParam;
}