#include "stdafx.h"
#include "MainEntryClass.h"

MainEntryClass::MainEntryClass()
{
}

MainEntryClass::~MainEntryClass()
{
	_KeyCode->ReleaseSingleton();
	_ImageManager->ReleaseSingleton();
	_Camera->ReleaseSingleton();
	_Scene->ReleaseSingleton();
	_DB->ReleaseSingleton();
	_BulletManager->ReleaseSingleton();
	_EnemyManager->ReleaseSingleton();
	_FontManager->ReleaseSingleton();
}

//	���α׷� ����ɶ� �ѹ��� ȣ��
HRESULT MainEntryClass::Init(void)
{
	_FontManager->Create("TITLE", "�޸հ��", 40.f, DWRITE_TEXT_ALIGNMENT_CENTER, DWRITE_FONT_WEIGHT_BOLD);
	_FontManager->Create("SCORE", "�޸հ��", 24.f);
	_FontManager->Create("CHARACTER_NAME", "�޸հ��", 20.f, DWRITE_TEXT_ALIGNMENT_CENTER, DWRITE_FONT_WEIGHT_BOLD);
	_FontManager->Create("SKILL", "�޸հ��", 22.f, DWRITE_TEXT_ALIGNMENT_CENTER, DWRITE_FONT_WEIGHT_BOLD);

	//	�̹��� �ʱ�ȭ
	_ImageManager->CreateImage("Background", "image/Background.jpg");
	_ImageManager->CreateImage("Background_Boss", "image/Background_Boss.png");
	_ImageManager->CreateImage("GameOver", "image/Gameover.png");

	//	�÷��̾� �̹��� �б�
	_ImageManager->CreateFrameImage("Player1", "image/Player1_IDLE.png", 4, 1);
	_ImageManager->CreateFrameImage("Player2", "image/Player2_IDLE.png", 4, 1);
	_ImageManager->CreateFrameImage("Player3", "image/Player3_IDLE.png", 4, 1);

	_ImageManager->CreateFrameImage("Bullet1", "image/Player1_bullet.png", 8, 1);
	_ImageManager->CreateFrameImage("Bullet2", "image/Player2_bullet.png", 1, 1);
	_ImageManager->CreateFrameImage("Bullet3", "image/Player3_bullet.png", 4, 1);

	_ImageManager->CreateFrameImage("Barrier", "image/Barrier.png", 1, 1);
	_ImageManager->CreateFrameImage("Creature", "image/Creature.png", 16, 1);
	_ImageManager->CreateFrameImage("Magic_Bomb", "image/Magic_Bomb.png", 4, 1);
	_ImageManager->CreateFrameImage("Explosion_Bomb", "image/Explosion_Bomb.png", 1, 1);
	_ImageManager->CreateFrameImage("Lightning", "image/Lightning.png", 1, 1);

	_ImageManager->CreateFrameImage("TimeStop", "image/Gray.png", 1, 1);
	_ImageManager->CreateFrameImage("Slash1", "image/Slash1.png", 1, 1);
	_ImageManager->CreateFrameImage("Slash2", "image/Slash2.png", 1, 1);


	//	�� �̹��� �б�
	_ImageManager->CreateFrameImage("Minion", "image/Minion.png", 1, 4);
	_ImageManager->CreateFrameImage("Flier", "image/Flier.png", 4, 6);
	_ImageManager->CreateFrameImage("Boss", "image/Boss.png", 4, 1);
	_ImageManager->CreateFrameImage("eBullet", "image/Enemy_bullet.png", 6, 1);

	//	������ �̹���

	_ImageManager->CreateImage("Heal", "image/Heal.png");
	_ImageManager->CreateImage("CoolTime", "image/Cooltime.png");
	_ImageManager->CreateImage("Attack", "image/Attack.png");

	//	�ҷ� �ʱ�ȭ
	_BulletManager->CreateBullet();

	//	�� �� �ʱ�ȭ
	_EnemyManager->CreateEnemy(30, 10);

	_Scene->CreateScene("END_GAME_SCENE", new EndGameScene);
	_Scene->CreateScene("IN_GAME_SCENE", new InGameScene);
	_Scene->CreateScene("CHARACTER_SELECT_SCENE", new CharacterSelectScene);
	//_Scene->CreateScene("TITLE_SCENE", new TitleScene);

	_Scene->ChangeScene("CHARACTER_SELECT_SCENE");

	/*_Scene->CreateScene("TEST_SCENE", new TestScene);
	_Scene->ChangeScene("TEST_SCENE");*/

	return S_OK;
}

//	���α׷� �������� ȣ��
void MainEntryClass::Release(void)
{
	_BulletManager->Release();
	_EnemyManager->Release();
}

//�� �����Ӹ��� ȣ��
void MainEntryClass::Update(void)
{
	_Scene->Update();
}

void MainEntryClass::Render(void)
{
	_Scene->Render();
}