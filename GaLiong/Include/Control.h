#pragma once
#include "Preprocess.h"

_L_BEGIN
class _L_ Control
{
	friend class Window;
public:
	virtual const inline bool Implemented(unsigned long long key) final
	{
		return (key & implemented) ? true : false;
	}
protected:
	unsigned long long implemented = 0x00000000;
	Size *windowSize;
};
_L_END