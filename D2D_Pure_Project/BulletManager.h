#pragma once
#include "Singletonbase.h"
#include <vector>
#include "NormalBullet.h"
#include "GuidedBullet.h"
#include "BombBullet.h"
#include "OrbitBullet.h"
#include "ChainBullet.h"
#include "FocusBullet.h"
#include "SlashBullet.h"

class BulletManager : public SingletonBase<BulletManager>
{
private:
	vector<BulletClass*> vBullet;

public:
	BulletManager();
	~BulletManager();

	HRESULT CreateBullet();
	void Release(void);
	void Update(void);
	void Render(void);

	void Reset(void);

	bool isFire(int _whos_bullet, float _fRadius, D2D_POINT_2F _pos, D2D_POINT_2F _vel = { 0.f,0.f }, D2D_POINT_2F _acc = { 0.f,0.f });
	bool isFire(int _whos_bullet, float _fRadius, D2D_POINT_2F _pos, float _fSpeed, float _fDirc);

	bool isGuided(int _whos_bullet, float _fRadius, D2D_POINT_2F _pos, D2D_POINT_2F _vel = { 0.f,0.f }, D2D_POINT_2F _acc = { 0.f,0.f });
	bool isGuided(int _whos_bullet, float _fRadius, D2D_POINT_2F _pos, float _fSpeed, float _fDirc);

	bool isBomb(int _whos_bullet, float _fRadius, D2D_POINT_2F _pos, D2D_POINT_2F _vel = { 0.f,0.f }, D2D_POINT_2F _acc = { 0.f,0.f });
	bool isBomb(int _whos_bullet, float _fRadius, D2D_POINT_2F _pos, float _fSpeed, float _fDirc);

	bool isOrbit(int _whos_bullet, float _fRadius, D2D_POINT_2F _pos, D2D_POINT_2F _vel = { 0.f,0.f }, D2D_POINT_2F _acc = { 0.f,0.f });
	bool isOrbit(int _whos_bullet, float _fRadius, D2D_POINT_2F _pos, float _fSpeed, float _fDirc);

	bool isChain(int _whos_bullet, float _fRadius, D2D_POINT_2F _pos, D2D_POINT_2F _vel = { 0.f,0.f }, D2D_POINT_2F _acc = { 0.f,0.f });
	bool isChain(int _whos_bullet, float _fRadius, D2D_POINT_2F _pos, float _fSpeed, float _fDirc);

	bool isFocus(int _whos_bullet, float _fRadius, D2D_POINT_2F _pos, D2D_POINT_2F _vel = { 0.f,0.f }, D2D_POINT_2F _acc = { 0.f,0.f });
	bool isFocus(int _whos_bullet, float _fRadius, D2D_POINT_2F _pos, float _fSpeed, float _fDirc);

	bool isSlash(int _whos_bullet, float _fRadius, D2D_POINT_2F _pos, D2D_POINT_2F _vel = { 0.f,0.f }, D2D_POINT_2F _acc = { 0.f,0.f });
	bool isSlash(int _whos_bullet, float _fRadius, D2D_POINT_2F _pos, float _fSpeed, float _fDirc);

	vector<BulletClass*> GetBullets(void) { return vBullet; }
};

