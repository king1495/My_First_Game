#include "stdafx.h"
#include "TimerModule.h"

#pragma comment (lib, "winmm.lib")
#include <mmsystem.h>

TimerModule::TimerModule()
{
	//	시스템 클럭(주파수)을 저장하는 부분
	if (QueryPerformanceFrequency((LARGE_INTEGER*)&_PreriodTime)) {
		isHardware = true;
		//	프로그램이 처음 시작되는 부분을 지정
		QueryPerformanceCounter((LARGE_INTEGER*)&_LastTime);
		TimeScale = 1.0f / _PreriodTime;	//	주파수의 역수는 주기(t)
	}
	else {
		isHardware = false;
		_LastTime = timeGetTime();
		TimeScale = 0.001f;
	}
}


TimerModule::~TimerModule()
{
}

void TimerModule::UpdateTime(float frameLock)
{
	//	지금 시간을 얻어
	if (isHardware) QueryPerformanceCounter((LARGE_INTEGER*)&_CurTime);
	else _CurTime = timeGetTime();

	//	지금시간과 이전시간을 뺀 후 주기를 곱해 : 총 몇번 출력했는지
	TimeElapsed = (_CurTime - _LastTime) * TimeScale;

	if (frameLock > 0.0f) {
		while (TimeElapsed < (1.0f / frameLock)) {
			if (isHardware) QueryPerformanceCounter((LARGE_INTEGER*)&_CurTime);
			else _CurTime = timeGetTime();

			TimeElapsed = (_CurTime - _LastTime) * TimeScale;
		}
	}

	_LastTime = _CurTime;
	FPSFrameCount++;
	FPSTimeElapsed += TimeElapsed;
	WorldTime += TimeElapsed;

	if (FPSTimeElapsed > 1.0f) {
		FrameRate = FPSFrameCount;
		FPSFrameCount = 0;
		FPSTimeElapsed = 0.0f;
	}
}

void TimerModule::RenderTime(void)
{
	WCHAR timsStr[256];

#if defined(DEBUG) || defined(_DEBUG)
	static TCHAR TimeTextString[] = { L"WorldTime : %.2f\nFrameCount : %f\nFPS : %d" };

	//	유니코드 기반으로 프로그램을 만들때는 wsprintf 가 편하긴 한데
	//	float형을 지원하지 않음.... 그래서 _strprintf_s
	_stprintf_s(timsStr, TimeTextString, WorldTime, TimeElapsed, FrameRate);
	_FontManager->TextRender(timsStr, RectF(0.f, 0.f, 200.f, 100.f));
#else
	static TCHAR TimeTextString[] = { L"FPS : %d" };

	_stprintf_s(timsStr, TimeTextString, FrameRate);
	_FontManager->TextRender(timsStr, RectF(0.f, 0.f, 200.f, 100.f));

#endif
}
