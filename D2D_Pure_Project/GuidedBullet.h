#pragma once
#include "BulletClass.h"
#include "EnemyClass.h"

class GuidedBullet : public BulletClass
{
	EnemyClass* pEnemy;

public:
	GuidedBullet();
	~GuidedBullet();

	HRESULT Init(void);

	void SetTarget(void);
	void Fly(void);
	void SetBulletImage(void);
};

