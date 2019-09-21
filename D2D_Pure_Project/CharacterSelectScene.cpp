#include "stdafx.h"
#include "CharacterSelectScene.h"


CharacterSelectScene::CharacterSelectScene()
{
}


CharacterSelectScene::~CharacterSelectScene()
{
}

HRESULT CharacterSelectScene::Init(void)
{
	imScale = 3.f;

	ZeroMemory(isSelected, sizeof isSelected);

	pImages.push_back(_ImageManager->FindImage("Player1"));
	pImages.push_back(_ImageManager->FindImage("Player2"));
	pImages.push_back(_ImageManager->FindImage("Player3"));

	for (int i = 0; i < pImages.size(); ++i) {
		D2D_RECT_F temp = MakeRectCenter(200.f*i + 200.f, WinSizeY / 2.f - 100.f, 180.f, 300.f);
		rect_button.push_back(temp);
	}

	BT_OK = MakeRectCenter(WinSizeX / 2.f, WinSizeY - 100.f, 200.f, 80.f);

	CurrentFrame.frameMaxX = 4;
	CurrentFrame.frameMaxY = 1;
	CurrentFrame.frameX = 0;
	CurrentFrame.frameY = 0;

	return S_OK;
}

void CharacterSelectScene::Release(void)
{
	pImages.clear();
}

void CharacterSelectScene::Update(void)
{
	if (_KeyCode->isKeyDown(VK_LBUTTON)) {
		for (int i = 0; i < pImages.size(); ++i) {
			if (isPointInRect(AppMouse.x, AppMouse.y, BT_OK) && isSelected[i]) {
				_DB->SaveSelectCharacter(i);
				_Scene->ChangeScene("IN_GAME_SCENE");
			}

			if (isPointInRect(AppMouse.x, AppMouse.y, rect_button[i])) {
				isSelected[i] = true;
			}
			else {
				isSelected[i] = false;
			}
		}
	}

	FrameTime++;
	if (FrameTime % 3 == 0) {
		CurrentFrame = NextFrame(CurrentFrame);
	}
	if (FrameTime == UINT_MAX) FrameTime = 0;
}

void CharacterSelectScene::Render(void)
{
	float renderx;
	float rendery = WinSizeY / 2.f - 100.f;

	for (int i = 0; i < pImages.size(); ++i) {
		renderx = 200.f*i + 200.f;

		_RenderTarget->DrawRectangle(rect_button[i], _Device->pDefaultBrush);

		if (isSelected[i]) {
			pImages[i]->FrameRenderCenter(
				renderx,
				rendery,
				CurrentFrame.frameX,
				CurrentFrame.frameY,
				1.f,
				false, 0.f,
				4.f*imScale/3.f, 4.f*imScale / 3.f);
		}
		else {
			pImages[i]->FrameRenderCenter(
				renderx,
				rendery,
				0,
				0,
				1.f,
				false, 0.f,
				imScale, imScale);
		}

		switch (i) {
		case 0:
			// 글자를...쓰자....
			_FontManager->TextRender(L"마녀", MakeRectCenter(renderx, rect_button[i].bottom + 20.f, 180.f, 30.f), "CHARACTER_NAME");
			break;

		case 1:
			_FontManager->TextRender(L"초능력자", MakeRectCenter(renderx, rect_button[i].bottom + 20.f, 180.f, 30.f), "CHARACTER_NAME");
			break;

		case 2:
			_FontManager->TextRender(L"검사", MakeRectCenter(renderx, rect_button[i].bottom + 20.f, 180.f, 30.f), "CHARACTER_NAME");
			break;
		}
	}

	_RenderTarget->DrawRectangle(BT_OK, _Device->pDefaultBrush);
	_FontManager->TextRender(L"\nStart!", BT_OK, "CHARACTER_NAME");
}
