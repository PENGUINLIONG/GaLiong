#pragma once
#include "Preprocess.h"
#include "TextEntity.h"
#include "Timer.h"

_L_BEGIN
class _L_ TextBar : public TextEntity
{
public:
	TextBar();
	~TextBar();
	void BindTexture(TextureBase *texture) override;
	void BindBorderTexture(TextureBase *texture);
	void Move(unsigned long duration, RectD destination);
private:
	Flag borderConfig = 0x0000;
	Texture *border[8];
	Timer moveTimer, textTimer;
};
_L_END