#pragma once
#include "Singletonbase.h"

class Database : public SingletonBase<Database>
{
	int Select_Character;
	UINT Attack_Power;
	bool isDelayOn;
	bool isStopOn;
	bool isReflectOn;

public:
	Database();
	~Database();

	void SaveSelectCharacter(int _num) { Select_Character = _num; }
	int LoadSelectCharacter(void) { return Select_Character; }

	void SetAttack_Power(UINT _power = 1) { Attack_Power = _power; }
	UINT GetAttack_Power(void) { return Attack_Power; }

	void SetisDelayOn(bool _bool) { isDelayOn = _bool; }
	bool GetisDelayOn(void) { return isDelayOn; }
	
	void SetisStopOn(bool _bool) { isStopOn = _bool; }
	bool GetisStopOn(void) { return isStopOn; }

	void SetisReflectOn(bool _bool) { isReflectOn = _bool; }
	bool GetisReflectOn(void) { return isReflectOn; }
};