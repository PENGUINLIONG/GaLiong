#include "Timer.h"

_L_BEGIN
Timer::Timer()
{
}
Timer::Timer(void *userData, unsigned long interval) : userData(userData), interval(interval)
{
	if (interval)
		available = true;
}
Timer::Timer(void *userData, unsigned long interval, TimerExecuteMode mode) : userData(userData), interval(interval), mode(mode)
{
	if (interval)
		available = true;
}

void Timer::DoElapsed()
{
	while (chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - startTime) < interval && enabled)
		this_thread::yield();

	if (!enabled || !available)
		return;
	
	if (!callbacks.empty() && available)
	{
		for_each(callbacks.begin(), callbacks.end(), [&](TimerCallbackFunction &callback)
		{
			callback(*this, userData);
		});
	}
}

void Timer::Elapsed()
{
	if (!available)
		return;
	do
	{
		if (!enabled)
			break;
		startTime = chrono::steady_clock::now();
		DoElapsed();
	} while (mode == TimerExecuteMode::Loop);
	enabled = false;
}

bool Timer::IsEnabled()
{
	if (!available)
		return false;
	return enabled;
}

Timer &Timer::operator+=(const TimerCallbackFunction &callback)
{
	AppendCallback(callback);
	return *this;
}

Timer &Timer::operator-=(const TimerCallbackFunction &callback)
{
	RemoveCallback(callback);
	return *this;
}

void Timer::AppendCallback(const TimerCallbackFunction &callback)
{
	if (!available)
		return;
	if (callback)
		callbacks.push_back(callback);
};

void Timer::RemoveCallback(const TimerCallbackFunction &callback)
{
	if (!available)
		return;
	if (callback)
		callbacks.remove(callback);
}

void Timer::Start()
{
	if (!available)
		return;
	if (enabled)
		Stop();
	async(launch::async, [&](){ Elapsed(); });
	enabled = true;
}

void Timer::Stop()
{
	enabled = false;
}

Timer::~Timer()
{
	Stop();
}
_L_END
