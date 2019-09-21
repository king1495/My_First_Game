#include "stdafx.h"
#include "Bullet.h"


Bullet::Bullet()
	:isActive(false),
	hp(1), type(0), whos_bullet(0),
	fSpeed(0.f), fAngle(0.f), fRadius(0.f),
	FrameTime(0), FrameFreq(1)
{
}


Bullet::~Bullet()
{
}

HRESULT Bullet::Init()
{
	BULLET_NAME[0] = "eBullet";
	BULLET_NAME[1] = "Bullet1";
	BULLET_NAME[2] = "Bullet2";
	BULLET_NAME[3] = "Bullet3";

	img = _ImageManager->FindImage(BULLET_NAME[0]);

	CurrentFrame.frameX = 0;
	CurrentFrame.frameY = 0;
	CurrentFrame.frameMaxX = img->GetMaxFrameX();
	CurrentFrame.frameMaxY = img->GetMaxFrameY();

	return S_OK;
}

void Bullet::Release(void)
{
}

void Bullet::Update(void)
{
	if (!isActive) return;

	if (center.x + _Camera->x < -WinSizeX / 2.f ||
		center.y + _Camera->y < -WinSizeY / 2.f ||
		center.x + _Camera->x > 1.5f*WinSizeX ||
		center.y + _Camera->y > 1.5f*WinSizeY) {
		isActive = false;
		return;
	}

	center.x += sinf(fAngle) * fSpeed;
	center.y += -cosf(fAngle) * fSpeed;

	p2Render.x = center.x + _Camera->x;
	p2Render.y = center.y + _Camera->y;

	circle = MakeCircle(center.x + _Camera->x, center.y + _Camera->y, fRadius);

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

void Bullet::Render(void)
{
	if (!isActive) return;

	img->FrameRenderCenter(
		p2Render.x, p2Render.y,
		CurrentFrame.frameX, CurrentFrame.frameY,
		1.0f,
		false,
		RadianToDegree(fAngle));

	TCHAR status[256];
	if (_KeyCode->ToggleKeyDown(VK_TAB)) {
		_stprintf_s(status, L"x : %.2f, y : %.2f\nSpeed : %.2f\nAngle : %.2f", p2Render.x, p2Render.y, fSpeed, 180.f * fAngle / PI);
		_Device->RenderText(status, MakeRect(p2Render.x - img->GetFrameWidth() / 2.f, p2Render.y - img->GetFrameHeight() / 2.f, 200.f, -60.f));
		_RenderTarget->DrawEllipse(circle, _Device->pDefaultBrush);
	}
}

void Bullet::isFire(float _x, float _y, float _fRadius, float _fSpeed, float _fAngle, int _whos_bullet, int _istype)
{
	type = _istype;
	whos_bullet = _whos_bullet;
	img = _ImageManager->FindImage(BULLET_NAME[type]);

	FrameFreq = 2;

	center.x = _x;
	center.y = _y;

	p2Render.x = center.x + _Camera->x;
	p2Render.y = center.y + _Camera->y;

	fRadius = _fRadius;
	fSpeed = _fSpeed;
	fAngle = _fAngle;
	isActive = true;
	FrameTime = 0;
	CurrentFrame.frameX = 0;
	CurrentFrame.frameY = 0;
	CurrentFrame.frameMaxX = img->GetMaxFrameX();
	CurrentFrame.frameMaxY = img->GetMaxFrameY();

	circle = MakeCircle(center.x + _Camera->x, center.y + _Camera->y, fRadius);
}
