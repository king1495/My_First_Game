#include "stdafx.h"
#include "FocusBullet.h"


FocusBullet::FocusBullet()
{
}


FocusBullet::~FocusBullet()
{
}

HRESULT FocusBullet::Init(void)
{
	isType = Focus;

	return S_OK;
}

void FocusBullet::Fly(void)
{
	if (FrameTime > 180) {

		//	거리 = 시간*속력
		float fAngle = GetAngle(p2Render.x, p2Render.y, AppMouse.x, AppMouse.y) + PI / 2.f;

		Velocity.x += fSpeed * sinf(fAngle);
		Velocity.y += -fSpeed * cosf(fAngle);
	}

	Position.x += Velocity.x;
	Position.y += Velocity.y;

	fDirection = GetAngle(Velocity) - PI / 2.f;

	if (FrameTime >= 600) isActive = false;
}
