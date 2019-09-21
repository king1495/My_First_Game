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
	
	bool isKeyDown(int KeyCode);	//	Ű ��������
	bool StayKeyDown(int KeyCode);	//	Ű ������������
	bool isKeyUp(int KeyCode);		//	Ű ������
	bool ToggleKeyDown(int KeyCode);//	Ű ���
};

//#define _KeyCode KeyModule::GetInstance()