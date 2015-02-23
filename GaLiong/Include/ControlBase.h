#pragma once
#include "Preprocess.h"

_L_BEGIN
class _L_ ControlBase
{
	friend class Window;
public:
	virtual const bool Implemented(BufferLength key) final
	{
		return (key & implemented) ? true : false;
	}
protected:
	BufferLength implemented = 0x00000000;
	Size *windowSize = nullptr;

	virtual ~ControlBase() {}
	virtual void SetWindowSize(Size *windowSize)
	{
		this->windowSize = windowSize;
	}
};
_L_END
