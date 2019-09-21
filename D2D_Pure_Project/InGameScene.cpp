#include "stdafx.h"
#include "InGameScene.h"


InGameScene::InGameScene()
	:Score(0), isGameover(false), isWin(false),
	isBossOn(false),
	pPlayer(nullptr), pItem(nullptr), backImg(nullptr)
{
}


InGameScene::~InGameScene()
{
}

HRESULT InGameScene::Init(void)
{
	backImg = _ImageManager->FindImage("Background");
	GameoverImg = _ImageManager->FindImage("GameOver");

	pPlayer = new CharacterManager;
	pPlayer->Init();

	pItem = new ItemManager;
	pItem->Init();

	Score = 0;
	isGameover = false;
	isWin = false;
	isBossOn = false;

	_DB->SetisDelayOn(false);
	_DB->SetisReflectOn(false);
	_DB->SetisStopOn(false);
	_DB->SetAttack_Power();

	return S_OK;
}

void InGameScene::Release(void)
{
	SafeDeleteClass(pItem);
	SafeDeleteClass(pPlayer);
}

void InGameScene::Update(void)
{
	if (isGameover) {
		if (_KeyCode->isKeyDown('R')) {
			_BulletManager->Reset();
			_EnemyManager->Reset();
			_Scene->ChangeScene("CHARACTER_SELECT_SCENE");
		}
		return;
	};

	_BulletManager->Update();
	_EnemyManager->Update();
	pPlayer->Update();
	pItem->Update();

	CollisionCheck();

	if (isWin) {
		_BulletManager->Reset();
		_EnemyManager->Reset();
		_Scene->ChangeScene("END_GAME_SCENE");
		return;
	}

	if (pPlayer->GetHp() <= 0) {
		isGameover = true;
	};

	if (Score > 100 && !isBossOn) {
		_EnemyManager->Reset();
		_EnemyManager->ActiveEnemy(isBoss, 0.5f, 50.f);
		backImg = _ImageManager->FindImage("Background_Boss");
		isBossOn = true;
	}
	else if (!isBossOn) {
		if (GetRandomInt(0, 99) > 90) {
			_EnemyManager->ActiveEnemy(isMinion, 1.f, 12.f);
		}

		if (GetRandomInt(0, 99) < 5) {
			_EnemyManager->ActiveEnemy(isFlier, 30.f, 12.f);
		}
	}


}

void InGameScene::Render(void)
{
	backImg->Render(_Camera->x - backImg->GetWidth() / 2.f, _Camera->y - backImg->GetHeight() / 2.f, 0.6f);
	backImg->Render(_Camera->x + backImg->GetWidth() / 2.f, _Camera->y - backImg->GetHeight() / 2.f, 0.6f);
	backImg->Render(_Camera->x - backImg->GetWidth() / 2.f, _Camera->y + backImg->GetHeight() / 2.f, 0.6f);
	backImg->Render(_Camera->x + backImg->GetWidth() / 2.f, _Camera->y + backImg->GetHeight() / 2.f, 0.6f);

	_BulletManager->Render();
	_EnemyManager->Render();
	pPlayer->Render();
	pItem->Render();

	TCHAR str[256];
	if (isGameover) {
		GameoverImg->RenderCenter(WinSizeX / 2.f, WinSizeY / 2.f, 1.f, false, 0.f, 0.8f, 0.8f);
	}
	else {
		_stprintf_s(str, L"Score : %d", Score);
		_FontManager->TextRender(str, MakeRectCenter(WinSizeX / 2.0f, 25.f, 200.f, 50.f), "SCORE");
	}
}
