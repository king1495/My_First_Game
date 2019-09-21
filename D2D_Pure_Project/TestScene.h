#pragma once
#include "ImageModule.h"
#include "GuidedBullet.h"

class TestScene : public cApplication
{
	ImageModule* img;
	GuidedBullet* pBullet;
	D2D_RECT_F rect;
	float x, y;
	float scaleX, scaleY;
	float rotation;

public:
	TestScene();
	~TestScene();

	HRESULT Init(void) override;
	void Release(void) override;
	void Update(void) override;
	void Render(void) override;
};

