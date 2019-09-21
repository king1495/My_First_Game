#pragma once
#include "BulletClass.h"

class OrbitBullet : public BulletClass
{
	float old_angle;

public:
	OrbitBullet();
	~OrbitBullet();

	HRESULT Init(void);
	void InitFire(void);

	void Fly(void);
	void SetBulletImage(void);
};

