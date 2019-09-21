#include "stdafx.h"
#include "EnemyClass.h"

EnemyClass::EnemyClass()
	:fspeed(0.f), fradius(0.f), fangle(0.f),
	isActive(false), isType(isMinion),
	FrameTime(0), FrameFreq(2),
	alpha(1.f), Hp(1)
{
	ImageName[0] = "Minion";
	ImageName[1] = "Flier";
	ImageName[2] = "Boss";
}


EnemyClass::~EnemyClass()
{
}

HRESULT EnemyClass::Init(float _speed, float _radius)
{
	img = _ImageManager->FindImage(ImageName[isType]);

	if (isType == isBoss) Hp = 1000;

	width = img->GetFrameWidth();
	height = img->GetFrameHeight();

	fspeed = _speed;
	fradius = _radius;

	CurrentFrame.frameX = 0;
	CurrentFrame.frameY = 0;
	CurrentFrame.frameMaxX = img->GetMaxFrameX();
	CurrentFrame.frameMaxY = img->GetMaxFrameY();

	//	Render좌표 기준 스폰지점 만듬
	while (true) {
		switch (isType)
		{
		case isMinion: case isFlier:
			center.x = GetRandomFloat(-WinSizeX / 2.f, 1.5f*WinSizeX);
			center.y = GetRandomFloat(-WinSizeY / 2.f, 1.5f*WinSizeY);
			break;
		case isBoss:
			center.x = WinSizeX / 2.f;
			center.y = WinSizeY / 2.f;
			break;
		}
		if (!isPointInCircle(center.x, center.y, MakeCircle(Ppos.x, Ppos.y, 300.f)) || isType == isBoss) {
			break;
		}
	}

	p2Render.x = center.x + _Camera->x;
	p2Render.y = center.y + _Camera->y;

	circle = MakeCircle(center.x + _Camera->x, center.y + _Camera->y, fradius);

	isActive = true;

	return S_OK;
}

void EnemyClass::Release(void)
{
}

void EnemyClass::Update(void)
{
	if (!isActive)
	{
		alpha -= _Timer->GetElapsedTime() * 10;
		return;
	}
	else {
		alpha = 1.0f;
	}

	// 스탑이면 무브가 안걸려야되고
	if (!_DB->GetisStopOn()) {
		Move();
	}

	p2Render.x = center.x + _Camera->x;
	p2Render.y = center.y + _Camera->y;

	circle = MakeCircle(p2Render.x, p2Render.y, fradius);

	if (!_DB->GetisStopOn()) {
		Attack();
	}

	if (FrameTime % FrameFreq == 0) {
		CurrentFrame.frameX++;
		if (CurrentFrame.frameX >= CurrentFrame.frameMaxX) {
			CurrentFrame.frameX = 0;
			CurrentFrame.frameY++;
			if (CurrentFrame.frameY >= CurrentFrame.frameMaxY) {
				CurrentFrame.frameY = 0;
			}
		}
	}

	FrameTime++;
	if (FrameTime == UINT_MAX) FrameTime = 0;
}

void EnemyClass::Render(void)
{
	if (!isActive || alpha <= 0) return;

	if (isType == isBoss) {
		img->FrameRenderCenter(p2Render.x, p2Render.y, CurrentFrame.frameX, CurrentFrame.frameY, alpha, false, RadianToDegree(fangle), 4.f, 4.f);
		D2D_RECT_F HP_bar = MakeRect(WinSizeX / 2.f - 300.f, WinSizeY / 2.f - 210.f, 600.f*((float)Hp / 1000.f), 20.f);
		_Device->ChangeColor(RGB(0, 255, 0));
		_RenderTarget->FillRectangle(HP_bar, _Device->pDefaultBrush);
		_Device->ChangeColor(RGB(0, 0, 0));
		D2D_RECT_F HP_rect = MakeRect(WinSizeX / 2.f - 300.f, WinSizeY / 2.f - 210.f, 600.f, 20.f);
		_RenderTarget->DrawRectangle(HP_rect, _Device->pDefaultBrush);
	}
	else {
		if (p2Render.x < 0 - img->GetFrameWidth() ||
			p2Render.x > WinSizeX + img->GetFrameWidth() ||
			p2Render.y < 0 - img->GetFrameHeight() ||
			p2Render.y > WinSizeY + img->GetFrameHeight()
			) return;
		img->FrameRenderCenter(p2Render.x, p2Render.y, CurrentFrame.frameX, CurrentFrame.frameY, alpha, false, RadianToDegree(fangle));
	}

	TCHAR status[256];
	if (_KeyCode->ToggleKeyDown(VK_TAB)) {
		_stprintf_s(status, L"x : %.2f, y : %.2f\nAngle : %.2f\nHp : %d", center.x, center.y, 180.f * fangle / PI, Hp);
		_FontManager->TextRender(status, MakeRect(p2Render.x - width / 2.f, p2Render.y - height / 2.f, 200.f, -60.f));
		_RenderTarget->DrawEllipse(circle, _Device->pDefaultBrush);
	}
}