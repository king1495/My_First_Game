#include "stdafx.h"
#include "TimerModule.h"

#pragma comment (lib, "winmm.lib")
#include <mmsystem.h>

TimerModule::TimerModule()
{
	//	�ý��� Ŭ��(���ļ�)�� �����ϴ� �κ�
	if (QueryPerformanceFrequency((LARGE_INTEGER*)&_PreriodTime)) {
		isHardware = true;
		//	���α׷��� ó�� ���۵Ǵ� �κ��� ����
		QueryPerformanceCounter((LARGE_INTEGER*)&_LastTime);
		TimeScale = 1.0f / _PreriodTime;	//	���ļ��� ������ �ֱ�(t)
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
	//	���� �ð��� ���
	if (isHardware) QueryPerformanceCounter((LARGE_INTEGER*)&_CurTime);
	else _CurTime = timeGetTime();

	//	���ݽð��� �����ð��� �� �� �ֱ⸦ ���� : �� ��� ����ߴ���
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

	//	�����ڵ� ������� ���α׷��� ���鶧�� wsprintf �� ���ϱ� �ѵ�
	//	float���� �������� ����.... �׷��� _strprintf_s
	_stprintf_s(timsStr, TimeTextString, WorldTime, TimeElapsed, FrameRate);
	_FontManager->TextRender(timsStr, RectF(0.f, 0.f, 200.f, 100.f));
#else
	static TCHAR TimeTextString[] = { L"FPS : %d" };

	_stprintf_s(timsStr, TimeTextString, FrameRate);
	_FontManager->TextRender(timsStr, RectF(0.f, 0.f, 200.f, 100.f));

#endif
}
