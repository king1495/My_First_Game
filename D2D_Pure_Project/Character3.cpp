#include "stdafx.h"
#include "Character3.h"


Character3::Character3()
	:SlashCount(3), SlashFrame(0)
{
	imSlash[0] = _ImageManager->FindImage("Slash1");
	imSlash[1] = _ImageManager->FindImage("Slash2");
	CoolTimeMax[0] = 8.f;
	CoolTimeMax[1] = 3.f;
	CoolTimeMax[2] = 5.f;
	CoolTimeMax[3] = 15.f;
	CoolTimeMax[4] = 30.f;
}


Character3::~Character3()
{
}

void Character3::Skill0(void)
{
	_BulletManager->isSlash(0, 50.f, { front.x + 10.f*sinf(fangle), front.y - 10.f*cosf(fangle) }, 0.1f, fangle + PI / 3.f);
	BulletTime = 0.15f;
}

void Character3::Skill1(void)
{
	isActive = 320;
	_DB->SetisReflectOn(true);
	oldRadius = fradius;
	fradius = 60.f;
	CoolTime[0] = CoolTimeMax[0];
}

void Character3::Skill2(void)
{
	isActive = 30;
	SlashCount--;
	SlashFrame = 6;
	SlashAngle = fangle;
	if (SlashCount == 0) {
		CoolTime[1] = CoolTimeMax[1];
	}
}

void Character3::Skill3(void)
{
	_BulletManager->isSlash(0, 75.f, front, 10.f, fangle);
	CoolTime[2] = CoolTimeMax[2];
}

void Character3::Skill4(void)
{
	_BulletManager->isSlash(0, 150.f, { front.x + 100.f*sinf(fangle), front.y - 100.f*cosf(fangle) }, 0.1f, fangle + PI / 3.f);
	CoolTime[3] = CoolTimeMax[3];
}

void Character3::Skill5(void)
{
	isActive = 6000;
	_DB->SetisDelayOn(true);
	CoolTime[4] = CoolTimeMax[4];
}

void Character3::ConsecutiveProcess(void)
{
	if (SlashFrame > 0) {
		Ppos.x += 25.f * sinf(SlashAngle);
		Ppos.y += -25.f * cosf(SlashAngle);

		if (!(Ppos.x <= 0 || Ppos.x >= WinSizeX)) {
			_Camera->x -= 25.f * sinf(SlashAngle);
		}

		if (!(Ppos.y <= 0 || Ppos.y >= WinSizeY)) {
			_Camera->y -= -25.f * cosf(SlashAngle);
		}

		_BulletManager->isSlash(0, 70.f, { front.x + 20.f*sinf(SlashAngle), front.y - 20.f*cosf(SlashAngle) }, 0.1f, SlashAngle + PI / 3.f);
		SlashFrame--;
	}

	if (CoolTime[4] < 25.f && CoolTime[0] < 5.f && _DB->GetisReflectOn()) {
		_DB->SetisReflectOn(false);
		fradius = oldRadius;
	}

	if (SlashCount == 0 && CoolTime[1] <= 0.f) SlashCount = 3;

	if (CoolTime[4] < 25.f && _DB->GetisDelayOn()) {
		_DB->SetisDelayOn(false);
	}

	if (CoolTime[4] >= 25.f) {
		CoolTime[0] = 0;
		CoolTime[1] = 0;
		CoolTime[2] = 0;
		CoolTime[3] = 0;
	}
}

void Character3::AdditionalRender(void)
{
	if (_DB->GetisReflectOn()) {
		float rand_radius = GetRandomFloat(50.f, 70.f);
		float rand_angle = GetRandomFloat(0, 2 * PI);

		imSlash[GetRandomInt()]->RenderCenter(
			rand_radius * sinf(rand_angle) + p2Render.x,
			-rand_radius * cosf(rand_angle) + p2Render.y,
			1.f, false,
			RadianToDegree(GetRandomFloat(0, 2 * PI)),
			0.5f, 0.5f);
	}
}
