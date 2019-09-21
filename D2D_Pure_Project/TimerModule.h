#pragma once

//	이건 잘 쓸일 없으니까....
class TimerModule
{
	bool isHardware;

	float TimeScale;
	float TimeElapsed;

	__int64 _PreriodTime;
	__int64 _LastTime;
	__int64 _CurTime;

	unsigned long FrameRate;
	unsigned long FPSFrameCount;

	float FPSTimeElapsed;
	float WorldTime;

public:
	TimerModule();
	~TimerModule();

	void UpdateTime(float frameLock = 60.0f);
	void RenderTime(void);

	inline float GetElapsedTime(void) const { return TimeElapsed; }
	inline float GetTime(void) const { return WorldTime; }
	inline float GetFPSTime(void) { return (float)FrameRate; }

	static TimerModule* GetInstance() {
		static TimerModule Instance;
		return &Instance;
	}
};

