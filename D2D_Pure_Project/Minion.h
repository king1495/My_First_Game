#pragma once
#include "EnemyClass.h"

class Minion : public EnemyClass
{
public:
	Minion();
	~Minion();

	void Move(void);
	void Attack(void);
};

