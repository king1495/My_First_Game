#include "stdafx.h"
#include "SlashBullet.h"


SlashBullet::SlashBullet()
{
}


SlashBullet::~SlashBullet()
{
}

HRESULT SlashBullet::Init(void)
{
	isType = Slash;
	return S_OK;
}

void SlashBullet::InitFire(void)
{
	StopFrame = 3;
	Hp = 10;
	scale = fRadius / 50.f;

	if (fRadius >= 100.f) StopFrame = 9;

	Hp *= scale;
}

void SlashBullet::AdditionalRender(void)
{
}

void SlashBullet::Fly(void)
{
	if (FrameTime >= StopFrame && isActive && fSpeed < 1.f) isActive = false;

	if (fRadius >= 75.f) {
		vector<BulletClass*> pBullets = _BulletManager->GetBullets();
		for (int j = 0; j < pBullets.size(); ++j) {
			if (!pBullets[j]->GetisActive()) continue;
			D2D1_ELLIPSE bCircle = pBullets[j]->GetCircle();

			if (pBullets[j]->GetWhos() == 1) {
				if (isCircleInCircle(bCircle, circle)) {
					pBullets[j]->SetisActive();
				}
			}
		}
	}



	if (fSpeed >= 1.f) {
		Velocity.x += Acceleration.x;
		Velocity.y += Acceleration.y;

		Position.x += Velocity.x;
		Position.y += Velocity.y;

		fSpeed = GetDistance(Velocity);
		fDirection = GetAngle(Velocity) + PI;
	}
}
