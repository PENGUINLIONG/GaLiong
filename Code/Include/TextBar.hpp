#pragma once
#include "Preprocess.hpp"
#include "Button.hpp"
#include "Timer.hpp"

_L_BEGIN
class _L_ TextBar : public Button
{
public:
	TextBar();
	virtual ~TextBar() override;
	virtual bool AppendText(wstring text) override;
	virtual void BindTexture(TextureRef texture) override;
	virtual bool ChangeText(wstring text) override;
	void Move(unsigned long duration, RectD destination);
	void SetTextSpeed(unsigned short msPerChar);
private:
	bool available = false, immediately = true;

	wstring text;
	size_t textLength, textOffset;
	
	Timer moveTimer, textTimer;

	static void textTimer_Elapsed(void *sender, ElapsedEventArgs e);
};
_L_END