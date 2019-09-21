#pragma once
#include "cApplication.h"
//#include "TitleScene.h"
#include "CharacterSelectScene.h"
#include "InGameScene.h"
#include "EndGameScene.h"
//#include "TestScene.h"

class MainEntryClass : public cApplication
{
public:
	MainEntryClass();
	~MainEntryClass();

	HRESULT Init(void) override;
	void Release(void) override;
	void Update(void) override;
	void Render(void) override;
};

