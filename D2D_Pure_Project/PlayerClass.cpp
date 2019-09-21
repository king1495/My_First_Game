#include "stdafx.h"
#include "PlayerClass.h"

PlayerClass::PlayerClass()
	: fangle(90.f), Hp(3),
	FrameTime(0), BulletTime(0),
	fradius(5.f), fspeed(6.f), isActive(60),
	alpha(1.0f), alphadirc(1.f)
{
	ZeroMemory(CoolTime, sizeof CoolTime);
	ZeroMemory(SkillAngle, sizeof SkillAngle);
}


PlayerClass::~PlayerClass()
{
}

HRESULT PlayerClass::Init(void)
{
	string PlayerImages[] = {
		"Player1",
		"Player2",
		"Player3"
	};

	img = _ImageManager->FindImage(PlayerImages[_DB->LoadSelectCharacter()]);
	//laser = _ImageManager->FindImage("Laser");
	//barrier = _ImageManager->FindImage("Barrier");

	//	실제 충돌반경 초기화
	circle = MakeCircle(
		WinSizeX / 2.f,
		WinSizeY / 2.f,
		fradius);

	//	Render좌표 초기화
	p2Render.x = WinSizeX / 2.f;
	p2Render.y = WinSizeY / 2.f;

	//	플레이어 중심좌표 전역변수
	Ppos = circle.point;

	CurrentFrame.frameX = 0;
	CurrentFrame.frameY = 0;
	CurrentFrame.frameMaxX = img->GetMaxFrameX();
	CurrentFrame.frameMaxY = img->GetMaxFrameY();

	return S_OK;
}

void PlayerClass::Release(void)
{
}

void PlayerClass::Update(void)
{
	if (_KeyCode->StayKeyDown('A')) {
		_Camera->x += fspeed;
		Ppos.x -= fspeed;
	}
	if (_KeyCode->StayKeyDown('D')) {
		_Camera->x -= fspeed;
		Ppos.x += fspeed;
	}
	if (_KeyCode->StayKeyDown('W')) {
		_Camera->y += fspeed;
		Ppos.y -= fspeed;
	}
	if (_KeyCode->StayKeyDown('S')) {
		_Camera->y -= fspeed;
		Ppos.y += fspeed;
	}

	fangle = GetAngle(WinSizeX / 2.f, WinSizeY / 2.f, (float)AppMouse.x, (float)AppMouse.y) + PI / 2.0f;	//	이건 고정

	//	실제 정면좌표 계산
	front =
	{ Ppos.x + (img->GetFrameHeight()*sinf(fangle) / 2.f),
		Ppos.y - (img->GetFrameHeight()*cosf(fangle) / 2.f) };

	if (_KeyCode->StayKeyDown(VK_LBUTTON) && BulletTime == 0) {
		_BulletManager->isFire(0, 10.f, front, 10.f, fangle);
		BulletTime = 5;
	}

	if (_KeyCode->isKeyDown(VK_RBUTTON) & CoolTime[0] <= 0) { // 전방 60도 영역으로 사격
		for (int i = 0; i < 13; ++i) {
			_BulletManager->isFire(0, 10.f, front, 6.f, fangle + PI * (6 - i) / 30.f);
			_BulletManager->isFire(0, 10.f, front, 8.f, fangle + PI * (6 - i) / 30.f);
			_BulletManager->isFire(0, 10.f, front, 10.f, fangle + PI * (6 - i) / 30.f);
		}
		CoolTime[0] = 5.f;
	}

	if (_KeyCode->isKeyDown('Q') & CoolTime[1] <= 0) {	// 수류탄 발사
		
			//_BulletManager->isFire(0, 10.f, front, fspeed, fangle);
		
		CoolTime[1] = 10.f;
	}

	if (_KeyCode->isKeyDown('E') & CoolTime[2] <= 0) {	//	유도탄 발사
		for (int i = 0; i < 12; ++i) {
			_BulletManager->isGuided(0, 10.f, Ppos, 2.f, fangle + (30.f*i * PI /180.f));
		}
		CoolTime[2] = 0.f;
	}
	if (_KeyCode->isKeyDown('R') & CoolTime[3] <= 0) {	// 주변 15도 간격으로 비사일 발사
		SkillAngle[3] = fangle;
		CoolTime[3] = 30.f;
	}

	if (_KeyCode->isKeyDown(VK_SPACE) & CoolTime[4] <= 0) {	// 주변 15도 간격으로 비사일 발사
		CoolTime[4] = 15.f;
	}

	if (CoolTime[3] >= 29.f) {
		_BulletManager->isFire(0, 10.f, Ppos, 10.f, SkillAngle[3]);
		_BulletManager->isFire(0, 10.f, Ppos, 10.f, SkillAngle[3] + DegreeToRadian(90.f));
		_BulletManager->isFire(0, 10.f, Ppos, 10.f, SkillAngle[3] + DegreeToRadian(180.f));
		_BulletManager->isFire(0, 10.f, Ppos, 10.f, SkillAngle[3] + DegreeToRadian(270.f));
		SkillAngle[3] += DegreeToRadian(12.f);
	}

	for (int i = 0; i < 5; ++i) {
		if (CoolTime[i] > 0) CoolTime[i] -= _Timer->GetElapsedTime(); // 1프레임당 시간 = Update() 한번 할때마다 시간 60FPS 1/60초
	}

	if (FrameTime % 2 == 0) {
		CurrentFrame = NextFrame(CurrentFrame);
	}

	FrameTime++;
	if (FrameTime == UINT_MAX) FrameTime = 0;
	if (BulletTime > 0) BulletTime--;
	if (isActive > 0) isActive--;
}

void PlayerClass::Render(void)
{
	TCHAR status[256];

	if (isActive > 0) {
		if (alpha > 1.f) {
			alphadirc = -1.f;
		}
		else if (alpha < 0.7f) {
			alphadirc = 1.f;
		}
		alpha += alphadirc * _Timer->GetElapsedTime()*2.f;
	}
	else {
		alpha = 1.0f;
	}

	img->FrameRenderCenter(p2Render.x, p2Render.y, CurrentFrame.frameX, CurrentFrame.frameY, alpha, false, RadianToDegree(fangle));

	//	스킬창 그리기
	for (int i = 0; i < 5; ++i) {
		D2D_RECT_F temp_rect = MakeRectCenter(WinSizeX / 2 - 50.f + (25.f*i), WinSizeY - 25.f, 25.f, 25.f);
		if (CoolTime[i] > 0) {
			_Device->ChangeColor(RGB(255, 0, 0));
		}
		else {
			_Device->ChangeColor(RGB(0, 255, 0));
		}
		_RenderTarget->FillRectangle(temp_rect, _Device->pDefaultBrush);
		_Device->ChangeColor(RGB(0, 0, 0));
		_RenderTarget->DrawRectangle(temp_rect, _Device->pDefaultBrush);
		if (CoolTime[i] > 0) {
			_stprintf_s(status, L"%.0f", CoolTime[i]);
			_Device->RenderText(status, temp_rect, _Device->pDefaultBrush, DWRITE_TEXT_ALIGNMENT_CENTER);
		}
	}

	if (_KeyCode->ToggleKeyDown(VK_TAB)) {
		_stprintf_s(status, L"x : %.2f, y : %.2f\ncx : %.2f, cy : %.2f\nAngle : %.2f\nHp : %d", p2Render.x, p2Render.y, Ppos.x, Ppos.y, 180.f * fangle / PI, Hp);
		_Device->RenderText(status, MakeRect(p2Render.x - img->GetFrameWidth() / 2.f, p2Render.y - img->GetFrameHeight() / 2.f, 200.f, -80.f));
		_RenderTarget->DrawEllipse(circle, _Device->pDefaultBrush);
	}
	else {
		_stprintf_s(status, L"Hp : %d", Hp);
		_Device->RenderText(status, MakeRect(p2Render.x - img->GetFrameWidth() / 2.f, p2Render.y - img->GetFrameHeight() / 2.f, 200.f, -20.f));
	}
}
