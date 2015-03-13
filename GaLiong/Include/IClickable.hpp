#pragma once
#include "Preprocess.hpp"
#include "Event.hpp"

_L_BEGIN
enum class MouseButtons
{
	Left,
	Middle,
	None,
	Right
};

class _L_ MouseEventArgs : public EventArgs
{
public:
	MouseButtons Button = MouseButtons::None;
	bool ButtonDown = 0;
	int Delta = 0;
	Point Location;

	MouseEventArgs(Point Location);
	MouseEventArgs(Point Location, MouseButtons Button, bool ButtonDown);
	MouseEventArgs(Point Location, int Delta);
};

class _L_ IClickable
{	
public:
	virtual bool IsHover(PointD point) = 0;
	Event<MouseEventArgs> MouseHover, MouseButton, MouseWheel;
};
_L_END