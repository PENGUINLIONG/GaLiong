#pragma once
#include "Preprocess.h"
#include "TextEntity.h"
#include "Timer.h"

_L_BEGIN
class _L_ TextBar : public TextEntity
{
public:
	struct BorderComment
	{
		const static Flag NoComment   = 0x0000;
		const static Flag Left        = 0x0001;
		const static Flag Top         = 0x0002;
		const static Flag Right       = 0x0004;
		const static Flag Bottom      = 0x0008;
		const static Flag UpperLeft   = 0x0010;
		const static Flag UpperRight  = 0x0040;
		const static Flag LowerLeft   = 0x0020;
		const static Flag LowerRight  = 0x0080;
		 
		const static Flag EveryBorder = 0x000F;
		const static Flag EveryCorner = 0x00F0;
		const static Flag EveryWhere  = 0x00FF;
	};

	TextBar();
	virtual ~TextBar() override;
	virtual void BindTexture(TextureRef texture) override;
	void BindBorderTexture(TextureRef texture, const Flag comment);
	void Move(unsigned long duration, RectD destination);
	virtual void Render() override;
	virtual void Resize() override;
private:
	bool available = false;
	struct BorderComponent
	{
		TextureRef Texture;
		Renderer::ReverseMethod ReverseMethod;
		RectD Rect;
		Flag Comment;
		SizeD TextureDuplication;
	};
	array<BorderComponent, 8> textures_Border;
	Timer moveTimer, textTimer;
};
_L_END