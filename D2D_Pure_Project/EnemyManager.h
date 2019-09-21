#pragma once
#include "Singletonbase.h"
#include <vector>
#include "Minion.h"
#include "Flier.h"
#include "Boss.h"

class EnemyManager : public SingletonBase<EnemyManager>
{
	vector<EnemyClass*> vEnemy;

public:
	EnemyManager();
	~EnemyManager();

	HRESULT CreateEnemy(UINT _Minionmax = 30, UINT _Fliermax = 10);
	void Release(void);
	void Update(void);
	void Render(void);

	void Reset(void);

	void ActiveEnemy(tagType _istype, float _speed, float _radius);

	vector<EnemyClass*> GetEnemys(void) { return vEnemy; }
};

