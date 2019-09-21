#pragma once

enum tagItem {
	isHeal,
	isCoolTime,
	isAttack
};

class ItemClass
{
	string ImageName[3];
	ImageModule* img;
	float alpha;

protected:
	D2D1_ELLIPSE circle;	//	Render 충돌반경
	D2D_POINT_2F center;	//	실제 중심좌표
	D2D_POINT_2F p2Render;	//	Render좌표
	UINT FrameTime;
	float fradius;

	tagItem isType;
	bool isActive;

public:
	ItemClass();
	~ItemClass();

	HRESULT Init(tagItem _type = isHeal, D2D_POINT_2F _pos = D2D_POINT_2F());
	void Release(void);
	void Update(void);
	void Render(void);

	void SetisActive(bool _flag = false) { isActive = _flag; }

	bool GetisActive(void) { return isActive; }
	tagItem GetType(void) { return isType; }

	D2D1_ELLIPSE GetCircle(void) { return circle; }
};

