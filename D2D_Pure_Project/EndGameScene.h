#pragma once
class EndGameScene : public cApplication
{
	D2D_RECT_F BT_RESTART;
	D2D_RECT_F BT_EXIT;

public:
	EndGameScene();
	~EndGameScene();

	HRESULT Init(void) override;
	void Release(void) override;
	void Update(void) override;
	void Render(void) override;
};

