#pragma once
#include "Preprocess.h"

_L_BEGIN
interface _L_ IRenderable
{
public:
	virtual void Render() = 0;
	virtual void Resize() = 0;
};
_L_END
