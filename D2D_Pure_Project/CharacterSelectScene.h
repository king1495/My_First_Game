#pragma once
class CharacterSelectScene : public cApplication
{
	vector<ImageModule*> pImages;
	vector<D2D_RECT_F> rect_button;
	bool isSelected[3];

	D2D_RECT_F BT_OK;

	Frame CurrentFrame;	
	UINT FrameTime;

	float imScale;

public:
	CharacterSelectScene();
	~CharacterSelectScene();

	HRESULT Init(void) override;
	void Release(void) override;
	void Update(void) override;
	void Render(void) override;
};

