#pragma once
#include "Preprocess.hpp"

_L_BEGIN
class _L_ IClickable
{	
public:
	virtual bool CheckClick(PointD point) = 0;
	virtual void ClickEventHandler(Point point) = 0;
};
_L_END
