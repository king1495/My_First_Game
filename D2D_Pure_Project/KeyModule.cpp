#include "stdafx.h"
#include "KeyModule.h"


KeyModule::KeyModule()
	:PrevKey(0)
{
	ZeroMemory(bKeyDown, sizeof bKeyDown);
}


KeyModule::~KeyModule()
{
}

bool KeyModule::isKeyDown(int KeyCode)
{
	if (GetAsyncKeyState(KeyCode) & 0x8000) {
		if (!bKeyDown[KeyCode]) {
			bKeyDown[KeyCode] = 0x01;
			return true;
		}
	}
	else bKeyDown[KeyCode] = 0x00;

	return false;
}

bool KeyModule::StayKeyDown(int KeyCode)
{
	if (GetAsyncKeyState(KeyCode) & 0x8000) {
		PrevKey = KeyCode;
		return true;
	}
	return false;
}

bool KeyModule::isKeyUp(int KeyCode)
{
	if (!StayKeyDown(KeyCode)) {
		if (PrevKey == KeyCode) {
			PrevKey = 0;
			return true;
		}
	}
	return false;
}

bool KeyModule::ToggleKeyDown(int KeyCode)
{
	if (GetKeyState(KeyCode) & 0x0001) return true;
	return false;
}
