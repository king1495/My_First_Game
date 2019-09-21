#include "stdafx.h"
#include "ItemClass.h"


ItemClass::ItemClass()
	:fradius(14.f), isActive(false), isType(isHeal), alpha(1.f), FrameTime(0)
{
	ImageName[0] = "Heal";
	ImageName[1] = "CoolTime";
	ImageName[2] = "Attack";

	center = D2D_POINT_2F();
	p2Render = center;
	img = _ImageManager->FindImage(ImageName[isType]);
}


ItemClass::~ItemClass()
{
}

HRESULT ItemClass::Init(tagItem _type, D2D_POINT_2F _pos)
{
	isType = _type;
	p2Render = _pos;

	img = _ImageManager->FindImage(ImageName[isType]);

	center.x = p2Render.x - _Camera->x;
	center.y = p2Render.y - _Camera->y;

	circle = MakeCircle(p2Render.x, p2Render.y, fradius);

	FrameTime = 0;

	isActive = true;

	return S_OK;
}

void ItemClass::Release(void)
{
}

void ItemClass::Update(void)
{
	p2Render.x = center.x + _Camera->x;
	p2Render.y = center.y + _Camera->y;

	circle = MakeCircle(p2Render.x, p2Render.y, fradius);

	FrameTime++;
	if (FrameTime == UINT_MAX) FrameTime = 0;
	if (FrameTime >= 300 && isActive) isActive = false;
}

void ItemClass::Render(void)
{
	if (!isActive || alpha <= 0) return;

	if (p2Render.x < 0 - img->GetWidth() ||
		p2Render.x > WinSizeX + img->GetWidth() ||
		p2Render.y < 0 - img->GetHeight() ||
		p2Render.y > WinSizeY + img->GetHeight()
		) return;

	img->RenderCenter(p2Render.x, p2Render.y, alpha);

	if (_KeyCode->ToggleKeyDown(VK_TAB)) {
		TCHAR status[256];
		_stprintf_s(status, L"x : %.2f, y : %.2f\nType : %d", center.x, center.y, isType);
		_FontManager->TextRender(status, MakeRect(p2Render.x - img->GetWidth() / 2.f, p2Render.y - img->GetWidth() / 2.f, 200.f, -40.f));
		_RenderTarget->DrawEllipse(circle, _Device->pDefaultBrush);
	}
}
