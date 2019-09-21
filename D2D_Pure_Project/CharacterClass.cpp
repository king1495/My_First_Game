#include "stdafx.h"
#include "CharacterClass.h"

CharacterClass::CharacterClass()
	:Hp(3), FrameTime(0), BulletTime(0.f),
	alpha(1.0f), alphadirc(1.f), isActive(120)
{
	ZeroMemory(CoolTime, sizeof CoolTime);
	ZeroMemory(CoolTimeMax, sizeof CoolTimeMax);
	ZeroMemory(SkillAngle, sizeof SkillAngle);
}


CharacterClass::~CharacterClass()
{
}

HRESULT CharacterClass::Init(void)
{
	string temp[] = {
		"Player1",
		"Player2",
		"Player3"
	};

	img = _ImageManager->FindImage(temp[_DB->LoadSelectCharacter()]);

	fradius = 5.f;
	fspeed = 6.f;

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

void CharacterClass::Release(void)
{
}

void CharacterClass::Update(void)
{
	Move();

	if (_KeyCode->StayKeyDown(VK_LBUTTON) && BulletTime <= 0) {
		Skill0();
	}

	if (_KeyCode->isKeyDown(VK_SPACE) && CoolTime[0] <= 0) {
		Skill1();
	}

	if (_KeyCode->isKeyDown(VK_RBUTTON) && CoolTime[1] <= 0) {
		Skill2();
	}

	if (_KeyCode->isKeyDown('Q') && CoolTime[2] <= 0) {
		Skill3();
	}

	if (_KeyCode->isKeyDown('E') && CoolTime[3] <= 0) {
		Skill4();
	}

	if (_KeyCode->isKeyDown('R') && CoolTime[4] <= 0) {
		Skill5();
	}

	ConsecutiveProcess();

	if (FrameTime % 2 == 0) {
		CurrentFrame = NextFrame(CurrentFrame);
	}

	DecreaseCoolTime();
	FrameTime++;
	if (FrameTime == UINT_MAX) FrameTime = 0;
	if (isActive > 0) isActive--;
	if (BulletTime > 0) BulletTime -= _Timer->GetElapsedTime();;
}

void CharacterClass::Render(void)
{
	TCHAR status[256];
	string skiilKey[] = {
		"SPC", "RB", "Q", "E", "R"
	};

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

	AdditionalRender();

	img->FrameRenderCenter(
		p2Render.x,
		p2Render.y,
		CurrentFrame.frameX,
		CurrentFrame.frameY,
		alpha,
		false,
		RadianToDegree(fangle));

	//	스킬창 그리기
	for (int i = 0; i < 5; ++i) {
		D2D_RECT_F temp_rect = MakeRectCenter(WinSizeX / 2 - 120.f + (60.f*i), WinSizeY - 30.f, 60.f, 60.f);

		//	녹색창
		_Device->ChangeColor(RGB(0, 255, 0));
		_RenderTarget->FillRectangle(temp_rect, _Device->pDefaultBrush);

		//	빨간창
		_Device->ChangeColor(RGB(255, 0, 0));
		_RenderTarget->FillRectangle(
			MakeRectCenter(WinSizeX / 2 - 120.f + (60.f*i), WinSizeY - 30.f, 60.f*CoolTime[i] / CoolTimeMax[i], 60.f*CoolTime[i] / CoolTimeMax[i])
			, _Device->pDefaultBrush);
		_Device->ChangeColor(RGB(0, 0, 0));
		_RenderTarget->DrawRectangle(temp_rect, _Device->pDefaultBrush);
		_FontManager->TextRender(skiilKey[i], MakeRectCenter(WinSizeX / 2 - 120.f + (60.f*i), WinSizeY - 75.f, 60.f, 30.f), "SKILL");

		if (CoolTime[i] > 0) {
			_stprintf_s(status, L"%.1f", CoolTime[i]);
			_FontManager->TextRender(status, temp_rect, "SKILL");
		}
	}

	if (_KeyCode->ToggleKeyDown(VK_TAB)) {
		_stprintf_s(status, L"x : %.2f, y : %.2f\ncx : %.2f, cy : %.2f\nAngle : %.2f\nHp : %d", p2Render.x, p2Render.y, Ppos.x, Ppos.y, 180.f * fangle / PI, Hp);
		_FontManager->TextRender(status, MakeRect(p2Render.x - img->GetFrameWidth() / 2.f, p2Render.y - img->GetFrameHeight() / 2.f, 200.f, -80.f));
		_RenderTarget->DrawEllipse(circle, _Device->pDefaultBrush);
	}
	else {
		_stprintf_s(status, L"Hp : %d", Hp);
		_FontManager->TextRender(status, MakeRect(p2Render.x - img->GetFrameWidth() / 2.f, p2Render.y - img->GetFrameHeight() / 2.f, 200.f, -20.f));
	}
}

void CharacterClass::Move(void)
{
	if (_KeyCode->StayKeyDown('A')) {
		Ppos.x -= fspeed;
	}
	if (_KeyCode->StayKeyDown('D')) {
		Ppos.x += fspeed;
	}
	if (_KeyCode->StayKeyDown('W')) {
		Ppos.y -= fspeed;
	}
	if (_KeyCode->StayKeyDown('S')) {
		Ppos.y += fspeed;
	}

	if (Ppos.x <= -WinSizeX / 2.f + fradius) Ppos.x = -WinSizeX / 2.f + fradius;
	if (Ppos.x >= 3.f*WinSizeX / 2.f - fradius) Ppos.x = 3.f*WinSizeX / 2.f - fradius;
	if (Ppos.y <= -WinSizeY / 2.f + fradius) Ppos.y = -WinSizeY / 2.f + fradius;
	if (Ppos.y >= 3.f*WinSizeY / 2.f - fradius) Ppos.y = 3.f*WinSizeY / 2.f - fradius;

	//	캠 컨디션 체크
	if (!(Ppos.x <= 0 || Ppos.x >= WinSizeX)) {
		_Camera->x = WinSizeX / 2.f - Ppos.x;
	}
	if (!(Ppos.y <= 0 || Ppos.y >= WinSizeY)) {
		_Camera->y = WinSizeY / 2.f - Ppos.y;
	}

	fangle = GetAngle(Ppos.x + _Camera->x, Ppos.y + _Camera->y, AppMouse.x, AppMouse.y) + PI / 2.0f;	//	이건 고정
																											//	실제 정면좌표 계산
	front =
	{ Ppos.x + (img->GetFrameHeight()*sinf(fangle) / 2.f),
		Ppos.y - (img->GetFrameHeight()*cosf(fangle) / 2.f) };

	//	Render좌표 초기화
	p2Render.x = Ppos.x + _Camera->x;
	p2Render.y = Ppos.y + _Camera->y;

	circle = MakeCircle(
		p2Render.x,
		p2Render.y,
		fradius);
}

void CharacterClass::DecreaseCoolTime(void)
{
	for (int i = 0; i < 5; ++i) {
		if (CoolTime[i] > 0) CoolTime[i] -= _Timer->GetElapsedTime(); // 1프레임당 시간 = Update() 한번 할때마다 시간 60FPS 1/60초
	}
}
