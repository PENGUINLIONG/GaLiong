#pragma once
#include "Preprocess.h"

_L_BEGIN
class Timer;
typedef void(*TimerCallbackFunction)(Timer &sender, void *userData);

class _L_ Timer
{
public:
	enum class TimerExecuteMode
	{
		Once,
		Loop
	};
	Timer(void *userData, unsigned long interval);
	Timer(void *userData, unsigned long interval, TimerExecuteMode mode);
	bool IsEnabled();
	Timer &operator+=(const TimerCallbackFunction &callback);
	Timer &operator-=(const TimerCallbackFunction &callback);
	void AppendCallback(const TimerCallbackFunction &callback);
	void RemoveCallback(const TimerCallbackFunction &callback);
	void Start();
	void Stop();
	~Timer();
private:
	void *userData = nullptr;
	bool available = false;
	bool enabled = false;
	bool done = false;
	//atomic<bool> ;
	chrono::steady_clock::time_point startTime;
	chrono::milliseconds interval;
	list<TimerCallbackFunction> callbacks;
	future<void> asyncAccess;
	TimerExecuteMode mode = TimerExecuteMode::Loop;

	void Elapsed();
	void DoElapsed();
};
_L_END
