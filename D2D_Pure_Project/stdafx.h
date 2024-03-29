#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <Windows.h>


// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <time.h>
#include <math.h>
#include <string>
#include <time.h>
using namespace std;

//	Direct2D headerFile
#pragma comment(lib, "d2d1.lib")
#include <d2d1.h>
#include <d2d1helper.h>
using namespace D2D1;

//#pragma comment(lib, "WindowCodecs.lib")
#include <wincodec.h>

//	png encoder
#pragma comment(lib, "dwrite.lib")
#include <dwrite.h>

#include "define.h"

#include "DX2DApp.h"

// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
#include "modules.h"
#include "Utility.h"
#include "RandomMacro.h"
#include "CollisionHelper.h"
//#include "SceneHeader.h"
using namespace nMakeShapes;
using namespace nString;
using namespace nRandom;
using namespace nCollision;

struct App_Desc {
	HINSTANCE _hInstance;
	HWND _hWnd;
	float width, height;
};

//	전역으로 선언, 프로그램 전체에서 유효함(프로그램 전체에서 전역변수처럼...)
//	stack, 정적 데이터 영역으로 들어감
//	막쓰면 나중에 코드관리가 ㅈ됨
extern App_Desc AppDesc;
extern D2D_POINT_2F AppMouse;
extern D2D_POINT_2F Ppos;

#define ApplicationName TEXT("D2D Example")
#define WinSizeX AppDesc.width
#define WinSizeY AppDesc.height