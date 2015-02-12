#pragma once
#include "Preprocess.h"
#include "Entity.h"
#include "Font.h"
#include "Label.h"

_L_BEGIN
class _L_ TextEntity : public Entity
{
public:
	TextEntity();
	inline bool AppendText(const wchar_t *text)
	{
		return label.AppendText(text);
	}
	virtual void BindFont(Font &font)
	{
		label.BindFont(font);
	}
	virtual void BindTexture(TextureBase *texture) = 0;
	bool ChangeText(const wchar_t *text)
	{
		return label.ChangeText(text);
	}
	inline void ClearText()
	{
		label.ClearText();
	}
	inline virtual void Render() override
	{
		Entity::Render();
		label.Render();
	}
	virtual inline void SetPosition(PointD position) override
	{
		Entity::SetPosition(position);
		label.pos = position;
	}
	virtual inline void SetSize(SizeD size) override
	{
		Entity::SetSize(size);
		label.size = size;
	}
	~TextEntity();
protected:
	Label label;

	inline virtual void SetWindowSize(Size *windowSize) override
	{
		Entity::SetWindowSize(windowSize);
		label.SetWindowSize(windowSize);
	}
};
_L_END