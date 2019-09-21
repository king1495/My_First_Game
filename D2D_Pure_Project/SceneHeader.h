#pragma once
class Scene {

public:
	Scene() {};
	virtual ~Scene() {};

	virtual HRESULT Init(void) {};
	virtual void Release(void) {};
	virtual void Update(void) {};
	virtual void Render(void) {};
};