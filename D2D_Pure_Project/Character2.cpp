#include "stdafx.h"
#include "Character2.h"


Character2::Character2()
{
	imgray = _ImageManager->FindImage("TimeStop");
	CoolTimeMax[0] = 8.f;
	CoolTimeMax[1] = 2.f;
	CoolTimeMax[2] = 10.f;
	CoolTimeMax[3] = 15.f;
	CoolTimeMax[4] = 30.f;
}


Character2::~Character2()
{
}

//	평타
void Character2::Skill0(void)
{
	_BulletManager->isFire(0, 10.f, front, 10.f, fangle);
	BulletTime = 0.1f;
}

//	방어스킬
void Character2::Skill1(void)
{
	isActive = 180;
	_DB->SetisStopOn(true);
	CoolTime[0] = CoolTimeMax[0];
}

//	마우스 우클릭
void Character2::Skill2(void)
{
	SkillAngle[1] = fangle - DegreeToRadian(50.f);
	CoolTime[1] = CoolTimeMax[1];
}

void Character2::Skill3(void)
{
	for (int i = 0; i < 12; ++i) {
		D2D_POINT_2F temp = { 120.f * sinf(DegreeToRadian(30.f*i)), -120.f * cosf(DegreeToRadian(30.f*i)) };
		_BulletManager->isOrbit(0, 10.f, { Ppos.x + temp.x, Ppos.y + temp.y });
	}
	CoolTime[2] = CoolTimeMax[2];
}

void Character2::Skill4(void)
{
	_BulletManager->isChain(0, 2.f, front);
	CoolTime[3] = CoolTimeMax[3];
}

void Character2::Skill5(void)
{
	isActive = 300;
	FrameTime = 0;
	_DB->SetisStopOn(true);
	CoolTime[4] = CoolTimeMax[4];
}

void Character2::ConsecutiveProcess(void)
{
	if (_DB->GetisStopOn() && CoolTime[0] <= 5.f && CoolTime[4] <= 27.f) _DB->SetisStopOn(false);

	if (CoolTime[1] >= 1.9f) { // 6 frame
		_BulletManager->isFire(0, 10.f, front, 10.f, SkillAngle[1]);
		SkillAngle[1] += DegreeToRadian(20.f);
	}

	if (FrameTime % 30 != 0) return; // 0.5초마다 실행

	if (CoolTime[4] >= 27.5f) {
		for (int i = 0; i < 60; ++i) {
			_BulletManager->isFocus(0, 10.f, Ppos, 2.f, GetRandomFloat(0, 2 * PI));
		}
	}
}

void Character2::AdditionalRender(void)
{
	if (_DB->GetisStopOn()) {
		imgray->Render(0.3f);
	}
}
