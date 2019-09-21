#pragma once

class ImageModule
{
public:
	ImageModule();
	~ImageModule();

	typedef struct IMAGE_INFO {
		IMAGE_INFO()
			:pWicFactory(nullptr),
			pWicConverter(nullptr),
			pWicDecoder(nullptr),
			pWicFrameDecoder(nullptr),
			pBitmap(nullptr),
			ImageSize(D2D1_SIZE_F()),
			BufferSize(1.0f),
			FrameImageSize(D2D1_SIZE_F()),
			MaxFrameX(1),
			MaxFrameY(1),
			frameXNum(0.0f),
			frameYNum(0.0f)
		{};

		IWICImagingFactory*		pWicFactory;
		IWICFormatConverter*	pWicConverter;
		IWICBitmapDecoder*		pWicDecoder;
		IWICBitmapFrameDecode*	pWicFrameDecoder;
		ID2D1Bitmap*			pBitmap;

		D2D1_SIZE_F				ImageSize;
		float BufferSize;

		D2D1_SIZE_F FrameImageSize;
		int MaxFrameX, MaxFrameY;

		float frameXNum, frameYNum;

	}*LPIMAGE_INFO;

private:
	LPIMAGE_INFO ImageInfo;
	wstring FileName;

public:
	void Release(void);

public:		//	CreateImage
	HRESULT CreateImage(string FileName, float width = 0.0f, float height = 0.0f);
	HRESULT CreateFrameImage(string FileName, int MaxFrameX, int MaxFrameY, float width = 0.0f, float height = 0.0f);

public:		//	Render
	void Render(float opacity = 1.0f);

	void Render(float x, float y, float opacity = 1.0f, bool isReverse = false, float degree = 0.f, float ScaleX = 1.0f, float ScaleY = 1.0f);
	void RenderCenter(float x, float y, float opacity = 1.0f, bool isReverse = false, float degree = 0.f, float ScaleX = 1.0f, float ScaleY = 1.0f);

	void CropRender(float x, float y, float opacity = 1.0f, float degree = 0.f, D2D_POINT_2F cX = { 0,0 }, D2D_POINT_2F cY = { 0,0 });
	void CropRenderCenter(float x, float y, float opacity = 1.0f, float degree = 0.f, D2D_POINT_2F cX = { 0,0 }, D2D_POINT_2F cY = { 0,0 });

	void FrameRender(float x, float y, int CFx = 0.f, int CFy = 0.f, float opacity = 1.0f, bool isReverse = false, float degree = 0.0f, float ScaleX = 1.f, float ScaleY = 1.f);
	void FrameRenderCenter(float x, float y, int CFx = 0.f, int CFy = 0.f, float opacity = 1.0f, bool isReverse = false, float degree = 0.0f, float ScaleX = 1.f, float ScaleY = 1.f);

public:		//	Get ImageInfo
	inline float GetWidth() { return ImageInfo->ImageSize.width; }
	inline float GetHeight() { return ImageInfo->ImageSize.height; }

	inline float GetFrameWidth() { return ImageInfo->FrameImageSize.width; }
	inline float GetFrameHeight() { return ImageInfo->FrameImageSize.height; }

	inline int GetMaxFrameX() { return ImageInfo->MaxFrameX; }
	inline int GetMaxFrameY() { return ImageInfo->MaxFrameY; }

	inline D2D_RECT_F GetRect(float x, float y) {
		return RectF(x, y, x + ImageInfo->ImageSize.width, y + ImageInfo->ImageSize.height);
	}

	inline D2D_RECT_F GetRectCenter(float x, float y) {
		return RectF(x - ImageInfo->ImageSize.width / 2.f, y - ImageInfo->ImageSize.height / 2.f, x + ImageInfo->ImageSize.width / 2.f, y + ImageInfo->ImageSize.height / 2.f);
	}

	inline D2D_RECT_F GetFrameRect(float x, float y) {
		return RectF(x, y, x + ImageInfo->FrameImageSize.width, y + ImageInfo->FrameImageSize.height);
	}

	inline D2D_RECT_F GetFrameRectCenter(float x, float y) {
		return RectF(x - ImageInfo->FrameImageSize.width / 2.f, y - ImageInfo->FrameImageSize.height / 2.f, x + ImageInfo->FrameImageSize.width / 2.f, y + ImageInfo->FrameImageSize.height / 2.f);
	}
};

