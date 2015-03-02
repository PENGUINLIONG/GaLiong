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
	virtual bool AppendText(wstring text) override;
	virtual void BindTexture(TextureRef texture) override;
	void BindBorderTexture(TextureRef texture, const Flag comment);
	virtual bool ChangeText(wstring text) override;
	void Move(unsigned long duration, RectD destination);
	virtual void Render() override;
	virtual void Resize() override;
	void SetTextSpeed(unsigned short msPerChar);
private:
	struct BorderComponent
	{
		TextureRef Texture;
		Renderer::ReverseMethod ReverseMethod;
		RectD Rect;
		Flag Comment;
		SizeD TextureDuplication;
	};
	friend class array<BorderComponent, 8>;

	bool available = false, immediately = true;
	array<BorderComponent, 8> textures_Border;

	wstring text;
	size_t textLength, textOffset;
	
	Timer moveTimer, textTimer;

	static void textTimer_Elapsed(Timer &sender, void *userData);
};
_L_END