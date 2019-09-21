#pragma once

#include "ImageModule.h"
#include "CharacterManager.h"
#include "ItemManager.h"

class InGameScene : public cApplication
{
	ImageModule* backImg;
	ImageModule* GameoverImg;
	CharacterManager* pPlayer;
	ItemManager* pItem;
	bool isGameover;
	bool isWin;
	bool isBossOn;
	int Score;

public:
	InGameScene();
	~InGameScene();

	HRESULT Init(void) override;
	void Release(void) override;
	void Update(void) override;
	void Render(void) override;

	void CollisionCheck();
};

