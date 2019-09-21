#pragma once
#include "BulletClass.h"

class BombBullet : public BulletClass
{
	bool isExplosion;

public:
	BombBullet();
	~BombBullet();

	HRESULT Init(void);
	void Update(void);

	void SetBulletImage(void);
};

