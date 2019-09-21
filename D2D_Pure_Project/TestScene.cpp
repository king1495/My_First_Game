#include "stdafx.h"
#include "TestScene.h"


TestScene::TestScene()
{
}


TestScene::~TestScene()
{
}

HRESULT TestScene::Init(void)
{
	img = new ImageModule;
	img->CreateImage("image/Lightning.png");

	x = WinSizeX / 2.f;
	y = WinSizeY / 2.f;
	scaleX = 1.f;
	scaleY = 1.f;
	rotation = 0.f;

	pBullet = new GuidedBullet;
	pBullet->isFire(0, 10.f, { x, y }, { 0.f, -1.f });

	return S_OK;
}

void TestScene::Release(void)
{
	img->Release();
	SafeDelete(img);

	pBullet->Release();
}

void TestScene::Update(void)
{
	if (_KeyCode->StayKeyDown('W')) y -= 5.f;
	if (_KeyCode->StayKeyDown('S')) y += 5.f;
	if (_KeyCode->StayKeyDown('A')) x -= 5.f;
	if (_KeyCode->StayKeyDown('D')) x += 5.f;
	//if (_KeyCode->StayKeyDown('Q')) rotation -= 0.1f;
	//if (_KeyCode->StayKeyDown('E')) rotation += 0.1f;
	if (_KeyCode->StayKeyDown(VK_UP)) scaleY += 0.1f;
	if (_KeyCode->StayKeyDown(VK_DOWN)) scaleY -= 0.1f;
	if (_KeyCode->StayKeyDown(VK_LEFT)) scaleX -= 0.1f;
	if (_KeyCode->StayKeyDown(VK_RIGHT)) scaleX += 0.1f;

	rect = MakeRectCenter(x, y, scaleX * img->GetWidth(), scaleY * img->GetHeight());

	rotation = GetAngle(x, y, AppMouse.x, AppMouse.y) + PI / 2.f;
	rotation = RadianToDegree(rotation);

	pBullet->Update();
}

void TestScene::Render(void)
{
	TCHAR status[256];
	pBullet->Render();

	D2D1_ELLIPSE circle = pBullet->GetCircle();
	float dirc = GetAngle(AppMouse.x, AppMouse.y, circle.point.x, circle.point.y) + PI / 2.f;
	_stprintf_s(status, L"Direction : %.2f", dirc * 180.f / PI);
	_RenderTarget->DrawLine(circle.point, { AppMouse.x, AppMouse.y }, _Device->pDefaultBrush);
	_FontManager->TextRender(status, MakeRect(AppMouse.x, AppMouse.y, 200.f, -20.f));

	img->FrameRenderCenter(x, y, 0, 0, 1.f, false, rotation, scaleX, scaleY);
	_RenderTarget->DrawRectangle(rect, _Device->pDefaultBrush);

	_stprintf_s(status, L"x : %.2f, y : %.2f\nscaleX : %.2f, scaleY : %.2f\nRotation : %.2f", x, y, scaleX, scaleY, -rotation);
	_FontManager->TextRender(status, MakeRect(x - scaleX * img->GetWidth() / 2.f, y - scaleY * img->GetHeight() / 2.f, 200.f, -60.f));
	//_Device->RenderText(status, MakeRect(x, y, 200.f, -60.f));
}
