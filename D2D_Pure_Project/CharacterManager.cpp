#include "stdafx.h"
#include "CharacterManager.h"


CharacterManager::CharacterManager()
	:pCharacter(nullptr)
{
}


CharacterManager::~CharacterManager()
{
}

HRESULT CharacterManager::Init(void)
{
	switch (_DB->LoadSelectCharacter())
	{
	case 0:
		pCharacter = new Character1;
		break;
	case 1:
		pCharacter = new Character2;
		break;
	case 2:
		pCharacter = new Character3;
		break;
	}

	pCharacter->Init();

	return S_OK;
}

void CharacterManager::Release(void)
{
	pCharacter->Release();
}

void CharacterManager::Update(void)
{
	pCharacter->Update();
}

void CharacterManager::Render(void)
{
	pCharacter->Render();
}

void CharacterManager::ResetCooltime(void)
{
	for (int i = 0; i < 5; ++i) {
		pCharacter->SetCoolTime(i);
	}
}
