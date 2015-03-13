#pragma once
#include "Preprocess.hpp"
#include "Event.hpp"

_L_BEGIN
class _L_ ElapsedEventArgs : public EventArgs
{
public:
	chrono::steady_clock::time_point Trigger;
	void *UserData = nullptr;
	
	ElapsedEventArgs(chrono::steady_clock::time_point Trigger, void *UserData);
	~ElapsedEventArgs();
};

class _L_ Timer
{
public:
	Event<ElapsedEventArgs> Elapsed;
	enum class TimerExecuteMode
	{
		Once,
		Loop
	};
	Timer();
	Timer(void *userData);
	Timer(void *userData, unsigned long interval, TimerExecuteMode mode);
	bool IsEnabled();
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
	TimerExecuteMode mode = TimerExecuteMode::Loop;

	void Elapse();
};
_L_END