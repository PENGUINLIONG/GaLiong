#pragma once
#include "Preprocess.hpp"
#include "TextEntity.hpp"
#include "Timer.hpp"

_L_BEGIN
class _L_ TextBar : public TextEntity
{
public:
	TextBar();
	virtual ~TextBar() override;
	virtual bool AppendText(wstring text) override;
	virtual void BindTexture(TextureRef texture) override;
	virtual bool ChangeText(wstring text) override;
	void Move(unsigned long duration, RectD destination);
	virtual void Render() override;
	virtual void Resize() override;
	void SetTextSpeed(unsigned short msPerChar);
private:
	bool available = false, immediately = true;

	wstring text;
	size_t textLength, textOffset;
	
	Timer moveTimer, textTimer;

	static void textTimer_Elapsed(Timer &sender, void *userData);
};
_L_END