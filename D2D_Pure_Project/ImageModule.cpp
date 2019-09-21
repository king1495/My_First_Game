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

	//	WIC�� ����ϱ� ���� Factory ��ü ����
	CoInitialize(nullptr);
	HRESULT hr = CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER,
		IID_PPV_ARGS(&ImageInfo->pWicFactory));
	Assert(hr == S_OK);

	//	�̹����� �о�´�
	hr = ImageInfo->pWicFactory->CreateDecoderFromFilename(
		this->FileName.c_str(),
		nullptr,
		GENERIC_READ,
		WICDecodeMetadataCacheOnDemand,
		&(ImageInfo->pWicDecoder));

	if (FAILED(hr)) {
		TCHAR ErrorStr[256];
		_stprintf_s(ErrorStr, L"�̹��� ������ �߸��Ǿ����ϴ�\n Error Image:%s", this->FileName.c_str());
		MessageBox(AppDesc._hWnd, ErrorStr, nullptr, MB_OK);
		Release();
		return E_FAIL;
	}

	Assert(hr == S_OK);

	//	ù ��° �������� ����� �� �ִ� ��ü ����
	hr = ImageInfo->pWicDecoder->GetFrame(0, &ImageInfo->pWicFrameDecoder);
	Assert(hr == S_OK);

	//	Factory ��ü�� ����Ͽ� �̹��� ��ȯ ��ü�� ����
	hr = ImageInfo->pWicFactory->CreateFormatConverter(&ImageInfo->pWicConverter);
	Assert(hr == S_OK);

	//	�ý����� ��� �����ϴ� ��Ʈ�� �������� ��ȯ
	hr = ImageInfo->pWicConverter->Initialize(
		ImageInfo->pWicFrameDecoder,
		GUID_WICPixelFormat32bppPRGBA,
		WICBitmapDitherTypeNone,
		nullptr,
		0.0f,
		WICBitmapPaletteTypeCustom
	);

	//	��ȯ�� �̹��������� D2D�� ����� ��Ʈ�� ����
	hr = _RenderTarget->CreateBitmapFromWicBitmap(
		ImageInfo->pWicConverter,
		nullptr,
		&ImageInfo->pBitmap
	);

	//	�̹����� �������� �������� �ʾ��� ���
	if (ImageInfo->pBitmap == nullptr) {
		Release();
		return E_FAIL;
	}

	//	�̹��� ���� ������� ����ϰ� ���� ���
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

	//	WIC�� ����ϱ� ���� Factory ��ü ����
	CoInitialize(nullptr);
	HRESULT hr = CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER,
		IID_PPV_ARGS(&ImageInfo->pWicFactory));
	Assert(hr == S_OK);

	//	�̹����� �о�´�
	hr = ImageInfo->pWicFactory->CreateDecoderFromFilename(
		this->FileName.c_str(),
		nullptr,
		GENERIC_READ,
		WICDecodeMetadataCacheOnDemand,
		&(ImageInfo->pWicDecoder));

	if (FAILED(hr)) {
		TCHAR ErrorStr[256];
		_stprintf_s(ErrorStr, L"�̹��� ������ �߸��Ǿ����ϴ�\n Error Image:%s", this->FileName.c_str());
		MessageBox(AppDesc._hWnd, ErrorStr, nullptr, MB_OK);
		Release();
		return E_FAIL;
	}

	Assert(hr == S_OK);

	//	ù ��° �������� ����� �� �ִ� ��ü ����
	hr = ImageInfo->pWicDecoder->GetFrame(0, &ImageInfo->pWicFrameDecoder);
	Assert(hr == S_OK);

	//	Factory ��ü�� ����Ͽ� �̹��� ��ȯ ��ü�� ����
	hr = ImageInfo->pWicFactory->CreateFormatConverter(&ImageInfo->pWicConverter);
	Assert(hr == S_OK);

	//	�ý����� ��� �����ϴ� ��Ʈ�� �������� ��ȯ
	hr = ImageInfo->pWicConverter->Initialize(
		ImageInfo->pWicFrameDecoder,
		GUID_WICPixelFormat32bppPRGBA,
		WICBitmapDitherTypeNone,
		nullptr,
		0.0f,
		WICBitmapPaletteTypeCustom
	);

	//	��ȯ�� �̹��������� D2D�� ����� ��Ʈ�� ����
	hr = _RenderTarget->CreateBitmapFromWicBitmap(
		ImageInfo->pWicConverter,
		nullptr,
		&ImageInfo->pBitmap
	);

	//	�̹����� �������� �������� �ʾ��� ���
	if (ImageInfo->pBitmap == nullptr) {
		Release();
		return E_FAIL;
	}

	//	�̹��� ���� ������� ����ϰ� ���� ���
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

	//	�ѷ��� �̹��� ��ġ
	D2D1_RECT_F dxLocation = RectF(0.0f, 0.0f,
		ImageInfo->ImageSize.width,
		ImageInfo->ImageSize.height);

	////	���� �̹��� ������
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

	//	�ѷ��� �̹��� ��ġ
	D2D1_RECT_F dxLocation = RectF(
		x, y,
		x + ImageInfo->ImageSize.width,
		y + ImageInfo->ImageSize.height);

	//	���� �̹��� ������
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

	//	�ѷ��� �̹��� ��ġ
	D2D1_RECT_F dxLocation = RectF(
		x - ImageInfo->ImageSize.width / 2.f,
		y - ImageInfo->ImageSize.height / 2.f,
		x + ImageInfo->ImageSize.width / 2.f,
		y + ImageInfo->ImageSize.height / 2.f);

	//	���� �̹��� ������
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

	//	�ѷ��� �̹��� ��ġ
	D2D1_RECT_F dxLocation = RectF(x, y,
		x + width,
		y + height);

	//	���� �̹��� ������
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

	//	�ѷ��� �̹��� ��ġ
	D2D1_RECT_F dxLocation = RectF(
		x - width / 2.f,
		y - height / 2.f,
		x + width / 2.f,
		y + height / 2.f);

	//	���� �̹��� ������
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

	//	�ѷ��� �̹��� ��ġ
	D2D1_RECT_F dxLocation = RectF(
		x,
		y,
		x + ImageInfo->FrameImageSize.width,
		y + ImageInfo->FrameImageSize.height);

	////	���� �̹��� ������
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

	//	�ѷ��� �̹��� ��ġ
	D2D1_RECT_F dxLocation = RectF(
		x - ImageInfo->FrameImageSize.width / 2.f,
		y - ImageInfo->FrameImageSize.height / 2.f,
		x + ImageInfo->FrameImageSize.width / 2.f,
		y + ImageInfo->FrameImageSize.height / 2.f);

	////	���� �̹��� ������
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
