#pragma once
#include "Singletonbase.h"

class KeyModule : public SingletonBase<KeyModule>
{
private:
	byte bKeyDown[256];
	byte PrevKey;

public:
	KeyModule();
	~KeyModule();
	
	bool isKeyDown(int KeyCode);	//	키 눌렸을때
	bool StayKeyDown(int KeyCode);	//	키 누르고있을때
	bool isKeyUp(int KeyCode);		//	키 땠을때
	bool ToggleKeyDown(int KeyCode);//	키 토글
};

//#define _KeyCode KeyModule::GetInstance()