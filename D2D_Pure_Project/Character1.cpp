#include "stdafx.h"
#include "Character1.h"

Character1::Character1()
{
	iShield = _ImageManager->FindImage("Barrier");
	CoolTimeMax[0] = 8.f;
	CoolTimeMax[1] = 3.f;
	CoolTimeMax[2] = 10.f;
	CoolTimeMax[3] = 15.f;
	CoolTimeMax[4] = 30.f;
}

Character1::~Character1()
{
}

void Character1::Skill0(void)
{
	_BulletManager->isFire(0, 10.f, front, 10.f, fangle);
	BulletTime = 0.1f;
}

void Character1::Skill1(void)
{
	isActive = 200;
	CoolTime[0] = CoolTimeMax[0];
}

void Character1::Skill2(void)
{
	for (int i = 0; i < 13; ++i) {
		_BulletManager->isFire(0, 10.f, front, 6.f, fangle + PI * (6 - i) / 30.f);
		_BulletManager->isFire(0, 10.f, front, 8.f, fangle + PI * (6 - i) / 30.f);
		_BulletManager->isFire(0, 10.f, front, 10.f, fangle + PI * (6 - i) / 30.f);
	}
	CoolTime[1] = CoolTimeMax[1];
}

void Character1::Skill3(void)
{
	_BulletManager->isBomb(0, 0.f, front, 2.f, fangle);
	CoolTime[2] = CoolTimeMax[2];
}

void Character1::Skill4(void)
{
	for (int i = 0; i < 12; ++i) {
		_BulletManager->isGuided(0, 10.f, Ppos, 2.f, fangle + (30.f*i * PI / 180.f));
	}
	CoolTime[3] = CoolTimeMax[3];
}

void Character1::Skill5(void)
{
	isActive = 180;
	SkillAngle[4] = fangle;
	CoolTime[4] = CoolTimeMax[4];
}

void Character1::ConsecutiveProcess(void)
{
	if (CoolTime[4] >= 29.f) {
		_BulletManager->isFire(0, 10.f, Ppos, 10.f, SkillAngle[4]);
		_BulletManager->isFire(0, 10.f, Ppos, 10.f, SkillAngle[4] + DegreeToRadian(90.f));
		_BulletManager->isFire(0, 10.f, Ppos, 10.f, SkillAngle[4] + DegreeToRadian(180.f));
		_BulletManager->isFire(0, 10.f, Ppos, 10.f, SkillAngle[4] + DegreeToRadian(270.f));
		SkillAngle[4] += DegreeToRadian(12.f);
	}
}

void Character1::AdditionalRender(void)
{
	if (isActive > 0 && CoolTime[0] > 5.f) {
		iShield->RenderCenter(p2Render.x, p2Render.y);
		fradius = iShield->GetFrameWidth()/2.f;
		circle = MakeCircle(
			WinSizeX / 2.f,
			WinSizeY / 2.f,
			fradius);
	}
	else if (isActive > 0 && CoolTime[0] > 4.f && fradius != 5.f) {
		fradius = 5.f;
		circle = MakeCircle(
			WinSizeX / 2.f,
			WinSizeY / 2.f,
			fradius);
	}
}
