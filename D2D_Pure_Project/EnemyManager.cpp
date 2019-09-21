#include "stdafx.h"
#include "EnemyManager.h"

EnemyManager::EnemyManager()
{
}

EnemyManager::~EnemyManager()
{
}

HRESULT EnemyManager::CreateEnemy(UINT _Minionmax, UINT _Fliermax)
{
	for (int i = 0; i < _Minionmax; ++i) {
		EnemyClass* Temp = new Minion();
		vEnemy.push_back(Temp);
	}

	for (int i = 0; i < _Fliermax; ++i) {
		EnemyClass* Temp = new Flier();
		vEnemy.push_back(Temp);
	}

	EnemyClass* Temp = new Boss();
	vEnemy.push_back(Temp);

	return S_OK;
}

void EnemyManager::Release(void)
{
	for (UINT i = 0; i < vEnemy.size(); ++i) {
		vEnemy[i]->Release();
		SafeDelete(vEnemy[i]);
	}
	vEnemy.clear();
}

void EnemyManager::Update(void)
{
	for (UINT i = 0; i < vEnemy.size(); ++i) {
		vEnemy[i]->Update();
	}
}

void EnemyManager::Render(void)
{
	for (UINT i = 0; i < vEnemy.size(); ++i)
		vEnemy[i]->Render();
}

void EnemyManager::ActiveEnemy(tagType _istype, float _speed, float _radius)
{
	for (UINT i = 0; i < vEnemy.size(); ++i) {
		if (vEnemy[i]->GetisActive() || vEnemy[i]->GetType() != _istype) continue;
		vEnemy[i]->Init(_speed, _radius);
		return;
	}
}

void EnemyManager::Reset(void)
{
	for (UINT i = 0; i < vEnemy.size(); ++i) {
		if (vEnemy[i]->GetisActive()) vEnemy[i]->SetisActive();
	}
}