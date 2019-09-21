#include "stdafx.h"
#include "Flier.h"


Flier::Flier()
	:move_angle(0.f), isMoveOn(false)
{
	isType = isFlier;
}


Flier::~Flier()
{
}

void Flier::Move(void)
{
	if (_DB->GetisDelayOn()) {
		if (FrameTime % 6 != 0) return;
	}

	if (FrameTime % 180 == 0)
	{
		isMoveOn = true;
		move_angle = GetRandomFloat(0, 2 * PI);
	}

	if (FrameTime % 186 == 0)
	{
		isMoveOn = false;
		FrameTime = 0;
	}
	
	// 적 위치 업데이트
	if (isMoveOn) {
		center.x += sinf(move_angle) * fspeed;
		center.y += -cosf(move_angle) * fspeed;
	}

	fangle = GetAngle(center.x, center.y, Ppos.x, Ppos.y) + PI / 2.0f;
}

void Flier::Attack(void)
{
	if (FrameTime % 180 == 0) {
		_BulletManager->isFire(1, 5.f, center, 2.f, fangle);
	}
}