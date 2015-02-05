#pragma once
#include "Preprocess.h"

_L_BEGIN
interface _L_ IRenderable
{
public:
	virtual void Render() = 0;
protected:
	bool visible = true;
};
_L_END
