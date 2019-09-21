#pragma once
#include "EnemyClass.h"

class Boss: public EnemyClass
{
	int pattern_num;
	float skillangle;

public:
	Boss();
	~Boss();

	void Move(void);
	void Attack(void);
};

