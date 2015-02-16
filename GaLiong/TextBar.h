#pragma once
#include "Preprocess.h"
#include "TextEntity.h"
#include "Timer.h"

_L_BEGIN
class _L_ TextBar : public TextEntity
{
public:
	void BindTexture(TextureBase *texture) override
	{
		Entity::BindTexture(texture);
	}
	void Move(unsigned long duration, RectD destination);
private:
	Timer moveTimer;
};
_L_END