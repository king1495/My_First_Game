#pragma once
#include "BulletClass.h"

class ChainBullet : public BulletClass
{
	ImageModule* chainImg;
	EnemyClass* pEnemy;

	D2D_POINT_2F light_center;
	float fDist;

public:
	ChainBullet();
	~ChainBullet();

	HRESULT Init(void);
	void InitFire(void);

	void Fly(void);

	void AdditionalRender(void);
};

