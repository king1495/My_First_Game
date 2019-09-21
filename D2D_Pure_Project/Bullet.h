#pragma once
#include "ImageModule.h"

class Bullet
{
	struct Frame {
		int frameX, frameY;
		int frameMaxX, frameMaxY;
	};

	string BULLET_NAME[4];

	ImageModule * img;
	Frame CurrentFrame;
	UINT FrameTime;
	UINT FrameFreq;
	D2D1_ELLIPSE circle;	//	Render 충돌반경
	D2D_POINT_2F center;	//	실제 중심좌표
	D2D_POINT_2F p2Render;	//	Render좌표
	int whos_bullet;
	int type;
	int hp;
	float fSpeed;
	float fRadius;
	float fAngle;

	bool isActive;

public:		//	기본 생성자 + 초기 생성자
	Bullet();
	~Bullet();

	HRESULT Init();
	void Release(void);
	void Update(void);
	void Render(void);

public:
	void isFire(float _x, float _y, float _fRadius, float _fSpeed, float _fAngle, int _whos_bullet, int _istype);

	int GetWhos(void) { return whos_bullet; }
	int GetType(void) { return type; }
	int GetHp(void) { return hp; }

	bool GetisActive(void) { return isActive; }
	void SetisActive(bool _flag = false) { isActive = _flag; }
	D2D1_ELLIPSE GetCircle(void) { return circle; }

	void Reflect(void);
};

