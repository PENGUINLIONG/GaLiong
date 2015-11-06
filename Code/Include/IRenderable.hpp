#pragma once
#include "Preprocess.hpp"
#include "Event.hpp"

_L_BEGIN
class ResizeEventArgs : EventArgs
{
public:
	Size WindowSize;

	ResizeEventArgs(Size windowSize);
};

class _L_ IRenderable
{
public:
	Event<EventArgs> Render;
	Event<ResizeEventArgs> Resize;
};
_L_END
