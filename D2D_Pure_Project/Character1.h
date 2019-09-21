#pragma once
#include "CharacterClass.h"

class Character1 : public CharacterClass
{
	ImageModule* iShield;

public:
	Character1();
	~Character1();

	void Skill0(void);
	void Skill1(void);
	void Skill2(void);
	void Skill3(void);
	void Skill4(void);
	void Skill5(void);

	void ConsecutiveProcess(void);
	void AdditionalRender(void);
};

