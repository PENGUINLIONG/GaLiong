#pragma once
#include "Preprocess.hpp"
#include "Entity.hpp"
#include "Font.hpp"
#include "Label.hpp"

_L_BEGIN
class _L_ TextEntity : public Entity
{
public:
	TextEntity();
	virtual ~TextEntity() override;
	virtual bool AppendText(wstring text)
	{
		return label.AppendText(text);
	}
	virtual void BindFont(Font &font)
	{
		label.BindFont(font);
	}
	virtual void BindTexture(TextureRef texture) = 0;
	virtual bool ChangeText(wstring text)
	{
		return label.ChangeText(text);
	}
	virtual void ClearText()
	{
		label.ClearText();
	}
	virtual void SetPosition(PointD position) override
	{
		Entity::SetPosition(position);
		label.pos = position;
	}
	virtual void SetSize(SizeD size) override
	{
		Entity::SetSize(size);
		label.size = size;
	}
protected:
	Label label;

	virtual void SetWindowSize(Size *windowSize) override
	{
		Entity::SetWindowSize(windowSize);
		label.SetWindowSize(windowSize);
	}
	void TextEntity_Render(void *sender, EventArgs e)
	{
		label.Render(this, e);
	}
	void TextEntity_Resize(void *sender, ResizeEventArgs e)
	{
		if (!size.Width || !size.Height)
			return;
		label.Resize(this, e);
	}
};
_L_END