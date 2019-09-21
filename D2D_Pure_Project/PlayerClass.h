#pragma once
#include "ImageModule.h"
#include "BulletManager.h"
#include "cApplication.h"

class PlayerClass
{
	ImageModule* img;
	UINT BulletTime;
	float CoolTime[5];
	float SkillAngle[5];
	Frame CurrentFrame;
	UINT FrameTime;
	D2D1_ELLIPSE circle;	//	Render �浹�ݰ�
	D2D_POINT_2F front;		//	���� ������ǥ
	D2D_POINT_2F p2Render;	//	Render��ǥ
	int Hp;
	float fradius;
	float fangle;
	float fspeed;
	float alpha;
	float alphadirc;

	int isActive;

public:
	PlayerClass();
	~PlayerClass();

	HRESULT Init(void);
	void Release(void);
	void Update(void);
	void Render(void);

	void HitDamage(void) { Hp--; }
	int GetHp(void) { return Hp; }
	int GetisActive(void) { return isActive; }
	void SetisActive(int _isActive = 180) { isActive = _isActive; }

	D2D1_ELLIPSE GetCircle(void) { return circle; }
};

