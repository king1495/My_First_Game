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

	D2D1_ELLIPSE circle;	//	Render �浹�ݰ�
	D2D_POINT_2F front;		//	���� ������ǥ
	D2D_POINT_2F p2Render;	//	Render��ǥ

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

	virtual void Skill0(void) = 0;	//	�⺻���� (���콺 ��Ŭ��)
	virtual void Skill1(void) = 0;	//	����� (�����̽���)
	virtual void Skill2(void) = 0;	//	��ų1 (���콺 ��Ŭ��)
	virtual void Skill3(void) = 0;	//	��ų2 (Q)
	virtual void Skill4(void) = 0;	//	��ų3 (E)
	virtual void Skill5(void) = 0;	//	��ų4 (R)

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

