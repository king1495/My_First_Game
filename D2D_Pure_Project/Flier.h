#pragma once
#include "EnemyClass.h"

class Flier : public EnemyClass
{
	bool isMoveOn;
	float move_angle;

public:
	Flier();
	~Flier();

	void Move(void);
	void Attack(void);
};

