#include "stdafx.h"
#include "BulletClass.h"


BulletClass::BulletClass()
	:whos_bullet(0), Hp(1),
	isActive(false), isReverse(false),
	FrameTime(0), FrameFreq(2),
	Position(D2D_POINT_2F()),
	Velocity(D2D_POINT_2F()),
	Acceleration(D2D_POINT_2F()),
	fSpeed(0.f), fDirection(0.f), fRadius(0.f),
	alpha(1.f), scale(1.f),
	isType(Normal)

{
	CurrentFrame.frameX = 0;
	CurrentFrame.frameY = 0;
	CurrentFrame.frameMaxX = 1;
	CurrentFrame.frameMaxY = 1;
}


BulletClass::~BulletClass()
{
}

HRESULT BulletClass::Init(void)
{
	return S_OK;
}

void BulletClass::Release(void)
{
}

void BulletClass::Update(void)
{
	if (Hp <= 0) {
		if (_DB->GetisReflectOn() && whos_bullet == 1) {
			Reflect();
			Hp = 1;
		}
		else {
			isActive = false;
		}
	}

	if (!isActive) return;

	BoundCondition();

	Fly();

	p2Render.x = Position.x + _Camera->x;
	p2Render.y = Position.y + _Camera->y;

	circle = MakeCircle(p2Render.x, p2Render.y, fRadius);

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

void BulletClass::Render(void)
{
	if (!isActive) return;
	if (p2Render.x < 0 - img->GetFrameWidth() ||
		p2Render.x > WinSizeX + img->GetFrameWidth() ||
		p2Render.y < 0 - img->GetFrameHeight() ||
		p2Render.y > WinSizeY + img->GetFrameHeight()
		) return;

	AdditionalRender();

	img->FrameRenderCenter(
		p2Render.x, p2Render.y,
		CurrentFrame.frameX, CurrentFrame.frameY,
		alpha,
		isReverse,
		RadianToDegree(fDirection),
		scale,
		scale);

	if (_KeyCode->ToggleKeyDown(VK_TAB)) {
		TCHAR status[256];
		_stprintf_s(status, L"x : %.2f, y : %.2f\nSpeed : %.2f\nDirection : %.2f", Position.x, Position.y, fSpeed, 180.f * fDirection / PI);
		_FontManager->TextRender(status, MakeRect(p2Render.x - img->GetFrameWidth() / 2.f, p2Render.y - img->GetFrameHeight() / 2.f, 200.f, -60.f));
		_RenderTarget->DrawEllipse(circle, _Device->pDefaultBrush);
	}
}

HRESULT BulletClass::isFire(int _whos_bullet, float _fRadius, D2D_POINT_2F _pos, D2D_POINT_2F _vel, D2D_POINT_2F _acc)
{
	whos_bullet = _whos_bullet;

	SetBulletImage();

	CurrentFrame.frameX = 0;
	CurrentFrame.frameY = 0;
	CurrentFrame.frameMaxX = img->GetMaxFrameX();
	CurrentFrame.frameMaxY = img->GetMaxFrameY();


	Position = _pos;
	Velocity = _vel;
	Acceleration = _acc;

	fRadius = _fRadius;
	fSpeed = GetDistance(Velocity);
	fDirection = GetAngle(Velocity) + PI / 2.f;
	isActive = true;
	FrameTime = 0;
	FrameFreq = 2;
	scale = 1.f;
	alpha = 1.f;

	InitFire();

	circle = MakeCircle(Position.x + _Camera->x, Position.y + _Camera->y, fRadius);

	p2Render.x = Position.x + _Camera->x;
	p2Render.y = Position.y + _Camera->y;

	return S_OK;
}

void BulletClass::BoundCondition(void)
{
	/*if (Position.x + _Camera->x < -WinSizeX / 2.f ||
		Position.y + _Camera->y < -WinSizeY / 2.f ||
		Position.x + _Camera->x > 1.5f*WinSizeX ||
		Position.y + _Camera->y > 1.5f*WinSizeY) {
		isActive = false;
		return;
	}*/

	if (Position.x < -WinSizeX / 2.f ||
		Position.y < -WinSizeY / 2.f ||
		Position.x >  1.5f*WinSizeX ||
		Position.y >  1.5f*WinSizeY) {
		isActive = false;
		return;
	}
}

void BulletClass::SetBulletImage(void)
{
	string BulletList[] = {
		"Bullet1" ,
		"Bullet2" ,
		"Bullet3"
	};

	switch (whos_bullet)
	{
	case 0:
		img = _ImageManager->FindImage(BulletList[_DB->LoadSelectCharacter()]);
		break;
	case 1:
		img = _ImageManager->FindImage("eBullet");
		break;
	}
}

void BulletClass::Fly(void)
{
	if (_DB->GetisStopOn() && whos_bullet == 1) return;
	if (_DB->GetisDelayOn()) {
		if (FrameTime % 6 != 0) return;
	}

	Velocity.x += Acceleration.x;
	Velocity.y += Acceleration.y;

	Position.x += Velocity.x;
	Position.y += Velocity.y;

	fSpeed = GetDistance(Velocity);
	fDirection = GetAngle(Velocity) - PI / 2.f;
}

void BulletClass::Reflect(void)
{
	if (whos_bullet == 0) return;

	whos_bullet = 0;

	int num = 0;
	float fDist = FloatMax();
	float fAngle = 0.f;
	vector<EnemyClass*> vEnemys = _EnemyManager->GetEnemys();

	for (int i = 0; i < vEnemys.size(); ++i) {
		if (!vEnemys[i]->GetisActive()) continue;
		D2D_POINT_2F ePos = vEnemys[i]->GetCircle().point;
		float temp = GetDistance(p2Render, ePos);
		if (temp < fDist) {
			fDist = temp;
			num = i;
			fAngle = GetAngle(p2Render, ePos) + PI / 2.f;
		}
	}

	Velocity.x = 10.f * sinf(fAngle);
	Velocity.y = -10.f * cosf(fAngle);
}