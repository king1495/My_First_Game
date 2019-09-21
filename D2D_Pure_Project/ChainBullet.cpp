#include "stdafx.h"
#include "ChainBullet.h"


ChainBullet::ChainBullet()
	:pEnemy(nullptr)
{
}


ChainBullet::~ChainBullet()
{
}

HRESULT ChainBullet::Init(void)
{
	isType = Chain;
	chainImg = _ImageManager->FindImage("Lightning");

	return S_OK;
}

void ChainBullet::InitFire(void)
{
	Hp = 20;
	light_center = D2D_POINT_2F();
}

void ChainBullet::Fly(void)
{
	if (FrameTime % 5 != 0) return;

	D2D_POINT_2F ePos = D2D_POINT_2F();
	fDist = FloatMax();
	vector<EnemyClass*> vEnemys = _EnemyManager->GetEnemys();

	for (int i = 0; i < vEnemys.size(); ++i) {
		if (!vEnemys[i]->GetisActive()) continue;
		D2D_POINT_2F tempPos = vEnemys[i]->GetCircle().point;
		float temp = GetDistance(p2Render, tempPos);
		if (temp < fDist) {
			fDist = temp;
			ePos = tempPos;
			fDirection = GetAngle(p2Render, ePos) + PI / 2.f;
		}
	}

	if (fDist > 500.f || fDist == 0.f) {
		isActive = false;
		return;
	}

	Position = { ePos.x - _Camera->x,ePos.y - _Camera->y };

	light_center = { (p2Render.x + ePos.x) / 2.f , (p2Render.y + ePos.y) / 2.f };
}

void ChainBullet::AdditionalRender(void)
{
	chainImg->CropRenderCenter(light_center.x, light_center.y, 0.8f, RadianToDegree(fDirection), { 0,chainImg->GetWidth() }, { 0,fDist });
}
