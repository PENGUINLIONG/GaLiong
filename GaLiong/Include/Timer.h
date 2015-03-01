#pragma once
#include "Preprocess.h"

_L_BEGIN
class Timer;
//typedef void(*TimerCallbackFunction)(Timer &sender, void *userData);
typedef function<void(Timer, void *)> TimerCallbackFunction;

class _L_ Timer
{
public:
	enum class TimerExecuteMode
	{
		Once,
		Loop
	};
	Timer();
	Timer(void *userData, unsigned long interval);
	Timer(void *userData, unsigned long interval, TimerExecuteMode mode);
	bool IsEnabled();
	Timer &operator+=(const TimerCallbackFunction &callback);
	Timer &operator-=(const TimerCallbackFunction &callback);
	void Start();
	void Stop();
	void SetInterval(unsigned long interval);
	~Timer();
private:
	void *userData = nullptr;
	bool available = false;
	bool enabled = false;
	bool done = false;
	chrono::steady_clock::time_point startTime;
	chrono::milliseconds interval;
	list<TimerCallbackFunction> callbacks;
	TimerExecuteMode mode = TimerExecuteMode::Loop;

	event Elapsed();
};
_L_END