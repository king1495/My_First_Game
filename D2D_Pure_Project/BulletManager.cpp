#include "stdafx.h"
#include "BulletManager.h"


BulletManager::BulletManager()
{
}


BulletManager::~BulletManager()
{
	/*for (UINT i = 0; i < vBullet.size(); ++i) {
		vBullet[i]->Release();
		SafeDelete(vBullet[i]);
	}
	vBullet.clear();*/
}

HRESULT BulletManager::CreateBullet()
{
	for (UINT i = 0; i < 500; ++i) {
		BulletClass* Temp = new NormalBullet();
		if (FAILED(Temp->Init())) return E_FAIL;
		vBullet.push_back(Temp);
	}

	for (UINT i = 0; i < 50; ++i) {
		BulletClass* Temp = new GuidedBullet();
		if (FAILED(Temp->Init())) return E_FAIL;
		vBullet.push_back(Temp);
	}

	for (UINT i = 0; i < 300; ++i) {
		BulletClass* Temp = new FocusBullet();
		if (FAILED(Temp->Init())) return E_FAIL;
		vBullet.push_back(Temp);
	}

	for (UINT i = 0; i < 30; ++i) {
		BulletClass* Temp = new OrbitBullet();
		if (FAILED(Temp->Init())) return E_FAIL;
		vBullet.push_back(Temp);
	}

	for (UINT i = 0; i < 2; ++i) {
		BulletClass* Temp = new ChainBullet();
		if (FAILED(Temp->Init())) return E_FAIL;
		vBullet.push_back(Temp);
	}

	for (UINT i = 0; i < 2; ++i) {
		BulletClass* Temp = new BombBullet();
		if (FAILED(Temp->Init())) return E_FAIL;
		vBullet.push_back(Temp);
	}

	for (UINT i = 0; i < 15; ++i) {
		BulletClass* Temp = new SlashBullet();
		if (FAILED(Temp->Init())) return E_FAIL;
		vBullet.push_back(Temp);
	}

	return S_OK;
}

void BulletManager::Release(void)
{
	for (BulletClass* b : vBullet) {
		b->Release();
		SafeDelete(b);
	}
	vBullet.clear();
}

void BulletManager::Update(void)
{
	for (BulletClass* b : vBullet)
		b->Update();
}

void BulletManager::Render(void)
{
	for (BulletClass* b : vBullet)
		b->Render();
}

void BulletManager::Reset(void)
{
	for (UINT i = 0; i < vBullet.size(); ++i) {
		if (vBullet[i]->GetisActive()) vBullet[i]->SetisActive();
	}
}

bool BulletManager::isFire(int _whos_bullet, float _fRadius, D2D_POINT_2F _pos, D2D_POINT_2F _vel, D2D_POINT_2F _acc)
{
	for (BulletClass* b : vBullet) {
		if (b->GetisActive() || b->GetType() != Normal) continue;
		b->isFire(_whos_bullet, _fRadius, _pos, _vel, _acc);
		return true;
	}
	return false;
}

bool BulletManager::isFire(int _whos_bullet, float _fRadius, D2D_POINT_2F _pos, float _fSpeed, float _fDirc)
{
	D2D_POINT_2F _vel = { _fSpeed * sinf(_fDirc), -_fSpeed * cosf(_fDirc) };
	for (BulletClass* b : vBullet) {
		if (b->GetisActive() || b->GetType() != Normal) continue;
		b->isFire(_whos_bullet, _fRadius, _pos, _vel);
		return true;
	}
	return false;
}

bool BulletManager::isGuided(int _whos_bullet, float _fRadius, D2D_POINT_2F _pos, D2D_POINT_2F _vel, D2D_POINT_2F _acc)
{
	for (BulletClass* b : vBullet) {
		if (b->GetisActive() || b->GetType() != Guided) continue;
		b->isFire(_whos_bullet, _fRadius, _pos, _vel, _acc);
		return true;
	}
	return false;
}

bool BulletManager::isGuided(int _whos_bullet, float _fRadius, D2D_POINT_2F _pos, float _fSpeed, float _fDirc)
{
	D2D_POINT_2F _vel = { _fSpeed * sinf(_fDirc), -_fSpeed * cosf(_fDirc) };
	for (BulletClass* b : vBullet) {
		if (b->GetisActive() || b->GetType() != Guided) continue;
		b->isFire(_whos_bullet, _fRadius, _pos, _vel);
		return true;
	}
	return false;
}

bool BulletManager::isBomb(int _whos_bullet, float _fRadius, D2D_POINT_2F _pos, D2D_POINT_2F _vel, D2D_POINT_2F _acc)
{
	for (BulletClass* b : vBullet) {
		if (b->GetisActive() || b->GetType() != Bomb) continue;
		b->isFire(_whos_bullet, _fRadius, _pos, _vel, _acc);
		return true;
	}
	return false;
}

bool BulletManager::isBomb(int _whos_bullet, float _fRadius, D2D_POINT_2F _pos, float _fSpeed, float _fDirc)
{
	D2D_POINT_2F _vel = { _fSpeed * sinf(_fDirc), -_fSpeed * cosf(_fDirc) };
	for (BulletClass* b : vBullet) {
		if (b->GetisActive() || b->GetType() != Bomb) continue;
		b->isFire(_whos_bullet, _fRadius, _pos, _vel);
		return true;
	}
	return false;
}

bool BulletManager::isOrbit(int _whos_bullet, float _fRadius, D2D_POINT_2F _pos, D2D_POINT_2F _vel, D2D_POINT_2F _acc)
{
	for (BulletClass* b : vBullet) {
		if (b->GetisActive() || b->GetType() != Orbit) continue;
		b->isFire(_whos_bullet, _fRadius, _pos, _vel, _acc);
		return true;
	}
	return false;
}

bool BulletManager::isOrbit(int _whos_bullet, float _fRadius, D2D_POINT_2F _pos, float _fSpeed, float _fDirc)
{
	D2D_POINT_2F _vel = { _fSpeed * sinf(_fDirc), -_fSpeed * cosf(_fDirc) };
	for (BulletClass* b : vBullet) {
		if (b->GetisActive() || b->GetType() != Orbit) continue;
		b->isFire(_whos_bullet, _fRadius, _pos, _vel);
		return true;
	}
	return false;
}

bool BulletManager::isChain(int _whos_bullet, float _fRadius, D2D_POINT_2F _pos, D2D_POINT_2F _vel, D2D_POINT_2F _acc)
{
	for (BulletClass* b : vBullet) {
		if (b->GetisActive() || b->GetType() != Chain) continue;
		b->isFire(_whos_bullet, _fRadius, _pos, _vel, _acc);
		return true;
	}
	return false;
}

bool BulletManager::isChain(int _whos_bullet, float _fRadius, D2D_POINT_2F _pos, float _fSpeed, float _fDirc)
{
	D2D_POINT_2F _vel = { _fSpeed * sinf(_fDirc), -_fSpeed * cosf(_fDirc) };
	for (BulletClass* b : vBullet) {
		if (b->GetisActive() || b->GetType() != Chain) continue;
		b->isFire(_whos_bullet, _fRadius, _pos, _vel);
		return true;
	}
	return false;
}

bool BulletManager::isFocus(int _whos_bullet, float _fRadius, D2D_POINT_2F _pos, D2D_POINT_2F _vel, D2D_POINT_2F _acc)
{
	for (BulletClass* b : vBullet) {
		if (b->GetisActive() || b->GetType() != Focus) continue;
		b->isFire(_whos_bullet, _fRadius, _pos, _vel, _acc);
		return true;
	}
	return false;
}

bool BulletManager::isFocus(int _whos_bullet, float _fRadius, D2D_POINT_2F _pos, float _fSpeed, float _fDirc)
{
	D2D_POINT_2F _vel = { _fSpeed * sinf(_fDirc), -_fSpeed * cosf(_fDirc) };
	for (BulletClass* b : vBullet) {
		if (b->GetisActive() || b->GetType() != Focus) continue;
		b->isFire(_whos_bullet, _fRadius, _pos, _vel);
		return true;
	}
	return false;
}

bool BulletManager::isSlash(int _whos_bullet, float _fRadius, D2D_POINT_2F _pos, D2D_POINT_2F _vel, D2D_POINT_2F _acc)
{
	for (BulletClass* b : vBullet) {
		if (b->GetisActive() || b->GetType() != Slash) continue;
		b->isFire(_whos_bullet, _fRadius, _pos, _vel, _acc);
		return true;
	}
	return false;
}

bool BulletManager::isSlash(int _whos_bullet, float _fRadius, D2D_POINT_2F _pos, float _fSpeed, float _fDirc)
{
	D2D_POINT_2F _vel = { _fSpeed * sinf(_fDirc), -_fSpeed * cosf(_fDirc) };
	for (BulletClass* b : vBullet) {
		if (b->GetisActive() || b->GetType() != Slash) continue;
		b->isFire(_whos_bullet, _fRadius, _pos, _vel);
		return true;
	}
	return false;
}
