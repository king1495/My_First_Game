#pragma once
#include "CharacterClass.h"

class Character3 : public CharacterClass
{
	ImageModule* imSlash[2];
	UINT SlashCount;
	UINT SlashFrame;
	float SlashAngle;
	float oldRadius;

public:
	Character3();
	~Character3();

	void Skill0(void);
	void Skill1(void);
	void Skill2(void);
	void Skill3(void);
	void Skill4(void);
	void Skill5(void);

	void ConsecutiveProcess(void);
	void AdditionalRender(void);
};

