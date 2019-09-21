#include "stdafx.h"
#include "OrbitBullet.h"


OrbitBullet::OrbitBullet()
{
}


OrbitBullet::~OrbitBullet()
{
}

HRESULT OrbitBullet::Init(void)
{
	isType = Orbit;
	return S_OK;
}

void OrbitBullet::InitFire(void)
{
	Hp = _DB->GetAttack_Power();
	old_angle = NULL;
}

void OrbitBullet::Fly(void)
{
	if (old_angle == NULL) {
		old_angle = GetAngle(Ppos, Position) + PI / 2.f;
	}

	Position.x = Ppos.x + 120.f * sinf(old_angle);
	Position.y = Ppos.y - 120.f * cosf(old_angle);

	fSpeed = 0.f;
	fDirection = old_angle + PI / 2.f;

	old_angle += DegreeToRadian(3.f);
	if (FrameTime >= 600) isActive = false;
}

void OrbitBullet::SetBulletImage(void)
{
	switch (whos_bullet)
	{
	case 0:
		img = _ImageManager->FindImage("Bullet2");
		break;
	case 1:
		img = _ImageManager->FindImage("eBullet");
		break;
	}
}
