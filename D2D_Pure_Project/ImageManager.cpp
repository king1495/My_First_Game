#include "stdafx.h"
#include "ImageManager.h"



ImageManager::ImageManager()
{
}

ImageManager::~ImageManager()
{
	miter iter = mImage.begin();
	for (iter; iter != mImage.end(); ++iter) {
		iter->second->Release();
		SafeDelete(iter->second);
	}
	mImage.clear();
}

ImageModule * ImageManager::CreateImage(string NickName, string Filename, float width, float height)
{
	ImageModule* img;
	img = FindImage(NickName);
	if (img != nullptr) return img;
	img = new ImageModule;
	if (FAILED(img->CreateImage(Filename, width, height))) return nullptr;

	mImage.insert(make_pair(NickName, img));
	return img;
}

ImageModule * ImageManager::CreateFrameImage(string NickName, string Filename, int MaxFrameX, int MaxFrameY, float width, float height)
{
	ImageModule* img;
	img = FindImage(NickName);
	if (img != nullptr) return img;
	img = new ImageModule;
	if (FAILED(img->CreateFrameImage(Filename, MaxFrameX, MaxFrameY, width, height))) return nullptr;

	mImage.insert(make_pair(NickName, img));
	return img;
}

ImageModule * ImageManager::FindImage(string NickName)
{
	if (mImage.empty()) return nullptr;
	miter iter = mImage.begin();

	for (iter; iter != mImage.end(); ++iter) {
		if (iter->first == NickName) return iter->second;
	}

	return nullptr;
}
