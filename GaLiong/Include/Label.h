#pragma once
#include "Preprocess.h"
#include "Font.h"
#include "Renderer.h"
#include "Entity.h"
#include "Texture.h"

_L_BEGIN
class Texture;

class _L_ Label : public Entity
{
	friend class TextEntity;
public:
	Alignment alignment;

	Label();
	virtual ~Label() override;

	bool AppendText(wstring text)
	{
		if (!font || !available || text.empty())
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
	virtual void BindTexture(TextureRef texture) { }
	bool ChangeText(wstring text)
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
		ClearTextures();
		fontSize = { 0, 0 };
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