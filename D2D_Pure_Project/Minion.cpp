#include "stdafx.h"
#include "Minion.h"


Minion::Minion()
{
	isType = isMinion;
}


Minion::~Minion()
{
}

void Minion::Move(void)
{
	if (_DB->GetisDelayOn()) {
		if (FrameTime % 6 != 0) return;
	}

	// �� ��ġ ������Ʈ

	fangle = GetAngle(center.x, center.y, Ppos.x, Ppos.y) + PI / 2.0f;

	center.x += sinf(fangle) * fspeed;
	center.y += -cosf(fangle) * fspeed;
}

void Minion::Attack(void)
{
}
