#pragma once
#include "Preprocess.h"

_L_BEGIN
class _L_ IClickable
{	
public:
	virtual bool CheckClick(Size window, Point point) = 0;
	virtual void ClickEventHandler(Point point) = 0;
};
_L_END
