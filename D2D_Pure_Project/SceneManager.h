#pragma once
#include "Singletonbase.h"
#include "cApplication.h"
#include <map>

class cApplication;
class SceneManager : public SingletonBase<SceneManager>
{
private:
	typedef map<string, cApplication*> _mScene;
	typedef map<string, cApplication*>::iterator _mIter;

	static cApplication* CurrentScene;
	//static cApplication* ? ;

	_mScene mScene;

	DWORD loadingThreadID;	//	호오오오옥시 배울 때 쓰일 Thread

public:
	SceneManager();
	~SceneManager();

	void Update(void);
	void Render(void);

	cApplication* CreateScene(string SceneName, cApplication* _Scene);
	HRESULT ChangeScene(string SceneName);
};

