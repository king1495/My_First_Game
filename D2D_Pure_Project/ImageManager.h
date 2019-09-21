#pragma once
#include "ImageModule.h"
#include "Singletonbase.h"
#include <map>

class ImageManager : public SingletonBase<ImageManager>
{
	std::map<string, ImageModule*> mImage;
	typedef std::map<string, ImageModule*>::iterator miter;


public:
	ImageManager();
	~ImageManager();

	ImageModule* CreateImage(string NickName, string Filename, float width = 0.f, float height = 0.f);
	ImageModule* CreateFrameImage(string NickName, string Filename, int MaxFrameX, int MaxFrameY, float width = 0.f, float height = 0.f);
	ImageModule* FindImage(string NickName);
};

