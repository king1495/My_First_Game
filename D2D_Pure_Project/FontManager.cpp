#include "stdafx.h"
#include "FontManager.h"

FontManager::FontManager()
{
	IDWriteTextFormat* pTemp = nullptr;

	_Device->pWriteFactory->CreateTextFormat(
		L"ÈÞ¸Õ°íµñ", nullptr,
		DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		14.0f, L"", &pTemp);

	pTemp->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);

	mFont.insert(make_pair("DEFAULT_CENTER", pTemp));

	pTemp = nullptr;

	_Device->pWriteFactory->CreateTextFormat(
		L"ÈÞ¸Õ°íµñ", nullptr,
		DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		14.0f, L"", &pTemp);

	pTemp->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_JUSTIFIED);

	mFont.insert(make_pair("DEFAULT_LEFT", pTemp));
}


FontManager::~FontManager()
{
	mIter iter = mFont.begin();
	for (iter; iter != mFont.end(); ++iter) {
		SafeRelease(iter->second);
	}
}

void FontManager::Create(std::string NickName, std::string FontName, float FontSize, DWRITE_TEXT_ALIGNMENT Alignment, DWRITE_FONT_WEIGHT Weight, DWRITE_FONT_STYLE Style)
{
	IDWriteTextFormat* pTemp = nullptr;

	if (FAILED(_Device->pWriteFactory->CreateTextFormat(
		StringToWstring(FontName).c_str(),
		nullptr,
		Weight,
		Style,
		DWRITE_FONT_STRETCH_NORMAL,
		FontSize, L"",
		&pTemp)))
	{
		MessageBox(AppDesc._hWnd, L"ÆùÆ®°¡ Á¸ÀçÇÏÁö ¾Ê½À´Ï´Ù.", nullptr, MB_OK);
	};

	pTemp->SetTextAlignment(Alignment);

	mFont.insert(make_pair(NickName, pTemp));
}

void FontManager::TextRender(std::string Text, D2D_RECT_F rc, std::string NickName)
{
	_RenderTarget->DrawTextW(
		StringToWstring(Text).c_str(),
		(UINT)Text.size(),
		mFont[NickName],
		rc,
		_Device->pDefaultBrush);
}

void FontManager::TextRender(wstring Text, D2D_RECT_F rc, std::string NickName)
{
	_RenderTarget->DrawTextW(
		Text.c_str(),
		(UINT)Text.size(),
		mFont[NickName],
		rc,
		_Device->pDefaultBrush);
}
