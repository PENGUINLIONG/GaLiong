#include "Timer.hpp"

_L_BEGIN
Timer::Timer()
{
}
Timer::Timer(void *userData) : userData(userData), interval(1000), mode(TimerExecuteMode::Loop)
{
	available = true;
}
Timer::Timer(void *userData, unsigned long interval, TimerExecuteMode mode = TimerExecuteMode::Loop) : userData(userData), interval(interval), mode(mode)
{
	if (interval)
		available = true;
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
		
		[&](){
			while (chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - startTime) < interval && enabled)
				this_thread::yield();

			if (!enabled || !available)
				return;

			if (!callbacks.empty() && available)
			{
				for (const auto &callback : callbacks)
				{
					callback(*this, userData);
				}
			}
		}();

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
	if (available && callback)
		callbacks.push_back(callback);
	return *this;
}

Timer &Timer::operator-=(const TimerCallbackFunction &callback)
{
	if (!available || !callback)
		return *this;
	auto funcPtr = callback.target<void(*)(Timer, void *)>();
	callbacks.remove_if([funcPtr](TimerCallbackFunction &inList){ return funcPtr == inList.target<void(*)(Timer, void *)>(); });
	return *this;
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

void Timer::SetInterval(unsigned long interval)
{
	bool shouldStart = enabled;
	Stop();
	this->interval = chrono::milliseconds(interval);
	if (shouldStart)
		Start();
}

Timer::~Timer()
{
	Stop();
}
_L_END