#pragma once
#include "Preprocess.h"
#include "Font.h"
#include "Renderer.h"
#include "Entity.h"
#include "TextureBase.h"

_L_BEGIN
interface TextureBase;

class _L_ Label : public Entity
{
	friend class TextEntity;
public:
	Label();
	virtual ~Label() override;

	bool AppendText(const wchar_t *text)
	{
		if (!font || !available || !wcslen(text))
			return false;

		this->text.append(text);
		return GenerateFont();
	}
	void BindFont(Font &font)
	{
		this->font = &font;
		visible = available = true;
		ClearTextures();
	}
	virtual void BindTexture(TextureBase *texture){}
	bool ChangeText(const wchar_t *text)
	{
		if (!available)
			return false;

		ClearText();
		AppendText(text);
		return true;
	}
	void ClearText()
	{
		empty = true;
		text.clear();
		fontSize = { 0, 0 };
		ClearTextures();
	}
	bool GenerateFont();
	virtual void Render() override;
	virtual void Resize() override
	{
		GenerateFont();
	}
private:
	bool available = false;
	bool empty = true;
	PointD fontPos;
	SizeD fontSize;
	wstring text = L"";
	Font *font = nullptr;
};
_L_END