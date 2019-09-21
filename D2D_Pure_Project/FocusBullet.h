#pragma once
#include "BulletClass.h"

class FocusBullet : public BulletClass
{
public:
	FocusBullet();
	~FocusBullet();

	HRESULT Init(void);

	void Fly(void);
};

