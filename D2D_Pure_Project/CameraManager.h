#pragma once
#include "Singletonbase.h"

class CameraManager : public SingletonBase<CameraManager>
{
public:
	CameraManager();
	~CameraManager();

	float x, y;
};

