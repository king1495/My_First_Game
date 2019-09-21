#pragma once
#include "BulletClass.h"

class SlashBullet : public BulletClass
{
	UINT StopFrame;

public:
	SlashBullet();
	~SlashBullet();
	
	HRESULT Init(void);

	void InitFire(void);
	void AdditionalRender(void);

	void Fly(void);
};

