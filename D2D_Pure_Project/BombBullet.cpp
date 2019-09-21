#include "stdafx.h"
#include "BombBullet.h"


BombBullet::BombBullet()
{
}


BombBullet::~BombBullet()
{
}

HRESULT BombBullet::Init(void)
{
	isType = Bomb;
	isExplosion = false;

	return S_OK;
}

void BombBullet::Update(void)
{
	if (!isActive) return;

	BoundCondition();

	Fly();
	
	p2Render.x = Position.x + _Camera->x;
	p2Render.y = Position.y + _Camera->y;

	circle = MakeCircle(p2Render.x, p2Render.y, fRadius);

	if (FrameTime >= 60 && !isExplosion) {
		isExplosion = true;
		img = _ImageManager->FindImage("Explosion_Bomb");
		CurrentFrame.frameX = 0;
		CurrentFrame.frameY = 0;
		CurrentFrame.frameMaxX = img->GetMaxFrameX();
		CurrentFrame.frameMaxY = img->GetMaxFrameY();
		scale = 0.f;
		Velocity.x = 0.f;
		Velocity.y = 0.f;
	}
	else if (FrameTime >= 60 && isExplosion) {
		fRadius = scale * 125.f;
		alpha -= _Timer->GetElapsedTime();
		scale += _Timer->GetElapsedTime();		
	}
	
	if (alpha <= 0.f) {
		isActive = false;
		isExplosion = false;
	}

	if (FrameTime % FrameFreq == 0) {
		CurrentFrame.frameX++;
		if (CurrentFrame.frameX >= CurrentFrame.frameMaxX) {
			CurrentFrame.frameX = 0;
			CurrentFrame.frameY++;
			if (CurrentFrame.frameY >= CurrentFrame.frameMaxY) {
				CurrentFrame.frameY = 0;
			}
		}
	}

	FrameTime++;
	if (FrameTime == UINT_MAX) FrameTime = 0;
}

void BombBullet::SetBulletImage(void)
{
	img = _ImageManager->FindImage("Magic_Bomb");
}
