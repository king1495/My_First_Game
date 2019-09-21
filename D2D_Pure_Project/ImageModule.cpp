#include "stdafx.h"
#include "ImageModule.h"


ImageModule::ImageModule()
	:ImageInfo(nullptr)
{
}


ImageModule::~ImageModule()
{
}

void ImageModule::Release(void)
{
	SafeRelease(ImageInfo->pWicConverter);
	SafeRelease(ImageInfo->pWicDecoder);
	SafeRelease(ImageInfo->pWicFrameDecoder);
	SafeRelease(ImageInfo->pWicFactory);
	SafeRelease(ImageInfo->pBitmap);

	SafeDelete(ImageInfo);
}

HRESULT ImageModule::CreateImage(string FileName, float width, float height)
{
	if (FileName == "") return E_FAIL;
	this->FileName = StringToWstring(FileName);

	if (ImageInfo != nullptr) Release();
	ImageInfo = new IMAGE_INFO();

	//	WIC를 사용하기 위한 Factory 객체 생성
	CoInitialize(nullptr);
	HRESULT hr = CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER,
		IID_PPV_ARGS(&ImageInfo->pWicFactory));
	Assert(hr == S_OK);

	//	이미지를 읽어온다
	hr = ImageInfo->pWicFactory->CreateDecoderFromFilename(
		this->FileName.c_str(),
		nullptr,
		GENERIC_READ,
		WICDecodeMetadataCacheOnDemand,
		&(ImageInfo->pWicDecoder));

	if (FAILED(hr)) {
		TCHAR ErrorStr[256];
		_stprintf_s(ErrorStr, L"이미지 파일이 잘못되었습니다\n Error Image:%s", this->FileName.c_str());
		MessageBox(AppDesc._hWnd, ErrorStr, nullptr, MB_OK);
		Release();
		return E_FAIL;
	}

	Assert(hr == S_OK);

	//	첫 번째 프레임을 사용할 수 있는 객체 구성
	hr = ImageInfo->pWicDecoder->GetFrame(0, &ImageInfo->pWicFrameDecoder);
	Assert(hr == S_OK);

	//	Factory 객체를 사용하여 이미지 변환 객체를 생성
	hr = ImageInfo->pWicFactory->CreateFormatConverter(&ImageInfo->pWicConverter);
	Assert(hr == S_OK);

	//	시스템이 사용 가능하느 비트맵 형식으로 변환
	hr = ImageInfo->pWicConverter->Initialize(
		ImageInfo->pWicFrameDecoder,
		GUID_WICPixelFormat32bppPRGBA,
		WICBitmapDitherTypeNone,
		nullptr,
		0.0f,
		WICBitmapPaletteTypeCustom
	);

	//	변환된 이미지형식을 D2D에 사용할 비트맵 생성
	hr = _RenderTarget->CreateBitmapFromWicBitmap(
		ImageInfo->pWicConverter,
		nullptr,
		&ImageInfo->pBitmap
	);

	//	이미지가 정상적을 생성되지 않았을 경우
	if (ImageInfo->pBitmap == nullptr) {
		Release();
		return E_FAIL;
	}

	//	이미지 원본 사이즈로 사용하고 싶은 경우
	if (width == 0.0f || height == 0.0f) {
		ImageInfo->ImageSize = ImageInfo->pBitmap->GetSize();
	}
	else {
		ImageInfo->ImageSize.width = width;
		ImageInfo->ImageSize.height = height;
	}
	ImageInfo->FrameImageSize = ImageInfo->ImageSize;

	return S_OK;
}

HRESULT ImageModule::CreateFrameImage(string FileName, int MaxFrameX, int MaxFrameY, float width, float height)
{
	if (FileName == "") return E_FAIL;
	this->FileName = StringToWstring(FileName);

	if (ImageInfo != nullptr) Release();
	ImageInfo = new IMAGE_INFO();

	//	WIC를 사용하기 위한 Factory 객체 생성
	CoInitialize(nullptr);
	HRESULT hr = CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER,
		IID_PPV_ARGS(&ImageInfo->pWicFactory));
	Assert(hr == S_OK);

	//	이미지를 읽어온다
	hr = ImageInfo->pWicFactory->CreateDecoderFromFilename(
		this->FileName.c_str(),
		nullptr,
		GENERIC_READ,
		WICDecodeMetadataCacheOnDemand,
		&(ImageInfo->pWicDecoder));

	if (FAILED(hr)) {
		TCHAR ErrorStr[256];
		_stprintf_s(ErrorStr, L"이미지 파일이 잘못되었습니다\n Error Image:%s", this->FileName.c_str());
		MessageBox(AppDesc._hWnd, ErrorStr, nullptr, MB_OK);
		Release();
		return E_FAIL;
	}

	Assert(hr == S_OK);

	//	첫 번째 프레임을 사용할 수 있는 객체 구성
	hr = ImageInfo->pWicDecoder->GetFrame(0, &ImageInfo->pWicFrameDecoder);
	Assert(hr == S_OK);

	//	Factory 객체를 사용하여 이미지 변환 객체를 생성
	hr = ImageInfo->pWicFactory->CreateFormatConverter(&ImageInfo->pWicConverter);
	Assert(hr == S_OK);

	//	시스템이 사용 가능하느 비트맵 형식으로 변환
	hr = ImageInfo->pWicConverter->Initialize(
		ImageInfo->pWicFrameDecoder,
		GUID_WICPixelFormat32bppPRGBA,
		WICBitmapDitherTypeNone,
		nullptr,
		0.0f,
		WICBitmapPaletteTypeCustom
	);

	//	변환된 이미지형식을 D2D에 사용할 비트맵 생성
	hr = _RenderTarget->CreateBitmapFromWicBitmap(
		ImageInfo->pWicConverter,
		nullptr,
		&ImageInfo->pBitmap
	);

	//	이미지가 정상적을 생성되지 않았을 경우
	if (ImageInfo->pBitmap == nullptr) {
		Release();
		return E_FAIL;
	}

	//	이미지 원본 사이즈로 사용하고 싶은 경우
	if (width == 0.0f || height == 0.0f) {
		ImageInfo->ImageSize = ImageInfo->pBitmap->GetSize();
	}
	else {
		ImageInfo->ImageSize.width = width;
		ImageInfo->ImageSize.height = height;
	}

	ImageInfo->MaxFrameX = MaxFrameX;
	ImageInfo->MaxFrameY = MaxFrameY;

	ImageInfo->FrameImageSize.width = ImageInfo->ImageSize.width / MaxFrameX;
	ImageInfo->FrameImageSize.height = ImageInfo->ImageSize.height / MaxFrameY;

	return S_OK;
}

void ImageModule::Render(float opacity)
{
	if (ImageInfo->pBitmap == nullptr) return;

	//	뿌려줄 이미지 위치
	D2D1_RECT_F dxLocation = RectF(0.0f, 0.0f,
		ImageInfo->ImageSize.width,
		ImageInfo->ImageSize.height);

	////	실제 이미지 사이즈
	D2D1_RECT_F dxSize = RectF(0.0f, 0.0f,
		ImageInfo->ImageSize.width,
		ImageInfo->ImageSize.height);

	_RenderTarget->DrawBitmap(ImageInfo->pBitmap,
		dxLocation,
		opacity,
		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		dxSize);
}

void ImageModule::Render(float x, float y, float opacity, bool isReverse, float degree, float ScaleX, float ScaleY)
{
	if (ImageInfo->pBitmap == nullptr) return;

	D2D_POINT_2F dxPoint = {
		x + ImageInfo->ImageSize.width / 2.f,
		y + ImageInfo->ImageSize.height / 2.f };

	Matrix3x2F dxMatrix = Matrix3x2F::Identity();
	if (degree != 0.f || ScaleX != 1.f || ScaleY != 1.f) {
		dxMatrix = Matrix3x2F::Rotation(degree, dxPoint) *
			Matrix3x2F::Scale(ScaleX, ScaleY, dxPoint);
	}

	if (isReverse) {
		dxMatrix = dxMatrix * Matrix3x2F::Scale(-1.0f, 1.0f, dxPoint);
	}

	if (!dxMatrix.IsIdentity()) {
		_RenderTarget->SetTransform(dxMatrix);
	}

	//	뿌려줄 이미지 위치
	D2D1_RECT_F dxLocation = RectF(
		x, y,
		x + ImageInfo->ImageSize.width,
		y + ImageInfo->ImageSize.height);

	//	실제 이미지 사이즈
	D2D1_RECT_F dxSize = RectF(0.0f, 0.0f,
		ImageInfo->ImageSize.width,
		ImageInfo->ImageSize.height);

	_RenderTarget->DrawBitmap(ImageInfo->pBitmap,
		dxLocation,
		opacity,
		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		dxSize);

	if (!dxMatrix.IsIdentity()) {
		_RenderTarget->SetTransform(Matrix3x2F::Identity());
	}
}

void ImageModule::RenderCenter(float x, float y, float opacity, bool isReverse, float degree, float ScaleX, float ScaleY)
{
	if (ImageInfo->pBitmap == nullptr) return;

	D2D_POINT_2F dxPoint = { x, y };

	Matrix3x2F dxMatrix = Matrix3x2F::Identity();
	if (degree != 0.f || ScaleX != 1.f || ScaleY != 1.f) {
		dxMatrix = Matrix3x2F::Rotation(degree, dxPoint) *
			Matrix3x2F::Scale(ScaleX, ScaleY, dxPoint);
	}

	if (isReverse) {
		dxMatrix = dxMatrix * Matrix3x2F::Scale(-1.0f, 1.0f, dxPoint);
	}

	if (!dxMatrix.IsIdentity()) {
		_RenderTarget->SetTransform(dxMatrix);
	}

	//	뿌려줄 이미지 위치
	D2D1_RECT_F dxLocation = RectF(
		x - ImageInfo->ImageSize.width / 2.f,
		y - ImageInfo->ImageSize.height / 2.f,
		x + ImageInfo->ImageSize.width / 2.f,
		y + ImageInfo->ImageSize.height / 2.f);

	//	실제 이미지 사이즈
	D2D1_RECT_F dxSize = RectF(0.0f, 0.0f,
		ImageInfo->ImageSize.width,
		ImageInfo->ImageSize.height);

	_RenderTarget->DrawBitmap(ImageInfo->pBitmap,
		dxLocation,
		opacity,
		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		dxSize);

	if (!dxMatrix.IsIdentity()) {
		_RenderTarget->SetTransform(Matrix3x2F::Identity());
	}
}

void ImageModule::CropRender(float x, float y, float opacity, float degree, D2D_POINT_2F cX, D2D_POINT_2F cY)
{
	if (ImageInfo->pBitmap == nullptr) return;

	float width = cX.y - cX.x;
	float height = cY.y - cY.x;

	D2D_POINT_2F dxPoint = {
		x + ImageInfo->ImageSize.width / 2.f,
		y + ImageInfo->ImageSize.height / 2.f };

	Matrix3x2F dxMatrix = Matrix3x2F::Identity();
	if (degree != 0.f) {
		dxMatrix = Matrix3x2F::Rotation(degree, dxPoint);
	}

	if (!dxMatrix.IsIdentity()) {
		_RenderTarget->SetTransform(dxMatrix);
	}

	//	뿌려줄 이미지 위치
	D2D1_RECT_F dxLocation = RectF(x, y,
		x + width,
		y + height);

	//	실제 이미지 사이즈
	D2D1_RECT_F dxSize = RectF(
		cX.x, cY.x,
		cX.y, cY.y);

	_RenderTarget->DrawBitmap(ImageInfo->pBitmap,
		dxLocation,
		opacity,
		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		dxSize);

	if (!dxMatrix.IsIdentity()) {
		_RenderTarget->SetTransform(Matrix3x2F::Identity());
	}
}

void ImageModule::CropRenderCenter(float x, float y, float opacity, float degree, D2D_POINT_2F cX, D2D_POINT_2F cY)
{
	if (ImageInfo->pBitmap == nullptr) return;

	float width = cX.y - cX.x;
	float height = cY.y - cY.x;

	D2D_POINT_2F dxPoint = { x,	y };

	Matrix3x2F dxMatrix = Matrix3x2F::Identity();
	if (degree != 0.f) {
		dxMatrix = Matrix3x2F::Rotation(degree, dxPoint);
	}

	if (!dxMatrix.IsIdentity()) {
		_RenderTarget->SetTransform(dxMatrix);
	}

	//	뿌려줄 이미지 위치
	D2D1_RECT_F dxLocation = RectF(
		x - width / 2.f,
		y - height / 2.f,
		x + width / 2.f,
		y + height / 2.f);

	//	실제 이미지 사이즈
	D2D1_RECT_F dxSize = RectF(
		cX.x, cY.x,
		cX.y, cY.y);

	_RenderTarget->DrawBitmap(ImageInfo->pBitmap,
		dxLocation,
		opacity,
		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		dxSize);

	if (!dxMatrix.IsIdentity()) {
		_RenderTarget->SetTransform(Matrix3x2F::Identity());
	}
}

void ImageModule::FrameRender(float x, float y, int CFx, int CFy, float opacity, bool isReverse, float degree, float ScaleX, float ScaleY)
{
	if (ImageInfo->pBitmap == nullptr) return;

	D2D_POINT_2F dxPoint = {
		x + ImageInfo->FrameImageSize.width / 2.f,
		y + ImageInfo->FrameImageSize.height / 2.f };

	Matrix3x2F dxMatrix = Matrix3x2F::Identity();
	if (degree != 0.f || ScaleX != 1.f || ScaleY != 1.f) {
		dxMatrix = Matrix3x2F::Rotation(degree, dxPoint) *
			Matrix3x2F::Scale(ScaleX, ScaleY, dxPoint);
	}

	if (isReverse) {
		dxMatrix = dxMatrix * Matrix3x2F::Scale(-1.0f, 1.0f, dxPoint);
	}

	if (!dxMatrix.IsIdentity()) {
		_RenderTarget->SetTransform(dxMatrix);
	}

	//	뿌려줄 이미지 위치
	D2D1_RECT_F dxLocation = RectF(
		x,
		y,
		x + ImageInfo->FrameImageSize.width,
		y + ImageInfo->FrameImageSize.height);

	////	실제 이미지 사이즈
	D2D1_RECT_F dxSize = RectF(
		CFx*ImageInfo->FrameImageSize.width,
		CFy*ImageInfo->FrameImageSize.height,
		(CFx + 1)*ImageInfo->FrameImageSize.width,
		(CFy + 1)*ImageInfo->FrameImageSize.height);

	_RenderTarget->DrawBitmap(ImageInfo->pBitmap,
		dxLocation,
		opacity,
		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		dxSize);

	if (!dxMatrix.IsIdentity()) {
		_RenderTarget->SetTransform(Matrix3x2F::Identity());
	}
}

void ImageModule::FrameRenderCenter(float x, float y, int CFx, int CFy, float opacity, bool isReverse, float degree, float ScaleX, float ScaleY)
{
	if (ImageInfo->pBitmap == nullptr) return;

	D2D_POINT_2F dxPoint = { x, y };

	Matrix3x2F dxMatrix = Matrix3x2F::Identity();
	if (degree != 0.f || ScaleX != 1.f || ScaleY != 1.f) {
		dxMatrix = Matrix3x2F::Rotation(degree, dxPoint) *
			Matrix3x2F::Scale(ScaleX, ScaleY, dxPoint);
	}

	if (isReverse) {
		dxMatrix = dxMatrix * Matrix3x2F::Scale(-1.0f, 1.0f, dxPoint);
	}

	if (!dxMatrix.IsIdentity()) {
		_RenderTarget->SetTransform(dxMatrix);
	}

	//	뿌려줄 이미지 위치
	D2D1_RECT_F dxLocation = RectF(
		x - ImageInfo->FrameImageSize.width / 2.f,
		y - ImageInfo->FrameImageSize.height / 2.f,
		x + ImageInfo->FrameImageSize.width / 2.f,
		y + ImageInfo->FrameImageSize.height / 2.f);

	////	실제 이미지 사이즈
	D2D1_RECT_F dxSize = RectF(
		CFx*ImageInfo->FrameImageSize.width,
		CFy*ImageInfo->FrameImageSize.height,
		(CFx + 1)*ImageInfo->FrameImageSize.width,
		(CFy + 1)*ImageInfo->FrameImageSize.height);

	_RenderTarget->DrawBitmap(ImageInfo->pBitmap,
		dxLocation,
		opacity,
		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		dxSize);

	if (!dxMatrix.IsIdentity()) {
		_RenderTarget->SetTransform(Matrix3x2F::Identity());
	}
}
