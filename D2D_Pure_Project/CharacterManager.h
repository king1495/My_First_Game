#pragma once
#include "CharacterClass.h"
#include "Character1.h"
#include "Character2.h"
#include "Character3.h"
#include <vector>

class CharacterManager
{
	CharacterClass* pCharacter;

public:
	CharacterManager();
	~CharacterManager();

	HRESULT Init(void);
	void Release(void);
	void Update(void);
	void Render(void);

	void HitDamage(void) { pCharacter->HitDamage(); }
	void AddHp(void) { pCharacter->AddHp(); }
	int GetHp(void) { return pCharacter->GetHp(); }

	int GetisActive(void) { return pCharacter->GetIsActive(); }
	void SetisActive(int _isActive = 180) { pCharacter->SetIsActive(_isActive); }

	void ResetCooltime(void);

	D2D1_ELLIPSE GetCircle(void) { return pCharacter->GetCircle(); }
};

