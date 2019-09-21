#pragma once
#include "ImageModule.h"

class CharacterClass
{
protected:
	ImageModule* img;
	Frame CurrentFrame;
	UINT FrameTime;
	float BulletTime;
	float CoolTime[5];
	float CoolTimeMax[5];
	float SkillAngle[5];
	float alpha;
	float alphadirc;

	float fradius;
	float fangle;
	float fspeed;

	D2D1_ELLIPSE circle;	//	Render 충돌반경
	D2D_POINT_2F front;		//	실제 정면좌표
	D2D_POINT_2F p2Render;	//	Render좌표

	UINT Hp;
	UINT isActive;

public:
	CharacterClass();
	~CharacterClass();

	virtual HRESULT Init(void);
	virtual void Release(void);
	virtual void Update(void);
	virtual void Render(void);

	virtual void Move(void);

	virtual void Skill0(void) = 0;	//	기본공격 (마우스 좌클릭)
	virtual void Skill1(void) = 0;	//	방어기술 (스페이스바)
	virtual void Skill2(void) = 0;	//	스킬1 (마우스 우클릭)
	virtual void Skill3(void) = 0;	//	스킬2 (Q)
	virtual void Skill4(void) = 0;	//	스킬3 (E)
	virtual void Skill5(void) = 0;	//	스킬4 (R)

	virtual void ConsecutiveProcess(void) {};
	virtual void AdditionalRender(void) {};

	int GetHp(void) { return Hp; }
	void HitDamage(void) { Hp--; }
	void AddHp(void) { Hp++; }

	void SetIsActive(int _active = 180) { isActive = _active; };
	int GetIsActive(void) { return isActive; };

	void SetCoolTime(int _num, float _time = 0.f) { CoolTime[_num] = _time; }

	float GetCoolTime(int _num) { return CoolTime[_num]; }
	float GetCoolTimeMax(int _num) { return CoolTimeMax[_num]; }

	D2D1_ELLIPSE GetCircle(void) { return circle; }

	void DecreaseCoolTime(void);
};

