#include "stdafx.h"
#include "EndGameScene.h"


EndGameScene::EndGameScene()
{
}


EndGameScene::~EndGameScene()
{
}

HRESULT EndGameScene::Init(void)
{
	BT_RESTART = MakeRectCenter(WinSizeX / 2.f - 250.f, WinSizeY - 100.f, 200.f, 80.f);
	BT_EXIT = MakeRectCenter(WinSizeX / 2.f + 250.f, WinSizeY - 100.f, 200.f, 80.f);

	return S_OK;
}

void EndGameScene::Release(void)
{
}

void EndGameScene::Update(void)
{
	if (_KeyCode->isKeyDown(VK_LBUTTON)) {
		if (isPointInRect(AppMouse.x, AppMouse.y, BT_RESTART)) {
			_Scene->ChangeScene("CHARACTER_SELECT_SCENE");
		}
		if (isPointInRect(AppMouse.x, AppMouse.y, BT_EXIT)) {
			PostQuitMessage(0);
		}
	}
}

void EndGameScene::Render(void)
{
	_FontManager->TextRender(L"Game Clear!!", MakeRectCenter(WinSizeX / 2.f, WinSizeY / 2.f, 600.f, 50.f), "TITLE");

	_RenderTarget->DrawRectangle(BT_RESTART, _Device->pDefaultBrush);
	_FontManager->TextRender(L"\nRestart!", BT_RESTART, "CHARACTER_NAME");

	_RenderTarget->DrawRectangle(BT_EXIT, _Device->pDefaultBrush);
	_FontManager->TextRender(L"\nExit", BT_EXIT, "CHARACTER_NAME");
}
