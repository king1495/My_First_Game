#pragma once

enum tagBullet {
	Normal,
	Guided,
	Bomb,
	Orbit,
	Chain,
	Focus,
	Slash
};

class BulletClass
{
protected:
	struct Frame {
		int frameX, frameY;
		int frameMaxX, frameMaxY;
	};

	ImageModule * img;
	Frame CurrentFrame;
	UINT FrameTime;
	UINT FrameFreq;
	D2D_POINT_2F p2Render;	//	Render좌표
	D2D1_ELLIPSE circle;	//	Render 충돌반경
	float alpha;
	float scale;

	int whos_bullet;	//	0이면 플레이어, 1이면 적군
	bool isActive;		//	탄이 활성화된 상태인지 아닌지
	bool isReverse;

	D2D_POINT_2F Position;	//	실제 중심좌표
	D2D_POINT_2F Velocity;	//	실제 속도
	D2D_POINT_2F Acceleration;	//	실제 가속도

	float fSpeed;
	float fDirection;
	float fRadius;

	tagBullet isType;
	int Hp;

public:
	BulletClass();
	~BulletClass();

	virtual HRESULT Init(void);
	virtual void Release(void);
	virtual void Update(void);
	virtual void Render(void);

	virtual HRESULT isFire(int _whos_bullet, float _fRadius, D2D_POINT_2F _pos, D2D_POINT_2F _vel = { 0.f,0.f }, D2D_POINT_2F _acc = { 0.f,0.f });

	virtual void BoundCondition(void);
	virtual void SetBulletImage(void);
	virtual void InitFire(void) { Hp = 1; };
	virtual void AdditionalRender(void) {};

	int GetWhos(void) { return whos_bullet; }
	int GetHp(void) { return Hp; }
	void HitDamage(void) { Hp--; }

	tagBullet GetType(void) { return isType; }

	bool GetisActive(void) { return isActive; }
	void SetisActive(bool _flag = false) { isActive = _flag; }
	D2D1_ELLIPSE GetCircle(void) { return circle; }

	float GetDirc(void) { return fDirection; }
	float GetSpeed(void) { return fSpeed; }

	virtual void Fly(void);
	virtual void Reflect(void);
};

