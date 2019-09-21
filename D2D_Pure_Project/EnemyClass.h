#pragma once

enum tagType {
	isMinion,
	isFlier,
	isBoss
};

class EnemyClass
{
	struct Frame {
		int frameX, frameY;
		int frameMaxX, frameMaxY;
	};
	string ImageName[3];
	ImageModule* img;
	Frame CurrentFrame;
	float alpha;

protected:
	D2D1_ELLIPSE circle;	//	Render �浹�ݰ�
	D2D_POINT_2F center;	//	���� �߽���ǥ
	D2D_POINT_2F p2Render;	//	Render��ǥ
	UINT FrameTime;
	UINT FrameFreq;
	int Hp;
	float width, height;
	float fradius;
	float fspeed;
	float fangle;

	tagType isType;
	bool isActive;

public:
	EnemyClass();
	~EnemyClass();

	virtual HRESULT Init(float _speed, float _radius);
	virtual void Release(void);
	virtual void Update(void);
	virtual void Render(void);

	void SetHp(int _Hp) { Hp = _Hp; }
	void SetX(int _X) { center.x = _X; }
	void SetY(int _Y) { center.y = _Y; }
	void SetRadius(int _radius) { fradius = _radius; }
	void SetSpeed(int _speed) { fspeed = _speed; }
	void SetDirc(int _angle) { fangle = _angle; }
	void SetisActive(bool _flag = false) { isActive = _flag; }
	void SetType(tagType _istype) { isType = _istype; }

	int GetHp(void) { return Hp; }
	float GetX(void) { return center.x; }
	float GetY(void) { return center.y; }
	float GetRadius(void) { return fradius; }
	float GetSpeed(void) { return fspeed; }
	float GetDirc(void) { return fangle; }
	bool GetisActive(void) { return isActive; }
	tagType GetType(void) { return isType; }

	UINT GetFrameTime(void) { return FrameTime; }

	D2D1_ELLIPSE GetCircle(void) { return circle; }

	void HitDamage(UINT _dmg = 1) { Hp -= _dmg; }

	virtual void Move(void) {};	//	���� �����Լ� (��ӹ��� Ŭ�������� ���������������� ��������)
	virtual void Attack(void) {};	//	���� �����Լ� (��ӹ��� Ŭ�������� ���������������� ��������)
};

