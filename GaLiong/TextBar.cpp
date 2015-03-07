#include "TextBar.hpp"

_L_BEGIN
TextBar::TextBar()
{
	implemented = ControlInterface::IRenderable | ControlInterface::IClickable;

	textTimer = Timer(this);
	textTimer += textTimer_Elapsed;

	text = L"";
	textOffset = 0;
	textLength = 0;

	label.alignment = Alignment::Left;

	available = true;
}
TextBar::~TextBar()
{
	textTimer.Stop();
}

bool TextBar::AppendText(wstring text)
{
	this->text += text;
	textLength = this->text.size();
	if (immediately)
	{
		label.AppendText(text);
		label.GenerateFont();
	}
	else
	{
		immediately = false;
		textTimer.Start();
	}

	return true;
}

void TextBar::BindTexture(TextureRef texture)
{
	Entity::BindTexture(texture);
}

bool TextBar::ChangeText(wstring text)
{
	this->text.clear();
	this->text = text;
	textOffset = 0;
	textLength = text.size();
	label.ClearText();
	AppendText(text);
	return true;
}

void TextBar::SetTextSpeed(unsigned short msPerChar)
{
	if (msPerChar == 0)
	{
		textTimer.Stop();
		immediately = true;
	}
	else
		immediately = false;
	textTimer.SetInterval(msPerChar);
}

void TextBar::textTimer_Elapsed(Timer &sender, void *userData)
{
	TextBar *instance = reinterpret_cast<TextBar *>(userData);
	if (instance)
	{
		if (instance->textOffset < instance->textLength)
		{
			instance->label.AppendText(instance->text.substr(instance->textOffset, 1));
			instance->textOffset++;
		}
		else
			instance->textTimer.Stop();
	}
}
_L_END