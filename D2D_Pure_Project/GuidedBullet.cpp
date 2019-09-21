#include "stdafx.h"
#include "GuidedBullet.h"


GuidedBullet::GuidedBullet()
	:pEnemy(nullptr)
{
}

GuidedBullet::~GuidedBullet()
{
}

HRESULT GuidedBullet::Init(void)
{
	isType = Guided;

	return S_OK;
}

void GuidedBullet::SetTarget(void)
{
	//	타겟의 포인터가 있고, 타겟이 살아있으면 타겟을 바꾸지 않음
	if (pEnemy && pEnemy->GetisActive()) return;

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
		}
	}
	pEnemy = vEnemys[num];
}

void GuidedBullet::Fly(void)
{
	float fDist = FloatMax();
	float fAngle = 0.f;
	if (whos_bullet == 0) {
		SetTarget();
		fDist = GetDistance(p2Render, pEnemy->GetCircle().point);
		fAngle = GetAngle(p2Render, pEnemy->GetCircle().point) + PI / 2.f;
	}
	else if(whos_bullet == 1){
		fDist = GetDistance(p2Render.x, p2Render.y, Ppos.x + _Camera->x, Ppos.y + _Camera->y);
		fAngle = GetAngle(p2Render.x, p2Render.y, Ppos.x + _Camera->x, Ppos.y + _Camera->y) + PI / 2.f;
	}
	//	거리 = 시간*속력

	fDist = (fDist < 0.2f) ? 0.2f : fDist;

	Acceleration.x = 25.f*sinf(fAngle) / fDist;
	Acceleration.y = -25.f*cosf(fAngle) / fDist;

	Velocity.x += Acceleration.x;
	Velocity.y += Acceleration.y;

	Position.x += Velocity.x;
	Position.y += Velocity.y;

	fSpeed = GetDistance(Velocity);
	fDirection = GetAngle(Velocity) - PI / 2.f;
}

void GuidedBullet::SetBulletImage(void)
{
	switch (whos_bullet)
	{
	case 0:
		img = _ImageManager->FindImage("Creature");
		break;
	case 1:
		img = _ImageManager->FindImage("eBullet");
		break;
	}
}
