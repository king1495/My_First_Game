#include "stdafx.h"
#include "Boss.h"


Boss::Boss()
{
	isType = isBoss;
	skillangle = 0.f;
	pattern_num = 0;
}


Boss::~Boss()
{
}

void Boss::Move(void)
{
	// 적 위치 업데이트

	fangle = GetAngle(center.x, center.y, Ppos.x, Ppos.y) + PI / 2.0f;

	center.x += sinf(fangle) * fspeed;
	center.y += -cosf(fangle) * fspeed;
}

void Boss::Attack(void)
{
	if (FrameTime == 120) {
		pattern_num = GetRandomInt(1, 5);
		skillangle = fangle;
		if (pattern_num == 1) {
			skillangle = fangle + GetRandomFloat(-PI / 3, PI / 3);
		}
	}

	switch (pattern_num) {
	case 1:
		if (FrameTime < 180) {
			center.x += 5.f * sinf(skillangle);
			center.y += -5.f * cosf(skillangle);
			if (FrameTime % 3 == 0) {
				_BulletManager->isFire(1, 5.f, center, 3.f, fangle);
				_BulletManager->isFire(1, 5.f, center, 3.f, fangle + DegreeToRadian(15.f));
				_BulletManager->isFire(1, 5.f, center, 3.f, fangle + DegreeToRadian(30.f));
				_BulletManager->isFire(1, 5.f, center, 3.f, fangle - DegreeToRadian(15.f));
				_BulletManager->isFire(1, 5.f, center, 3.f, fangle - DegreeToRadian(30.f));
			}
		}

		break;
	case 2:
		if (FrameTime < 180) {
			_BulletManager->isFire(1, 5.f, center, 3.f, fangle + GetRandomFloat(-PI / 6.f, PI / 6.f));
		}
		break;
	case 3:
		if (FrameTime < 140) {
			_BulletManager->isGuided(1, 5.f, center, 2.f, GetRandomFloat(0, 2 * PI));
		}
		break;
	case 4:
		if (FrameTime < 180) {
			_BulletManager->isFire(1, 5.f, { center.x - 200.f, center.y }, 3.f, skillangle);
			_BulletManager->isFire(1, 5.f, { center.x + 200.f, center.y }, 3.f, skillangle);
			_BulletManager->isFire(1, 5.f, { center.x, center.y + 200.f }, 3.f, skillangle);
			_BulletManager->isFire(1, 5.f, { center.x, center.y - 200.f }, 3.f, skillangle);
			skillangle += DegreeToRadian(13.f);
		}
		break;
	case 5:
		if (FrameTime < 240) {
			_BulletManager->isFire(1, 5.f, center, 3.f, skillangle);
			_BulletManager->isFire(1, 5.f, center, 3.f, skillangle + DegreeToRadian(90.f));
			_BulletManager->isFire(1, 5.f, center, 3.f, skillangle + DegreeToRadian(180.f));
			_BulletManager->isFire(1, 5.f, center, 3.f, skillangle + DegreeToRadian(270.f));
			skillangle += DegreeToRadian(8.f);
		}
		break;
	}

	if (FrameTime > 300) {
		FrameTime = 0;
		pattern_num = 0;
	}
}
