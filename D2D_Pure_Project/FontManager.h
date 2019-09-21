#pragma once
#include "Singletonbase.h"
#include <map>

class FontManager : public SingletonBase<FontManager>
{
	typedef map<std::string, IDWriteTextFormat*> _mFont;
	typedef _mFont::iterator mIter;

	_mFont mFont;

public:
	FontManager();
	~FontManager();

	void Create(std::string NickName,
		std::string FontName, 
		float FontSize = 14.f, 
		DWRITE_TEXT_ALIGNMENT Alignment = DWRITE_TEXT_ALIGNMENT_CENTER,
		DWRITE_FONT_WEIGHT Weight = DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE Style = DWRITE_FONT_STYLE_NORMAL);

	void TextRender(std::string Text, D2D_RECT_F rc, std::string NickName = "DEFAULT_LEFT");
	void TextRender(wstring Text, D2D_RECT_F rc, std::string NickName = "DEFAULT_LEFT");
};

